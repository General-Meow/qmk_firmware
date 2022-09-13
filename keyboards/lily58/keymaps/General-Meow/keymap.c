#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _MOUSE 4

/*
enum layer_number {
  _COLEMAK = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
};
*/

// Enums defined for all examples:
enum {
    TD_ESC_CAPS,
    CT_EGG,
    CT_FLSH,
    CT_CLN,
    X_CTL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Enter|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |MOUSE |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|FDELETE|    |   `   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Lctr | Lower| / LShift/       \Space \  |RAISE | Menu |   ~  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT(
      KC_ESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
      KC_TAB,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,   KC_ENT,
  MO(_MOUSE),  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                        KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
     KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,  KC_DELETE,   KC_GRV,   KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_NONUS_BACKSLASH,
                      KC_LALT, KC_LEFT_CTRL, MO(_LOWER), KC_LSFT, KC_SPC, MO(_RAISE), KC_APPLICATION, S(KC_NONUS_HASH)
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |      |W_BACK|W Tab | W_FOR|      |                    | PGUP | HOME |  UP  |  END |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | P_TAB|N_WIN | N_TAB|      |-------.    ,-------| PGDN | LEFT | DOWN |RIGHT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | W CLS|      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
   KC_F1,    KC_F2,         KC_F3,        KC_F4,          KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV,  _______, LALT(KC_LEFT),   LCTL(KC_T), LALT(KC_RIGHT), _______,                   KC_PGUP, KC_HOME,   KC_UP,   KC_END, _______, _______,
  _______, _______, LCTL(KC_PGUP), LALT(KC_TAB),  LCTL(KC_PGDN), _______,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
  _______, _______,       _______,   LCTL(KC_W),        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |  (   |   )  |   {  |   }  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|   @  |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   !  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, _______,
  _______, _______, _______, _______, _______, _______,                       KC_AT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, _______,
  _______, _______, _______, _______, _______, _______,  _______, _______,  _______, KC_EXLM, _______, _______, _______, _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      | SH F6|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |CS F10|-------.    ,-------|      | A_INS|      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | MENU |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_F6),                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RCS(KC_F10),               XXXXXXX, LALT(KC_INSERT), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_APPLICATION, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
  /* MOUSE
   * ,---------------------------------------------------.                    ,------------------------------------------------------.
   * |      |      |         |         |         |       |                    |         |         |         |          |      |      |
   * |------+------+---------+---------+---------+-------|                    |---------+---------+---------+----------+------+------|
   * |      |      |         |         |         |       |                    | WH_UP   | WH_LEFT | MS_UP   | WH_RIGHT |      |      |
   * |------+------+---------+---------+---------+-------|                    |---------+---------+---------+----------+------+------|
   * |      |      | MS_BTN2 | MS_BTN3 | MS_BTN1 |       |-------.    ,-------| WH_DOWN | MS_LEFT | MS_DOWN | MS_RIGHT |      |      |
   * |------+------+---------+---------+---------+-------|       |    |       |---------+---------+---------+----------+------+------|
   * |      |      |         |         |         |       |-------|    |-------|         |         |         |          |      |      |
   * `--------------------------------------------/       /              \      \-------------------------------------------------------'
   *                   |      |MS ACC2 |MS ACC0| /       /                \      \  |      |      |      |
   *                   |      |        |       |/       /                  \      \ |      |      |      |
   *                   `----------------------------'                    '------''--------------------'
   */
    [_MOUSE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, XXXXXXX,          KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, KC_MS_ACCEL2, KC_MS_ACCEL0, _______, _______,  _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
  return true;
}
