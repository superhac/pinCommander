/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */


/***** Pinvol *************************************************************************************/

// global volume - send_hid_keyboard
/*                                      -----Keyboard HID Key-----  ------KEYBOARD Modifiers----*/
#define PINVOL_GLOBAL_VOL_UP_KEYMAP     (uint8_t [6]){HID_KEY_F10}, KEYBOARD_MODIFIER_LEFTGUI
#define PINVOL_GLOBAL_VOL_DOWN_KEYMAP   (uint8_t [6]){HID_KEY_F9},  KEYBOARD_MODIFIER_LEFTGUI
#define PINVOL_GLOBAL_NIGHT_MODE_KEYMAP (uint8_t [6]){HID_KEY_F7},  KEYBOARD_MODIFIER_LEFTGUI
#define PINVOL_GLOBAL_MUTE_KEYMAP       (uint8_t [6]){HID_KEY_F8},  KEYBOARD_MODIFIER_LEFTGUI

// Table Volume.  Uses consumer hid keys. send_hid_consumer
/*                                               -----Consumer HID Key-----                 ------KEYBOARD Modifiers----*/
#define PINVOL_TABLE_VOL_UP_KEYMAP      (uint16_t) HID_USAGE_CONSUMER_VOLUME_INCREMENT,                  0
#define PINVOL_TABLE_VOL_DOWN_KEYMAP    (uint16_t) HID_USAGE_CONSUMER_VOLUME_DECREMENT,                  0

// SSF Volume Uses consumer hid keys. send_hid_consumer
/*                                                -----Consumer HID Key-----                ------KEYBOARD Modifiers----*/
#define PINVOL_SSF_BG_VOL_UP_KEYMAP     (uint16_t) HID_USAGE_CONSUMER_VOLUME_INCREMENT,     KEYBOARD_MODIFIER_LEFTSHIFT
#define PINVOL_SSF_BG_VOL_DOWN_KEYMAP   (uint16_t) HID_USAGE_CONSUMER_VOLUME_DECREMENT,     KEYBOARD_MODIFIER_LEFTSHIFT
#define PINVOL_SSF_REAR_VOL_UP_KEYMAP   (uint16_t) HID_USAGE_CONSUMER_VOLUME_INCREMENT,     KEYBOARD_MODIFIER_LEFTCTRL
#define PINVOL_SSF_REAR_VOL_DOWN_KEYMAP (uint16_t) HID_USAGE_CONSUMER_VOLUME_DECREMENT,     KEYBOARD_MODIFIER_LEFTCTRL
#define PINVOL_SSF_FRONT_VOL_UP_KEYMAP  (uint16_t) HID_USAGE_CONSUMER_VOLUME_INCREMENT,     KEYBOARD_MODIFIER_LEFTALT
#define PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP  (uint16_t) HID_USAGE_CONSUMER_VOLUME_DECREMENT,   KEYBOARD_MODIFIER_LEFTALT

/*************************************************************************************************/

/****** PinMame **********************************************************************************/
// send_hid_keyboard
/*                                      -----Keyboard HID Key-----      ------KEYBOARD Modifiers----*/
#define PINMAME_EBBUYIN_KEYMAP          (uint8_t [6]){HID_KEY_2},       0
#define PINMAME_COIN3_KEYMAP            (uint8_t [6]){HID_KEY_5},       0
#define PINMAME_COIN4_KEYMAP            (uint8_t [6]){HID_KEY_4},       0
#define PINMAME_DOOR_KEYMAP             (uint8_t [6]){HID_KEY_END},     0
#define PINMAME_CANCEL_KEYMAP           (uint8_t [6]){HID_KEY_7},       0
#define PINMAME_DOWN_KEYMAP             (uint8_t [6]){HID_KEY_8},       0
#define PINMAME_UP_KEYMAP               (uint8_t [6]){HID_KEY_9},       0
#define PINMAME_ENTER_KEYMAP            (uint8_t [6]){HID_KEY_0},       0

#define PINMAME_SHOWOPTS_KEYMAP          (uint8_t [6]){HID_KEY_F1},     0
#define PINMAME_SHOWKEYS_KEYMAP          (uint8_t [6]){HID_KEY_F2},     0
#define PINMAME_DIP_KEYMAP               (uint8_t [6]){HID_KEY_F6},     0
#define PINMAME_RESETEMU_KEYMAP          (uint8_t [6]){HID_KEY_F3},     0
#define PINMAME_ADDEBALL_KEYMAP          (uint8_t [6]){HID_KEY_B},      0
#define PINMAME_WINDOWLOCK_KEYMAP        (uint8_t [6]){HID_KEY_F4},     0
#define PINMAME_BANGBACK_KEYMAP          (uint8_t [6]){HID_KEY_T},      0
#define PINMAME_DISPLAYSIZE_KEYMAP       (uint8_t [6]){HID_KEY_F5},     0
/************************************************************************************************/

/****** VPX **********************************************************************************/
// send_hid_keyboard
/*                                      -----Keyboard HID Key-----      ------KEYBOARD Modifiers----*/
#define VPX_STEREO3D_KEYMAP             (uint8_t [6]){HID_KEY_F10},       0
#define VPX_STATS_KEYMAP                (uint8_t [6]){HID_KEY_F11},       0
/************************************************************************************************/
