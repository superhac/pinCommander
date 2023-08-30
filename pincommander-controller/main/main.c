/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "usb.h"
#include "udp_server.h"
#include "accel.h"
// #include "keymaps.h"
#include "led_strip.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
// #include "lwip/sockets.h"

#include "esp_netif.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

static const char *TAG = "main.c";

// on esp32-s3 - GPIO 1, GPIO2, GPIO_NUM_46 (Nothing), and GPIO 20, GPIO 19 (causes reboot when grounded?), GPIO 48 appears to be connected to NEOPIXEL don't work.
gpio_num_t pins[] = {GPIO_NUM_3, GPIO_NUM_6, GPIO_NUM_7, GPIO_NUM_8, GPIO_NUM_9, GPIO_NUM_10, GPIO_NUM_11, GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14,
                     GPIO_NUM_15, GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18, GPIO_NUM_21, GPIO_NUM_36, GPIO_NUM_40, GPIO_NUM_41, GPIO_NUM_42, GPIO_NUM_45, GPIO_NUM_47};

// windows button HID starts at 1.  e.g. 0=1, 1=2, .. on windows.  ** Theres also an issue in using GAMEPAD_BUTTON_0.  The any GPIO mapped to it doesn't work. skipped for now 
uint32_t buttons[] = {GAMEPAD_BUTTON_1, GAMEPAD_BUTTON_2, GAMEPAD_BUTTON_3, GAMEPAD_BUTTON_4, GAMEPAD_BUTTON_5, GAMEPAD_BUTTON_6, GAMEPAD_BUTTON_7,
                      GAMEPAD_BUTTON_8, GAMEPAD_BUTTON_9, GAMEPAD_BUTTON_10, GAMEPAD_BUTTON_11, GAMEPAD_BUTTON_12, GAMEPAD_BUTTON_13, GAMEPAD_BUTTON_14, GAMEPAD_BUTTON_15, GAMEPAD_BUTTON_16,
                      GAMEPAD_BUTTON_17, GAMEPAD_BUTTON_18, GAMEPAD_BUTTON_19, GAMEPAD_BUTTON_20, GAMEPAD_BUTTON_21};

/* WiFi Settings for AP Mode*/
#define ESP_WIFI_SSID "pincommander"
#define ESP_WIFI_PASS "pincommanderpass"
#define ESP_WIFI_CHANNEL 1
#define MAX_STA_CONN 4

/* NeoPixel */
// GPIO assignment
#define LED_STRIP_BLINK_GPIO 48
// Numbers of the LED in the strip
#define LED_STRIP_LED_NUMBERS 1
// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)
led_strip_handle_t led_strip = NULL;

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = ESP_WIFI_SSID,
            .ssid_len = strlen(ESP_WIFI_SSID),
            .channel = ESP_WIFI_CHANNEL,
            .password = ESP_WIFI_PASS,
            .max_connection = MAX_STA_CONN,
#ifdef CONFIG_ESP_WIFI_SOFTAP_SAE_SUPPORT
            .authmode = WIFI_AUTH_WPA3_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
#else /* CONFIG_ESP_WIFI_SOFTAP_SAE_SUPPORT */
            .authmode = WIFI_AUTH_WPA2_PSK,
#endif
            .pmf_cfg = {
                .required = true,
            },
        },
    };
    if (strlen(ESP_WIFI_PASS) == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             ESP_WIFI_SSID, ESP_WIFI_PASS, ESP_WIFI_CHANNEL);
}

void configure_led(void)
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_BLINK_GPIO,   // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_LED_NUMBERS,        // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812,            // LED strip model
        .flags.invert_out = false,                // whether to invert the output signal
    };

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .flags.with_dma = false,               // DMA feature is available on ESP target like ESP32-S3
    };

    // LED Strip object handle
    // led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with RMT backend");
    // return led_strip;
}

void led_blue()
{
    ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 5, 30, 35));
    ESP_ERROR_CHECK(led_strip_refresh(led_strip));
}

void setupUSB()
{
    ESP_LOGI(TAG, "USB initialization");
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = (const char **)hid_string_descriptor,
        .string_descriptor_count = sizeof(hid_string_descriptor) / sizeof(hid_string_descriptor[0]),
        .external_phy = false,
        .configuration_descriptor = hid_configuration_descriptor,
    };

    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
    ESP_LOGI(TAG, "USB initialization DONE");
}

void setupButtons()
{
    int i;
    for (i = 0; i < sizeof(pins) / sizeof(gpio_num_t); i++)
    {
        gpio_set_direction(pins[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(pins[i], GPIO_PULLUP_ONLY);
    }
}

uint32_t collect_button_status()
{
    uint32_t btns = 0;
    int i;

    for (i = 0; i < sizeof(buttons) / sizeof(ulong); i++)
    {
        /*                              -----HIGH--(NORMAL)---------  ---LOW (PRESSED)---*/
        btns = gpio_get_level(pins[i]) ? btns & ~(1UL << buttons[i]) : btns | buttons[i]; // active low
    }

    return btns;
}


void sendTemp_task( void * pvParameters )
{

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 3000; //send temp every 30 secs

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(9797);
    int addr_family = AF_INET;
    int ip_protocol = IPPROTO_IP;
    char buffer[50];
    sprintf(buffer, "controller/2/%.2f", getTemp());

    int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);

    for (;;)
    {
        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // Perform action here.
        ESP_LOGI(TAG, "Sending temp");
        int err = sendto(sock, buffer, strlen(buffer)-1, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)); // -1 to remove null
    }

}

void app_main(void)
{
    ESP_LOGI(TAG, "Main Loop Starting");

    /* nvs flash setup.  used by wifi*/
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    /* Init all drivers and devicess*/
    setupUSB();
    setupButtons();
    i2c_sensor_mpu6050_init();
    configure_led();
    wifi_init_softap();

    /*Setup UDP server. IPV4 only*/
    xTaskCreate(udp_server_task, "udp_server", 4096, (void *)AF_INET, 5, NULL);

    /* send temp every 30 secs*/
    xTaskCreate(sendTemp_task, "send temp", 4096, (void *)AF_INET, 5, NULL);

    /* Turn on Led*/
    led_blue();

    /* Wait for usb to mounted */
    printf("Waiting for Tud Mounting\n");
    while (!tud_mounted())
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    printf("Device Tud Mounted\n");

    mpu6050_acce_value_t acce;

    /* Main loop*/
    while (1)
    {
        get_accel(&acce);
        send_hid_controller(acce.acce_x, acce.acce_y, collect_button_status());
        // printf("acce_x:%d, acce_y:%d, acce_z:%f\n", (int) (acce.acce_x*100), (int) (acce.acce_y*100.0f), acce.acce_z);
        vTaskDelay(pdMS_TO_TICKS(10)); // need this or you get the watchdog error on the idle task.
    }
}
