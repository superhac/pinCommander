#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <ui.h>
#include "touch.h"
#include "lvgl_event_handler.h"
#include "WiFi.h"
#include <WiFiUdp.h>
#include "AsyncUDP.h"
#include <mutex>
#include "msgids.h"



/*Don't forget to set Sketchbook location in File/Preferencesto the path of your UI project (the parent foder of this INO file)*/

/* Device Name */
char DEVICE_NAME[] = "hmi";

/* WiFi Settings */
char SSID[] = "pincommander";
char SSID_PASS[] = "pincommanderpass";

/* lvgl mutex to update from other threads without issues */
std::mutex lvgl_mutex;

// UDP Sock setup info for sending  */
WiFiUDP udp;
const char *udpAddress = "255.255.255.255";  //broadcast
const int udpPort = 9797;

//broadcast listener
AsyncUDP audp;

// what pin is the backlight
#define GFX_BL 2

/* Dev Device Declaration */
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
  45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
  5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
  8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */,
  1 /* hsync_polarity */, 8 /* hsync_front_porch */, 1 /* hsync_pulse_width */, 32 /* hsync_back_porch */,
  1 /* vsync_polarity */, 8 /* vsync_front_porch */, 1 /* vsync_pulse_width */, 8 /* vsync_back_porch */,
  1 /* pclk_active_neg */, 12000000 /* prefer_speed */);

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
  800 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */);

/* screen resolution */
const uint32_t screenWidth = 800;
const uint32_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf_1[screenWidth * 10];
static lv_color_t buf_2[screenWidth * 10];
//static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing _ Double buffering */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif


  lv_disp_flush_ready(disp);
}

/* Callback for hetting touches */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touch_has_signal()) {
    if (touch_touched()) {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      //Serial.print("Data x :");
      //Serial.println(touch_last_x);

      //Serial.print("Data y :");
      //Serial.println(touch_last_y);
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_REL;
    }
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
  delay(15);
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, SSID_PASS);
  Serial.print("Connecting to WiFi ..");
}

void WiFiEvent(WiFiEvent_t event) {
  lvgl_mutex.lock(); /* need to block UI updates when updating UI objects */
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("Connected to access point");
      lv_img_set_src(ui_WiFiStatusImg, &ui_img_green_wifi_64_png);
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("Disconnected from WiFi access point");
      lv_img_set_src(ui_WiFiStatusImg, &ui_img_red_wifi_64_png);
      WiFi.reconnect();
      break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.print("Obtained IP address: ");
      Serial.println(WiFi.localIP());
      break;
    default: break;
  }
  lvgl_mutex.unlock();
}

/* setup */
void setup() {

  Serial.begin(115200); /* prepare for possible serial debug */

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);

  /* setup wifi */
  initWiFi();
  WiFi.onEvent(WiFiEvent);

  // Init Display
  gfx->begin();
  gfx->fillScreen(BLACK);

  /* turn on backlight og LCD */
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);

  /* init the lvgl lib */
  lv_init();
  delay(500);

  /* init the gt911 touchscreen */
  touch_init();

  if (!buf_2) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
    Serial.flush();
  } else {

    /* setup double buffering */
    lv_disp_draw_buf_init(&draw_buf, buf_1, buf_2, screenWidth * 10);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the touchscreen input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

// register logging call back-  needed?
#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print);
#endif
    Serial.println("Setup done");

    ui_init();
    lv_label_set_text(ui_ssidLabel, SSID);
    lv_label_set_text(ui_deviceNameLabel, DEVICE_NAME);
  }
}

void processBroadcast(AsyncUDPPacket packet) {
  if (packet.isBroadcast()) {

    /* convert payload into a string */
    uint8_t *payload = packet.data();
    Serial.println((char *)payload);
    char msg[packet.length() + sizeof(char)] = {}; /* +1 for \0 */
    memcpy(msg, payload, packet.length());
    msg[packet.length() + sizeof(char)] = '\0';  // add Null-termination for the string

    /* Tokenize */
    char *msgSenderID = NULL;
    char *msgID = NULL;
    char *msgData = NULL;

    char *tokenStore;
    tokenStore = strtok(msg, "/");
    if (tokenStore != NULL) {
      msgSenderID = strdup(tokenStore);
    }
    tokenStore = strtok(NULL, "/");
    if (tokenStore != NULL) {
      msgID = strdup(tokenStore);
    }
    tokenStore = strtok(NULL, "/");
    if (tokenStore != NULL) {
      msgData = strdup(tokenStore);
    }
    //Serial.println(senderID);
    //Serial.println(msgID);
    //Serial.println(msgData);

    if (msgID != NULL) {
      switch (atoi(msgID)) {
        case 0:
          Serial.println("invalid msgID? atoi reutned 0");
          break;
        case MSG_ID_CAB_TEMP:
          processTempMessage(msgData);
          break;
        case MSG_ID_PONG_RESP:
          if(msgSenderID != NULL) {
            processPongResponse(msgData, msgSenderID);
          }
          break;
        default:
          Serial.println("could not match msgID?");
          break;
      }
    } else {
      Serial.print("unknown msgID! masID=");
      Serial.println(msgID);
    }
  }
}

void processPongResponse(char *payload, char *sender) {
  char buff[50];
  if (strlen(sender) <= 50) {
    sprintf(buff,"Detected a ping resposne from \"%s\". \n", sender);
    Serial.println(buff);
    lvgl_mutex.lock();
    lv_textarea_add_text(ui_statusMsgsTextArea, buff);
    lvgl_mutex.unlock();
  }
}

void processTempMessage(char *payload) {
  lvgl_mutex.lock();
  lv_label_set_text(ui_cabinetTempLabel, payload);
  lvgl_mutex.unlock();
}

// this is externed because lvgl is calling this from a C based callback and this is a cpp file.
extern "C" void sendUDPMsg(char buffer[], size_t size, uint8_t msgID) {
  char msgBuff[200]={};
  char msgIDString [10];
  itoa(msgID,msgIDString, 10);
  size_t headerSize = strlen(DEVICE_NAME) + 1 + strlen(msgIDString) + 1; // "+1" for the slash delimitars 
  sprintf(msgBuff, "%s/%s/",DEVICE_NAME,msgIDString);
  memcpy(msgBuff+headerSize, buffer, size); // this starts at the NULL string terminator in the string.
  
  udp.beginPacket(udpAddress, udpPort);
  udp.write((const uint8_t *)msgBuff, headerSize + size);
  udp.endPacket();
}

void loop() {
  lvgl_mutex.lock();
  lv_timer_handler(); /* let the GUI do its work */
  lvgl_mutex.unlock();
  if (audp.listen(9797)) {
    audp.onPacket(processBroadcast);
  }
}
