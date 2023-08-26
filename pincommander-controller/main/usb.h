/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */

#pragma once
#ifndef USB_H
#define USB_H

#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "class/hid/hid_device.h"
#include "driver/gpio.h"

#define TUSB_DESC_TOTAL_LEN      (TUD_CONFIG_DESC_LEN + CFG_TUD_HID * TUD_HID_DESC_LEN)  

enum
{
  REPORT_ID_KEYBOARD = 1,
  REPORT_ID_MOUSE,
  REPORT_ID_CONSUMER_CONTROL,
  REPORT_ID_GAMEPAD,
  REPORT_ID_COUNT
};


extern uint8_t hid_report_descriptor[];
extern char* hid_string_descriptor[5];
extern uint8_t hid_configuration_descriptor[];

void send_hid_controller(float x, float y, uint32_t buttons);
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance);
void send_hid_keyboard(uint8_t keycode[], uint8_t keymodifier);
void send_hid_consumer(uint16_t consumerkey, uint8_t keymodifier);


#endif