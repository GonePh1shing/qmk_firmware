#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _BASE = 0,
    _FN,
    _GAME,
    _SYS
};

// Keycode defines for layers
#define GAME    TG(_GAME)        //Toggle game layer
#define FN      MO(_FN)          //Function layer
#define SYS     MO(_SYS)         //System layer
#define FN13    LT(_FN,KC_F13)   //FN layer tap 'F13'

//Keycode defines for FN numpad
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

//Other misc keycode defines
#define LSHIFT  LSFT_T(KC_CAPS)

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  RGB_MENU
};

#define FN_ESC   LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base (Programmer's DVORAK)
   *            ,-------------------------------------------------.       ,-------------------------------------------------.
   *            | ESC  |   1  |   2  |   3  |   4  |   5  |   6   |       |   7   |   8  |   9  |   0  |   -  |   =  | BkSp |
   *            |------+------+------+------+------+------|-------|       |-------|------+------+------+------+------+------|
   *            | Tab  |   Q  |   W  |   E  |   R  |   T  |PrtScn |       |  Del  |   Y  |   U  |   I  |   O  |   P  |   \  |
   *            |------+------+------+------+------+------|-------|       |-------|------+------+------+------+------+------|
   *            |(TT)FN|   A  |   S  |   D  |   F  |   G  |LT1-F13|       |LT1-F13|   H  |   J  |   K  |   L  |   ;  |   '  |
   *            |------+------+------+------+------+------+-------|       |-------+------+------+------+------+------+------|
   *            |Sh/CL |   Z  |   X  |   C  |   V  |   B  | L_OS  |       |  R_OS |   N  |   M  |   ,  |   .  |   /  |Shift |
   *            |------+------+------+------+------+------+-------|       |-------+------+------+------+------+------+------|
   *            | Ctrl | Grave|   [  |   ]  | Alt  | Space| Home  |       |  PgUp | Enter| Left |  Up  | Down | Right| Ctrl |
   *            |------+------+------+------+------+------+-------|       |-------+------+------+------+------+------+------'
   *                                               | Space| End   |       | PgDwn | Enter|
   *                                               `--------------'       `--------------'
   */

  [_BASE] = LAYOUT( \
    KC_ESC,    KC_1,     KC_2,     KC_3,    KC_4,    KC_5,     KC_6,         KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, \
    KC_TAB,    KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,  KC_PSCR,       KC_DEL,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
   TT(_FN),    KC_A,     KC_S,     KC_D,    KC_F,    KC_G,     FN13,         FN13,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
    LSHIFT,    KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,  KC_LGUI,      KC_RGUI,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \
   KC_LCTL,  KC_GRV,  KC_LBRC,  KC_RBRC, KC_LALT,  KC_SPC,  KC_HOME,      KC_PGUP,  KC_ENT, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, KC_RCTL, \
                                                   KC_SPC,   KC_END,      KC_PGDN,  KC_ENT, \
  ),

  /* Function
   *            ,-------------------------------------------------.      ,-------------------------------------------------.
   *            | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6   |      |  F7   |  F8  |  F9  |  F10 |  F11 |  F12 | BkSp |
   *            |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *            | Tab  | WhLft|  MUp | WhRh | WhUp |  N/A |PrtScn |      |  Del  |   Y  |   U  |   I  |   O  |   [  |  N/A |
   *            |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *            |(TT)FN| MLft | MDwn | MRht | WhDn |  N/A |LT1-F13|      |LT1-F13|   H  |   J  |   K  |   L  |   '  |  N/A |
   *            |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *            |Sh/CL |  N/A |  N/A |  N/A |  N/A |  N/A | L_OS  |      |  R_OS |   N  |   M  |   ,  |   .  |  N/A |  N/A |
   *            |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *            |Mouse2|Accel0|Accel1|Accel2| Alt  |Mouse1| Paste |      | Paste | SH(7)| Left |  Up  | Down | Right|  SYS |
   *            |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------'
   *                                               |Mouse1| Copy  |      |  Cut  | SH(7)|
   *                                               `--------------'      `--------------'
   */
  [_FN] = LAYOUT( \
     KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_TRNS, \
     KC_TRNS, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,   KC_NO, KC_TRNS,      KC_TRNS,     KC_7,    NUM7,    NUM8,    NUM9, KC_LBRC,   KC_NO, \
     KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,   KC_NO, KC_TRNS,      KC_TRNS,     KC_9,    NUM4,    NUM5,    NUM6, KC_QUOT,   KC_NO, \
     KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS,      KC_TRNS,     KC_E,    NUM1,    NUM2,    NUM3,   KC_NO,   KC_NO,
     KC_BTN2, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_BTN1, KC_PSTE,      KC_PSTE,     NUM0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     SYS,
                                                  KC_BTN1, KC_COPY,       KC_CUT,     NUM0, \
  ),

  /* System
   *            ,-------------------------------------------------.      ,-------------------------------------------------.
   *            | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6   |      |  F7   |  F8  |  F9  |  F10 |  F11 |  F12 | BkSp |
   *            |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *            | Tab  | WhLft|  MUp | WhRh | WhUp |  N/A |PrtScn |      |  Del  |   Y  |   U  |   I  |   O  |   [  |  N/A |
   *            |------+------+------+------+------+------|-------|      |-------|------+------+------+------+------+------|
   *            |(TT)FN| MLft | MDwn | MRht | WhDn |  N/A |LT1-F13|      |LT1-F13|   H  |   J  |   K  |   L  |   '  |  N/A |
   *            |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *            |Sh/CL |  N/A |  N/A |  N/A |  N/A |  N/A | L_OS  |      |  R_OS |   N  |   M  |   ,  |   .  |  N/A |  N/A |
   *            |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------|
   *            |Mouse2|Accel0|Accel1|Accel2| Alt  |Mouse1| Paste |      | Paste | SH(7)| Left |  Up  | Down | Right|  SYS |
   *            |------+------+------+------+------+------+-------|      |-------+------+------+------+------+------+------'
   *                                               |Mouse1| Copy  |      |  Cut  | SH(7)|
   *                                               `--------------'      `--------------'
   */
  [_SYS] = LAYOUT( \
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET, \
       KC_NO, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
     KC_TRNS, RGB_VAD, RGB_SPD, RGB_SPI, RGB_VAI,   KC_NO, KC_TRNS,      KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
       KC_NO, RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, \
       KC_NO,RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_TOG,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS, \
                                                  RGB_TOG,   KC_NO,        KC_NO,   KC_NO, \
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

#ifdef RGB_OLED_MENU
uint8_t rgb_encoder_state = 4;

typedef void (*rgb_matrix_f)(void);

const rgb_matrix_f rgb_matrix_functions[6][2] = {
    { rgb_matrix_increase_hue, rgb_matrix_decrease_hue },
    { rgb_matrix_increase_sat, rgb_matrix_decrease_sat },
    { rgb_matrix_increase_val, rgb_matrix_decrease_val },
    { rgb_matrix_increase_speed, rgb_matrix_decrease_speed },
    { rgb_matrix_step, rgb_matrix_step_reverse },
    { rgb_matrix_increase_flags, rgb_matrix_decrease_flags }
};
#endif

#ifdef ENCODER_ENABLE

static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a)/sizeof(pin_t))

const uint16_t PROGMEM encoders[][NUMBER_OF_ENCODERS * 2][2]  = {
    [_QWERTY] = ENCODER_LAYOUT( \
        KC_VOLU, KC_VOLD,
        KC_VOLU, KC_VOLD
    ),
    [_COLEMAK] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    ),
    [_FN] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    ),
    [_ADJ] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (!is_keyboard_master())
    return;

#ifdef RGB_OLED_MENU
  if (index == RGB_OLED_MENU) {
    (*rgb_matrix_functions[rgb_encoder_state][clockwise])();
  } else
#endif
  {
    uint8_t layer = biton32(layer_state);
    uint16_t keycode = pgm_read_word(&encoders[layer][index][clockwise]);
    while (keycode == KC_TRANSPARENT && layer > 0)
    {
      layer--;
      if ((layer_state & (1 << layer)) != 0)
          keycode = pgm_read_word(&encoders[layer][index][clockwise]);
    }
    if (keycode != KC_TRANSPARENT)
      tap_code16(keycode);
  }
}
#endif

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
    case RGB_MENU:
#ifdef RGB_OLED_MENU
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          rgb_encoder_state = (rgb_encoder_state - 1);
          if (rgb_encoder_state > 5) {
            rgb_encoder_state = 5;
          }
        } else {
          rgb_encoder_state = (rgb_encoder_state + 1) % 6;
        }
      }
#endif
      return false;
  }
  return true;
}

// OLED Driver Logic
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;
  return OLED_ROTATION_180;
}

static void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
  };
  oled_write_P(sol_logo, false);
}

static void render_status(void) {
  // Render to mode icon
  static const char PROGMEM sol_icon[] = {
    0x9b,0x9c,0x9d,0x9e,0x9f,
    0xbb,0xbc,0xbd,0xbe,0xbf,
    0xdb,0xdc,0xdd,0xde,0xdf,0
  };
  oled_write_P(sol_icon, false);

  // Define layers here
  oled_write_P(PSTR("Layer"), false);
  uint8_t layer = layer_state ? biton(layer_state) : biton32(default_layer_state);
  switch (layer) {
    case _QWERTY:
      oled_write_P(PSTR("BASE "), false);
      break;
    case _COLEMAK:
      oled_write_P(PSTR("CLMK "), false);
      break;
    case _FN:
      oled_write_P(PSTR("FN   "), false);
      break;
    case _ADJ:
      oled_write_P(PSTR("ADJ  "), false);
      break;
    default:
      oled_write_P(PSTR("UNDEF"), false);
  }

  // Host Keyboard LED Status
    uint8_t led_state = host_keyboard_leds();
    oled_write_P(PSTR("-----"), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUMLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false);

#ifdef RGB_OLED_MENU
    static char buffer[31] = { 0 };
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d e%3d ", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode, rgb_matrix_get_flags());
    buffer[4 + rgb_encoder_state * 5] = '<';

    oled_write_P(PSTR("-----"), false);
    oled_write(buffer, false);
#endif
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
}

#endif
