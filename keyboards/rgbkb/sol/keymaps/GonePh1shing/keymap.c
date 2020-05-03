#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

enum layer_number {
    _BASE = 0,
    _GAME, //Not yet defined
    _FN,
    _SYS
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  _______,
  XXXXXXX,
  GAME,
  FN,
  SYS,
  FN13,
  NUM1,
  NUM2,
  NUM3,
  NUM4,
  NUM5,
  NUM6,
  NUM7,
  NUM8,
  NUM9,
  NUM0,
  NUM00,
  LSHIFT,
  COPY,
  PASTE,
  CUT
};

//Custom keycode aliases
    //Layers
    #define GAME    TG(_GAME)           //Game layer
    #define FN      MO(_FN)             //Function layer
    #define SYS     MO(_SYS)            //System layer
    #define FN13    LT(_FN,KC_F13)      //FN layer, tap 'F13'

    //FN numpad
    #define NUM1    LSFT(KC_5)
    #define NUM2    LSFT(KC_8)
    #define NUM3    LSFT(KC_4)
    #define NUM4    LSFT(KC_9)
    #define NUM5    LSFT(KC_3)
    #define NUM6    LSFT(KC_0)
    #define NUM7    LSFT(KC_2)
    #define NUM8    LSFT(KC_MINS)
    #define NUM9    LSFT(KC_6)
    #define NUM0    LSFT(KC_7)

    //Others
    #define _______ KC_TRNS
    #define XXXXXXX KC_NO
    #define LSHIFT  LSFT_T(KC_CAPS)     //Hold = Shift, Tap = Caps
    #define COPY    LCTL(KC_I)
    #define PASTE   LCTL(KC_DOT)
    #define CUT     LCTL(KC_B)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base (Programmer's DVORAK)
   *          ,-------------------------------------------------.      ,-------------------------------------------------.
   *          | ESC  |   1  |   2  |   3  |   4  |   5  |   6   |      |   7   |   8  |   9  |   0  |   -  |   =  | BkSp |
   *          |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *          | Tab  |   Q  |   W  |   E  |   R  |   T  |PrtScn |      |  Del  |   Y  |   U  |   I  |   O  |   P  |   \  |
   *          |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *          |(TT)FN|   A  |   S  |   D  |   F  |   G  |LT1-F13|      |LT1-F13|   H  |   J  |   K  |   L  |   ;  |   '  |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *          |Sh/CL |   Z  |   X  |   C  |   V  |   B  | L_OS  |      |  R_OS |   N  |   M  |   ,  |   .  |   /  |Shift |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *          | Ctrl | Grave|   [  |   ]  | Alt  | Space| Home  |      |  PgUp | Enter| Left |  Up  | Down | Right| Ctrl |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------'
   *                                             | Space| End   |      | PgDwn | Enter|
   *                                             `--------------'      `--------------'
   */
  [_BASE] = LAYOUT( \
    KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,         KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_PSCR,       KC_DEL,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
   TT(_FN),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    FN13,         FN13,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
    LSHIFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LGUI,      KC_RGUI,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \
   KC_LCTL,  KC_GRV, KC_LBRC, KC_RBRC, KC_LALT,  KC_SPC, KC_HOME,      KC_PGUP,  KC_ENT, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, KC_RCTL, \
                                                 KC_SPC,  KC_END,      KC_PGDN,  KC_ENT, \
  ),

  /* Function
   *                             Mouse Control                                                Numpad
   *          ,-------------------------------------------------.      ,-------------------------------------------------.
   *          | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6   |      |  F7   |  F8  |  F9  |  F10 |  F11 |  F12 | BkSp |
   *          |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *          | Tab  |  N/A | WhLft|  MUp | WhRh | WhUp |PrtScn |      |  Del  |   *  |   7  |   8  |   9  |   /  |  N/A |
   *          |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *          |(TT)FN|Mouse2| MLft | MDwn | MRht | WhDn |LT1-F13|      |LT1-F13|   +  |   4  |   5  |   6  |   -  |  N/A |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *          |Sh/CL |  N/A |Mouse4|  N/A |Mouse5|  N/A | L_OS  |      |  R_OS |  N/A |   1  |   2  |   3  |  N/A |  N/A |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *          | Ctrl |Accel0|Accel1|Accel2| Alt  |Mouse1| Paste |      | Paste | Enter|   0  |  00  |   .  |  N/A |  SYS |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------'
   *                                             |Mouse1| Copy  |      |  Cut  | Enter|
   *                                             `--------------'      `--------------'
   */
  [_FN] = LAYOUT( \
   _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, \
   _______, XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, _______,      _______,    KC_7,    NUM7,    NUM8,    NUM9, KC_LBRC, XXXXXXX, \
   _______, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,      _______,    KC_9,    NUM4,    NUM5,    NUM6, KC_QUOT, XXXXXXX, \
   _______, XXXXXXX, KC_BTN4, XXXXXXX, KC_BTN5, XXXXXXX, _______,      _______, XXXXXXX,    NUM1,    NUM2,    NUM3, XXXXXXX, XXXXXXX, \
   _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, KC_BTN1,   PASTE,        PASTE, _______,    NUM0,   NUM00,    KC_E, XXXXXXX,     SYS, \
                                                KC_BTN1,    COPY,          CUT, _______, \
  ),

  /* System
   *                              RGB Control
   *          ,-------------------------------------------------.      ,-------------------------------------------------.
   *          |RGBRST|  N/A |  N/A |  N/A |  N/A |  N/A |  N/A  |      |  N/A  |  N/A |  N/A |  N/A |  N/A |  N/A | Reset|
   *          |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *          |  N/A |Hue - |Sat - |Sat + |Hue + |  N/A |  N/A  |      |  N/A  |  N/A |  N/A |  N/A |  N/A |  N/A |  N/A |
   *          |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *          |(TT)FN| Br - |Spd - |Spd + | Br + |  N/A |LT1-F13|      |LT1-F13|  N/A |  N/A |  N/A |  N/A |  N/A |  I/O |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *          |  N/A |Static|Breath|Rainb |Swirl |  N/A |  N/A  |      |  N/A  |  N/A |  N/A |  N/A |  N/A |  N/A |  N/A |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *          |  N/A |Snake |Knight| Xmas | Grad |On/Off|  N/A  |      |  N/A  |  N/A |  N/A |  N/A |  N/A |  N/A |  SYS |
   *          |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------'
   *                                             |On/Off|  N/A  |      |  N/A  |  N/A |
   *                                             `--------------'      `--------------'
   */
  [_SYS] = LAYOUT( \
    RGBRST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   RESET, \
   XXXXXXX, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   _______, RGB_VAD, RGB_SPD, RGB_SPI, RGB_VAI, XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_PWR, \
   XXXXXXX, RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
   XXXXXXX,RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_TOG, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
                                                RGB_TOG, XXXXXXX,      XXXXXXX, XXXXXXX, \
  ),

// For RGBRST Keycode
#if defined(RGB_MATRIX_ENABLE)
void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}

void rgb_matrix_decrease_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}
#endif

//Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t reset_timer;
  switch (keycode) {
    case RGBRST:
#if defined(RGBLIGHT_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
#elif defined(RGB_MATRIX_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
        }
#endif
      return false;
    case RESET:
      if (record->event.pressed) {
          reset_timer = timer_read();
      } else {
          if (timer_elapsed(reset_timer) >= 500) {
              reset_keyboard();
          }
      }
      return false;
#if defined(RGB_MATRIX_ENABLE) && defined(KEYBOARD_rgbkb_sol_rev2)
    case RGB_TOG:
      if (record->event.pressed) {
        rgb_matrix_increase_flags();
      }
      return false;
#endif
    case NUM00:
      if (record->event.pressed) {
        // when keycode NUM00 is pressed
        SEND_STRING("&&"); //Sends "00"
      } else {
        // when keycode NUM00 is released
      }
      return false;
  }
  return true;
}
