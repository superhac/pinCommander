/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */

#include "usb.h"


static const char *TAG = "usb.c";

/*
 * @brief HID report descriptor
 *
 * In this example we implement Keyboard + Mouse HID device,
 * so we must define both report descriptors
 */
uint8_t hid_report_descriptor[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(REPORT_ID_KEYBOARD)),
    TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(REPORT_ID_MOUSE)), // even though we are not using the mouse you need it for gamepad or the gamepad doesnt work
    TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(REPORT_ID_CONSUMER_CONTROL)),
    TUD_HID_REPORT_DESC_GAMEPAD(HID_REPORT_ID(REPORT_ID_GAMEPAD))};

/**
 * @brief String descriptor
 */
char *hid_string_descriptor[5] = {
    // array of pointer to string descriptors
    (char[]){0x09, 0x04},     // 0: is supported language is English (0x0409)
    "PinComander",            // 1: Manufacturer
    "PinComander-Controller", // 2: Product
    "123356",                 // 3: Serials, should use chip ID
    "HID interface",          // 4: HID
};

/**
 * @brief Configuration descriptor
 *
 * This is a simple configuration descriptor that defines 1 configuration and 1 HID interface
 */
uint8_t hid_configuration_descriptor[] = {
    // Configuration number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, 1, 0, TUSB_DESC_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),
    
    // Interface number, string index, boot protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(0, 4, false, sizeof(hid_report_descriptor), 0x81, 16, 10),
    
};

/************* TinyUSB descriptors ****************/

/********* TinyUSB HID callbacks ***************/

// Invoked when received GET HID REPORT DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance)
{
    ESP_LOGI(TAG, "tud_hid_descriptor_report_cb");
    // We use only one interface and one HID report descriptor, so we can ignore parameter 'instance'
    return hid_report_descriptor;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    ESP_LOGI(TAG, "tud_hid_get_report_cb");
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
extern void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    ESP_LOGI(TAG, "tud_hid_set_report_cb");
}

extern void send_hid_consumer(uint16_t consumerkey, uint8_t keymodifier) 
{
    ESP_LOGI(TAG, "Sending Consumer report");
    /* send keyboard modifiers  */
    tud_hid_keyboard_report(HID_ITF_PROTOCOL_KEYBOARD, keymodifier, NULL);
    vTaskDelay(pdMS_TO_TICKS(10)); 
    /* send consumer key */
    tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &consumerkey, 2);
       
    vTaskDelay(pdMS_TO_TICKS(30));

    /* Unpress keys*/
    uint16_t empty = 0;
    tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty, 2);
    vTaskDelay(pdMS_TO_TICKS(10));
    tud_hid_keyboard_report(HID_ITF_PROTOCOL_KEYBOARD, 0, NULL); 

}

extern void send_hid_keyboard(uint8_t keycode[], uint8_t keymodifier)
{
    // Keyboard output: Send key 'a/A' pressed and released

       ESP_LOGI(TAG, "Sending Keyboard report");
       //uint8_t keycode[6] = {HID_KEY_F10}; //, HID_KEY_B};
       tud_hid_keyboard_report(HID_ITF_PROTOCOL_KEYBOARD, keymodifier, keycode);
       //PINVOL_GLOBAL_VOL_UP_KEYMAP();
       vTaskDelay(pdMS_TO_TICKS(50)); // had to set to 50 for pinmame
       tud_hid_keyboard_report(HID_ITF_PROTOCOL_KEYBOARD, 0, NULL);  

    // vTaskDelay(pdMS_TO_TICKS(1000)); // need to add delay or it won't work?  No less then 10
}

void send_hid_controller(float x, float y, uint32_t buttons)
{
    hid_gamepad_report_t report =
        {
            .x = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0, .hat = 0, .buttons = 0};

    report.x = (uint8_t)(x * 100);
    report.y = (uint8_t)(y * 100);
    report.buttons = buttons;
    tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
}
