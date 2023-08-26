#include <lvgl.h>
#include "lvgl_event_handler.h"
#include <ui.h>
#include "msgids.h"

/* KEYMAP for PinVol */

/* Global */
const uint8_t PINVOL_GLOBAL_VOL_UP_KEYMAP[] = "PINVOL_GLOBAL_VOL_UP_KEYMAP";
const uint8_t PINVOL_GLOBAL_VOL_DOWN_KEYMAP[] = "PINVOL_GLOBAL_VOL_DOWN_KEYMAP";
const uint8_t PINVOL_GLOBAL_NIGHT_MODE_KEYMAP[] = "PINVOL_GLOBAL_NIGHT_MODE_KEYMAP";
const uint8_t PINVOL_GLOBAL_MUTE_KEYMAP[] = "PINVOL_GLOBAL_MUTE_KEYMAP";

/* Table */
const uint8_t PINVOL_TABLE_VOL_UP_KEYMAP[] = "PINVOL_TABLE_VOL_UP_KEYMAP";
const uint8_t PINVOL_TABLE_VOL_DOWN_KEYMAP[] = "PINVOL_TABLE_VOL_DOWN_KEYMAP";

/* SSF */
const uint8_t PINVOL_SSF_BG_VOL_UP_KEYMAP[] = "PINVOL_SSF_BG_VOL_UP_KEYMAP";
const uint8_t PINVOL_SSF_BG_VOL_DOWN_KEYMAP[] = "PINVOL_SSF_BG_VOL_DOWN_KEYMAP";
const uint8_t PINVOL_SSF_REAR_VOL_UP_KEYMAP[] = "PINVOL_SSF_REAR_VOL_UP_KEYMAP";
const uint8_t PINVOL_SSF_REAR_VOL_DOWN_KEYMAP[] = "PINVOL_SSF_REAR_VOL_DOWN_KEYMAP";
const uint8_t PINVOL_SSF_FRONT_VOL_UP_KEYMAP[] = "PINVOL_SSF_FRONT_VOL_UP_KEYMAP";
const uint8_t PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP[] = "PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP";

/* KEYMAP for PinMame */
const uint8_t PINMAME_EBBUYIN_KEYMAP[] = "PINMAME_EBBUYIN_KEYMAP";
const uint8_t PINMAME_COIN3_KEYMAP[] = "PINMAME_COIN3_KEYMAP";
const uint8_t PINMAME_COIN4_KEYMAP[] = "PINMAME_COIN4_KEYMAP";
const uint8_t PINMAME_DOOR_KEYMAP[] = "PINMAME_DOOR_KEYMAP";
const uint8_t PINMAME_CANCEL_KEYMAP[] = "PINMAME_CANCEL_KEYMAP";
const uint8_t PINMAME_DOWN_KEYMAP[] = "PINMAME_DOWN_KEYMAP";
const uint8_t PINMAME_UP_KEYMAP[] = "PINMAME_UP_KEYMAP";
const uint8_t PINMAME_ENTER_KEYMAP[] = "PINMAME_ENTER_KEYMAP";

const uint8_t PINMAME_SHOWOPTS_KEYMAP[] = "PINMAME_SHOWOPTS_KEYMAP";
const uint8_t PINMAME_SHOWKEYS_KEYMAP[] = "PINMAME_SHOWKEYS_KEYMAP";
const uint8_t PINMAME_DIP_KEYMAP[] = "PINMAME_DIP_KEYMAP";
const uint8_t PINMAME_RESETEMU_KEYMAP[] = "PINMAME_RESETEMU_KEYMAP";
const uint8_t PINMAME_ADDEBALL_KEYMAP[] = "PINMAME_ADDEBALL_KEYMAP";
const uint8_t PINMAME_WINDOWLOCK_KEYMAP[] = "PINMAME_WINDOWLOCK_KEYMAP";
const uint8_t PINMAME_BANGBACK_KEYMAP[] = "PINMAME_BANGBACK_KEYMAP";
const uint8_t PINMAME_DISPLAYSIZE_KEYMAP[] = "PINMAME_DISPLAYSIZE_KEYMAP";



void buttonPinvolCallback(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {

    /* Global */
    if (ui_pinvolGlobalUpImgButton == btn) {
      LV_LOG_USER("pinvolGlobalUpImgButton");
      sendUDPMsg(PINVOL_GLOBAL_VOL_UP_KEYMAP, strlen(PINVOL_GLOBAL_VOL_UP_KEYMAP), MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolGlobalDownImgButton == btn) {
      LV_LOG_USER("pinvolGlobalDownImgButton Event recv");
      sendUDPMsg(PINVOL_GLOBAL_VOL_DOWN_KEYMAP, sizeof(PINVOL_GLOBAL_VOL_DOWN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolGlobalNightModeButton == btn) {
      LV_LOG_USER("PINVOL_GLOBAL_NIGHT_MODE_KEYMAP Event recv");
      sendUDPMsg(PINVOL_GLOBAL_NIGHT_MODE_KEYMAP, sizeof(PINVOL_GLOBAL_NIGHT_MODE_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolGlobalMuteImgButton == btn) {
      LV_LOG_USER("PINVOL_GLOBAL_MUTE_KEYMAP Event recv");
      sendUDPMsg(PINVOL_GLOBAL_MUTE_KEYMAP, sizeof(PINVOL_GLOBAL_MUTE_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings

      /* table */
    } else if (ui_pinvolTableVolUpImgButton == btn) {
      LV_LOG_USER("PINVOL_TABLE_VOL_UP_KEYMAP Event recv");
      sendUDPMsg(PINVOL_TABLE_VOL_UP_KEYMAP, sizeof(PINVOL_TABLE_VOL_UP_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolTableVolDownImgButton == btn) {
      LV_LOG_USER("PINVOL_TABLE_VOL_DOWN_KEYMAP Event recv");
      sendUDPMsg(PINVOL_TABLE_VOL_DOWN_KEYMAP, sizeof(PINVOL_TABLE_VOL_DOWN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings

      /* SSF */
    } else if (ui_pinvolSSFBgUpImgButton == btn) {
      LV_LOG_USER("PINVOL_SSF_BG_VOL_UP_KEYMAP Event recv");
      sendUDPMsg(PINVOL_SSF_BG_VOL_UP_KEYMAP, sizeof(PINVOL_SSF_BG_VOL_UP_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolSSFBgDownImgButton == btn) {
      LV_LOG_USER("PINVOL_SSF_BG_VOL_UP_KEYMAP Event recv");
      sendUDPMsg(PINVOL_SSF_BG_VOL_DOWN_KEYMAP, sizeof(PINVOL_SSF_BG_VOL_DOWN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolSSFRearUpImgButton == btn) {
      LV_LOG_USER("PINVOL_SSF_REAR_VOL_UP_KEYMAP Event recv");
      sendUDPMsg(PINVOL_SSF_REAR_VOL_UP_KEYMAP, sizeof(PINVOL_SSF_REAR_VOL_UP_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolSSFRearDownImgButton == btn) {
      LV_LOG_USER("PINVOL_SSF_BG_VOL_UP_KEYMAP Event recv");
      sendUDPMsg(PINVOL_SSF_REAR_VOL_DOWN_KEYMAP, sizeof(PINVOL_SSF_REAR_VOL_DOWN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolSSFFrontUpImgButton == btn) {
      LV_LOG_USER("pinvolSSFFrontUpImgButton Event recv");
      sendUDPMsg(PINVOL_SSF_FRONT_VOL_UP_KEYMAP, sizeof(PINVOL_SSF_FRONT_VOL_UP_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinvolSSFFrontDownImgButton == btn) {
      LV_LOG_USER("pinvolSSFFrontDownImgButton Event recv");
      sendUDPMsg(PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP, sizeof(PINVOL_SSF_FRONT_VOL_DOWN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    }

  } /* end button click event */
}

void buttonPinmameCallback(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {

    if (ui_pinmameEBBuyinButton == btn) {
      LV_LOG_USER("pinmameEBBuyinButton Event recv");
      sendUDPMsg(PINMAME_EBBUYIN_KEYMAP, sizeof(PINMAME_EBBUYIN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameCoin3Button == btn) {
      LV_LOG_USER("pinmameCoin3Button Event recv");
      sendUDPMsg(PINMAME_COIN3_KEYMAP, sizeof(PINMAME_COIN3_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameCoin4Button == btn) {
      LV_LOG_USER("pinmameCoin3Button Event recv");
      sendUDPMsg(PINMAME_COIN4_KEYMAP, sizeof(PINMAME_COIN4_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameUpButton == btn) {
      LV_LOG_USER("PINMAME_UP_KEYMAP Event recv");
      sendUDPMsg(PINMAME_UP_KEYMAP, sizeof(PINMAME_UP_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameDownButton == btn) {
      LV_LOG_USER("PINMAME_UP_KEYMAP Event recv");
      sendUDPMsg(PINMAME_DOWN_KEYMAP, sizeof(PINMAME_DOWN_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameDoorButton == btn) {
      LV_LOG_USER("PINMAME_DOOR_KEYMAP Event recv");
      sendUDPMsg(PINMAME_DOOR_KEYMAP, sizeof(PINMAME_DOOR_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameEnterButton == btn) {
      LV_LOG_USER("PINMAME_ENTER_KEYMAP Event recv");
      sendUDPMsg(PINMAME_ENTER_KEYMAP, sizeof(PINMAME_ENTER_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameCancelButton == btn) {
      LV_LOG_USER("PINMAME_CANCEL_KEYMAP Event recv");
      sendUDPMsg(PINMAME_CANCEL_KEYMAP, sizeof(PINMAME_CANCEL_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameShowOptsButton == btn) {
      LV_LOG_USER("pinmameShowOptsButton Event recv");
      sendUDPMsg(PINMAME_SHOWOPTS_KEYMAP, sizeof(PINMAME_SHOWOPTS_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameShowKeysButton == btn) {
      LV_LOG_USER("pinmameShowKeysButton Event recv");
      sendUDPMsg(PINMAME_SHOWKEYS_KEYMAP, sizeof(PINMAME_SHOWKEYS_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameDipButton == btn) {
      LV_LOG_USER("pinmameDipButton Event recv");
      sendUDPMsg(PINMAME_DIP_KEYMAP, sizeof(PINMAME_DIP_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameResetEmuButton == btn) {
      LV_LOG_USER("pinmameResetEmuButton Event recv");
      sendUDPMsg(PINMAME_RESETEMU_KEYMAP, sizeof(PINMAME_RESETEMU_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameAddEBallButton == btn) {
      LV_LOG_USER("pinmameAddEBallButton Event recv");
      sendUDPMsg(PINMAME_ADDEBALL_KEYMAP, sizeof(PINMAME_ADDEBALL_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameWindowLockButton == btn) {
      LV_LOG_USER("pinmameWindowLockButton Event recv");
      sendUDPMsg(PINMAME_WINDOWLOCK_KEYMAP, sizeof(PINMAME_WINDOWLOCK_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameBangBackButton == btn) {
      LV_LOG_USER("pinmameBangBackButton Event recv");
      sendUDPMsg(PINMAME_BANGBACK_KEYMAP, sizeof(PINMAME_BANGBACK_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    } else if (ui_pinmameDisplaySizeButton == btn) {
      LV_LOG_USER("pinmameDisplaySizeButton Event recv");
      sendUDPMsg(PINMAME_DISPLAYSIZE_KEYMAP, sizeof(PINMAME_DISPLAYSIZE_KEYMAP) - 1, MSG_ID_KEY_SEQUENCE);  //take off 1 to remove the null on strings
    }
  }
}

void buttonStatusCallback(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t* btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {

    if (ui_statusPingButton == btn) {
      char msg[] = "ping";
      LV_LOG_USER("statusPingButton Event recv");
      sendUDPMsg(msg, strlen(msg), MSG_ID_PING_REQ);
    }
  }
}