#include QMK_KEYBOARD_H
#include <stdio.h>
#include "swapper.h"
#include "enums.h"

// OLED setup
#define IDLE_FRAMES 5
#define IDLE_SPEED 30
#define TAP_FRAMES 2
#define TAP_SPEED 20
#define ANIM_FRAME_DURATION 200
#define ANIM_SIZE 512

bool gui_on = true;
char wpm_str[10];
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;

static long int oled_timeout = 600000; // 10 minutes

#define _COLEMAK 0
#define _COLEWIN 1
#define _MOD 2
#define _MODWIN 3
#define _FUNC 4
#define _FUNCWIN 5
#define _MOUSE 6
#define _MOUSEWIN 7

#define COLEMAK TO(_COLEMAK)
#define COLEWIN TO(_COLEWIN)
#define MOD MO(_MOD)
#define MODWIN MO(_MODWIN)
#define FUNC MO(_FUNC)
#define FUNCWIN MO(_FUNCWIN)
#define MOUSE MO(_MOUSE)
#define MOUSEWIN MO(_MOUSEWIN)
#define DEV MO(_DEV)
#define DEVWIN MO(_DEVWIN)

//tap dance
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
//-tap dance


void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
// #ifndef PERMISSIVE_HOLD //commented out to stop triggering hold when typing fast
            && !state->interrupted
// #endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


qk_tap_dance_action_t tap_dance_actions[] = {
  //mac ones
  //left
    [TD_Q]      = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, RCMD(KC_Q)),
    [TD_W]      = ACTION_TAP_DANCE_TAP_HOLD(KC_W, RCMD(KC_W)),
    [TD_F]      = ACTION_TAP_DANCE_TAP_HOLD(KC_F, RCMD(KC_F)),
    [TD_P]      = ACTION_TAP_DANCE_TAP_HOLD(KC_P, RCMD(KC_P)),
    [TD_B]      = ACTION_TAP_DANCE_TAP_HOLD(KC_B, RCMD(KC_B)),
    [TD_A]      = ACTION_TAP_DANCE_TAP_HOLD(KC_A, RCMD(KC_A)),
    [TD_R]      = ACTION_TAP_DANCE_TAP_HOLD(KC_R, RCMD(KC_R)),
    [TD_S]      = ACTION_TAP_DANCE_TAP_HOLD(KC_S, RCMD(KC_S)),
    [TD_T]      = ACTION_TAP_DANCE_TAP_HOLD(KC_T, RCMD(KC_T)),
    [TD_G]      = ACTION_TAP_DANCE_TAP_HOLD(KC_G, RCMD(KC_G)),
    [TD_C]      = ACTION_TAP_DANCE_TAP_HOLD(KC_C, RCMD(KC_C)),
    [TD_Z]      = ACTION_TAP_DANCE_TAP_HOLD(KC_Z, RCMD(KC_Z)),
    [TD_X]      = ACTION_TAP_DANCE_TAP_HOLD(KC_X, RCMD(KC_X)),
    [TD_D]      = ACTION_TAP_DANCE_TAP_HOLD(KC_D, RCMD(KC_D)),
    [TD_V]      = ACTION_TAP_DANCE_TAP_HOLD(KC_V, RCMD(KC_V)),
    //right
    [TD_J]      = ACTION_TAP_DANCE_TAP_HOLD(KC_J, KC_LPRN),
    [TD_L]      = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_RPRN),
    [TD_U]      = ACTION_TAP_DANCE_TAP_HOLD(KC_U, KC_LCBR),
    [TD_Y]      = ACTION_TAP_DANCE_TAP_HOLD(KC_Y, KC_RCBR),
    [TD_M]      = ACTION_TAP_DANCE_TAP_HOLD(KC_M, KC_AT),
    [TD_N]      = ACTION_TAP_DANCE_TAP_HOLD(KC_N, KC_MINS),
    [TD_E]      = ACTION_TAP_DANCE_TAP_HOLD(KC_E, KC_EQL),
    [TD_K]      = ACTION_TAP_DANCE_TAP_HOLD(KC_K, RCMD(KC_K)),
    [TD_H]      = ACTION_TAP_DANCE_TAP_HOLD(KC_H, KC_EXLM),
    [TD_QUO]    = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOT, KC_DQT),
    [TD_SCLN]    = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, KC_COLN),
    [TD_LBR]    = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_LBRC),
    [TD_RBR]    = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, KC_RBRC),
    [TD_DELW]    = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, LALT(KC_BSPC)),

  //windows
   //left
   [TD_WQ]      = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, C(KC_Q)),
   [TD_WW]      = ACTION_TAP_DANCE_TAP_HOLD(KC_W, C(KC_W)),
   [TD_WF]      = ACTION_TAP_DANCE_TAP_HOLD(KC_F, C(KC_F)),
   [TD_WP]      = ACTION_TAP_DANCE_TAP_HOLD(KC_P, C(KC_P)),
   [TD_WB]      = ACTION_TAP_DANCE_TAP_HOLD(KC_B, C(KC_B)),
   [TD_WA]      = ACTION_TAP_DANCE_TAP_HOLD(KC_A, C(KC_A)),
   [TD_WR]      = ACTION_TAP_DANCE_TAP_HOLD(KC_R, C(KC_R)),
   [TD_WS]      = ACTION_TAP_DANCE_TAP_HOLD(KC_S, C(KC_S)),
   [TD_WT]      = ACTION_TAP_DANCE_TAP_HOLD(KC_T, C(KC_T)),
   [TD_WG]      = ACTION_TAP_DANCE_TAP_HOLD(KC_G, C(KC_G)),
   [TD_WC]      = ACTION_TAP_DANCE_TAP_HOLD(KC_C, C(KC_C)),
   [TD_WZ]      = ACTION_TAP_DANCE_TAP_HOLD(KC_Z, C(KC_Z)),
   [TD_WX]      = ACTION_TAP_DANCE_TAP_HOLD(KC_X, C(KC_X)),
   [TD_WD]      = ACTION_TAP_DANCE_TAP_HOLD(KC_D, C(KC_D)),
   [TD_WV]      = ACTION_TAP_DANCE_TAP_HOLD(KC_V, C(KC_V)),
   [TD_WJ]      = ACTION_TAP_DANCE_TAP_HOLD(KC_J, KC_LPRN),
   [TD_WL]      = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_RPRN),
   [TD_WU]      = ACTION_TAP_DANCE_TAP_HOLD(KC_U, KC_LCBR),
   [TD_WY]      = ACTION_TAP_DANCE_TAP_HOLD(KC_Y, KC_RCBR),
   [TD_WM]      = ACTION_TAP_DANCE_TAP_HOLD(KC_M, KC_AT),
   [TD_WN]      = ACTION_TAP_DANCE_TAP_HOLD(KC_N, KC_MINS),
   [TD_WE]      = ACTION_TAP_DANCE_TAP_HOLD(KC_E, KC_EQL),
   [TD_WK]      = ACTION_TAP_DANCE_TAP_HOLD(KC_K, C(KC_K)),
   [TD_WH]      = ACTION_TAP_DANCE_TAP_HOLD(KC_H, KC_EXLM),
   [TD_WQUO]    = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOT, KC_DQT),
   [TD_WSCLN]    = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, KC_COLN),
   [TD_WLBR]    = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_LBRC),
   [TD_WRBR]    = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, KC_RBRC),
   [TD_WDELW]    = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, LCTL(KC_BSPC)),

};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Enter|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |MOUSE |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|FDELETE|    |  Win  |------+------+------+------+------+------|
 * |L Ctrl|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Lctr | Mod  | / LShift/       \Space \  |RAISE | Menu |   ~  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT(
      KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,        KC_9,       KC_0,  KC_BSPC,
      KC_TAB,TD(TD_Q),TD(TD_W),TD(TD_F),TD(TD_P),TD(TD_B),                             TD(TD_J),TD(TD_L),TD(TD_U),    TD(TD_Y),TD(TD_SCLN),   KC_ENT,
  MO(_MOUSE),TD(TD_A),TD(TD_R),    KC_S,TD(TD_T),TD(TD_G),                             TD(TD_M),TD(TD_N),TD(TD_E),      KC_I  ,       KC_O,TD(TD_QUO),
     KC_LCTL,TD(TD_Z),TD(TD_X),TD(TD_C),TD(TD_D),TD(TD_V),  TD(TD_DELW),     COLEWIN,  TD(TD_K),TD(TD_H),TD(TD_LBR),TD(TD_RBR),    KC_SLSH,KC_BSLASH,
                                KC_LALT, KC_LCMD,    MOD ,  OSM(KC_LSFT),          KC_SPC,     FUNC , KC_APPLICATION, S(KC_NONUS_HASH)
),
/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Enter|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |MOUSE |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|FDELETE|    |  COLE |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Lctr | Lower| / LShift/       \Space \  |RAISE | Menu |   ~  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEWIN] = LAYOUT(
      KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                            KC_6,     KC_7,     KC_8,         KC_9,        KC_0,    KC_BSPC,
      KC_TAB,TD(TD_WQ),TD(TD_WW),TD(TD_WF),TD(TD_WP),TD(TD_WB),                       TD(TD_WJ),TD(TD_WL),TD(TD_WU),    TD(TD_WY),TD(TD_WSCLN),     KC_ENT,
    MOUSEWIN,TD(TD_WA),TD(TD_WR),     KC_S,TD(TD_WT),TD(TD_WG),                       TD(TD_WM),TD(TD_WN),TD(TD_WE),       KC_I  ,        KC_O,TD(TD_WQUO),
     KC_LSFT,TD(TD_WZ),TD(TD_WX),TD(TD_WC),TD(TD_WD),TD(TD_WV),  KC_DELETE,   COLEMAK,TD(TD_WK),TD(TD_WH),TD(TD_WLBR),TD(TD_WRBR),     KC_SLSH,  KC_BSLASH,
                                   KC_LALT,  KC_LCTL,   MODWIN,   OSM(KC_LSFT),    KC_SPC,   FUNCWIN, KC_APPLICATION, S(KC_NONUS_HASH)
),
/* MOD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |Alt&F4|W_BACK|W Tab | W_FOR|      |                    | PGUP | HOME |  UP  |  END |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | P_TAB|N_WIN | N_TAB|      |-------.    ,-------| PGDN | LEFT | DOWN |RIGHT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | W CLS|      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_MOD] = LAYOUT(
  KC_TILD,     KC_F1,        KC_F2,     KC_F3,        KC_F4,     KC_F5,                         KC_F6,     KC_F7,     KC_F8,    KC_F9, KC_F10, KC_F11,
   KC_GRV,LCMD(KC_Q),LCMD(KC_LBRC),LCMD(KC_T),LCMD(KC_RBRC),S(KC_BSLS),                       KC_PGUP,   KC_HOME,     KC_UP,   KC_END,KC_DEL , KC_F12,
  _______,   _______,SCMD(KC_LBRC),  MC_SWMAC,SCMD(KC_RBRC),MC_IDEASWAPM,                       KC_PGDN,   KC_LEFT,   KC_DOWN, KC_RIGHT,KC_INS ,_______,
  _______,LCMD(KC_GRV),    _______,LCMD(KC_W),      _______,   _______, _______,     _______, _______,S(KC_LBRC),S(KC_RBRC),  KC_LBRC,KC_RBRC,_______,
                             KC_LALT, KC_LEFT_CTRL,            _______, _______,     LCMD(KC_SPC), _______, _______, _______
),
/* MODWIN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |Alt&F4|W_BACK|W Tab | W_FOR|      |                    | PGUP | HOME |  UP  |  END |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | P_TAB|N_WIN | N_TAB|      |-------.    ,-------| PGDN | LEFT | DOWN |RIGHT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | W CLS|      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_MODWIN] = LAYOUT(
  KC_TILD,      KC_F1,        KC_F2,     KC_F3,         KC_F4,     KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
   KC_GRV,LALT(KC_F4),LALT(KC_LEFT),LCTL(KC_T),LALT(KC_RIGHT),S(KC_BSLS),                         KC_PGUP,   KC_HOME,     KC_UP,   KC_END,KC_DEL , KC_F12,
  _______,    _______,LCTL(KC_PGUP),  MC_SWWIN, LCTL(KC_PGDN),MC_IDEASWAPW,                         KC_PGDN, KC_LEFT,   KC_DOWN, KC_RIGHT,KC_INS ,_______,
  _______,    _______,      _______, LCTL(KC_W),      _______,    KC_GRV, _______,       _______, _______,S(KC_LBRC),S(KC_RBRC),  KC_LBRC,KC_RBRC,_______,
                           _______, _______,        _______, _______,                    KC_LWIN, _______, _______, _______
),
/* FUNC
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |  (   |   )  |   {  |   }  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|   @  |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   !  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_FUNC] = LAYOUT(
  _______, _______, _______, _______,      _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,      _______, _______,                     KC_MSTP,KC_MPLY,KC_VOLU,_______,  LCA(KC_U),     LCA(KC_I),
  _______, _______, _______, _______,      _______, _______,                     KC_MSEL,KC_MPRV,KC_VOLD,KC_MNXT,LCA(KC_LEFT),LCA(KC_RIGHT),
  _______, _______, _______, _______,      _______, _______,  _______, _______,  _______,_______,_______,_______,   LCA(KC_J),    LCA(KC_K),
                             KC_LALT, KC_LEFT_CTRL, _______,  _______, _______,  _______, _______, _______
),
/* FUNCWIN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |  (   |   )  |   {  |   }  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|   @  |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   !  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_FUNCWIN] = LAYOUT(
  _______, _______, _______, _______,      _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,      _______, _______,                     KC_MSTP,KC_MPLY,KC_VOLU,_______,  LWIN(KC_UP),     _______,
  _______, _______, _______, _______,      _______, _______,                     KC_MSEL,KC_MPRV,KC_VOLD,KC_MNXT,LWIN(KC_LEFT),LWIN(KC_RIGHT),
  _______, _______, _______, _______,      _______, _______,  _______, _______,  KC_EJCT,_______,_______,_______,   LWIN(KC_DOWN),   _______,
                             KC_LALT, KC_LEFT_CTRL, _______,  _______, _______,  _______, _______, _______
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
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MS_WH_DOWN, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, XXXXXXX,          KC_MS_WH_UP, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, KC_MS_ACCEL2, KC_MS_ACCEL0, _______, _______,  _______, _______, _______
    ),

    /* MOUSEWIN
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
      [_MOUSEWIN] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MS_WH_UP, KC_MS_WH_LEFT, KC_MS_UP, KC_MS_WH_RIGHT, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, XXXXXXX,          KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 _______, KC_MS_ACCEL2, KC_MS_ACCEL0, _______, _______,  _______, _______, _______
      )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Process swapper
    switch (process_swapper(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };

    qk_tap_dance_action_t *action;
    switch (keycode) {
      case TD(TD_Q):
      case TD(TD_W):
      case TD(TD_F):
      case TD(TD_P):
      case TD(TD_B):
      case TD(TD_A):
      case TD(TD_R):
      case TD(TD_S):
      case TD(TD_T):
      case TD(TD_G):
      case TD(TD_C):
      case TD(TD_Z):
      case TD(TD_X):
      case TD(TD_D):
      case TD(TD_V):
      case TD(TD_J):
      case TD(TD_L):
      case TD(TD_U):
      case TD(TD_Y):
      case TD(TD_M):
      case TD(TD_N):
      case TD(TD_E):
      case TD(TD_K):
      case TD(TD_H):
      case TD(TD_QUO):
      case TD(TD_SCLN):
      case TD(TD_LBR):
      case TD(TD_RBR):
      case TD(TD_DELW):
      case TD(TD_WQ):
      case TD(TD_WW):
      case TD(TD_WF):
      case TD(TD_WP):
      case TD(TD_WB):
      case TD(TD_WA):
      case TD(TD_WR):
      case TD(TD_WS):
      case TD(TD_WT):
      case TD(TD_WG):
      case TD(TD_WC):
      case TD(TD_WZ):
      case TD(TD_WX):
      case TD(TD_WD):
      case TD(TD_WV):
      case TD(TD_WJ):
      case TD(TD_WL):
      case TD(TD_WU):
      case TD(TD_WY):
      case TD(TD_WM):
      case TD(TD_WN):
      case TD(TD_WE):
      case TD(TD_WK):
      case TD(TD_WH):
      case TD(TD_WQUO):
      case TD(TD_WSCLN):
      case TD(TD_WLBR):
      case TD(TD_WRBR):
      case TD(TD_WDELW):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _MOD, _FUNC, _DEV);
// }

//
// Rotate OLED display
//
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	if (!is_keyboard_master()) return OLED_ROTATION_180;
    else return rotation;
}

//
// Render left OLED display
//
static void render_status(void) {

    // WPM
    oled_write_P(PSTR("      "), false);
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write(wpm_str, false);
    oled_write_P(PSTR("   WPM"), false);

    // GUI keys indicator
    if (gui_on) oled_write_P(PSTR("\n       "), false);
    else oled_write_P(PSTR("\n      GUI   OFF"), false);

    // Caps lock indicator
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("\n      CAPS LOCK") : PSTR("\n       "), false);

    // Layer indicator
    oled_write_P(PSTR("\n      LAYER "), false);

    switch (get_highest_layer(layer_state)) {
        case 1:
          oled_write_P(PSTR("COLEWIN "), false);
        break;
        case 2:
           oled_write_P(PSTR("MOD     "), false);
        break;
        case 3:
           oled_write_P(PSTR("MODWIN  "), false);
        break;
        case 4:
           oled_write_P(PSTR("FUNC    "), false);
        break;
        case 5:
           oled_write_P(PSTR("FUNCWIN "), false);
        break;
        case 6:
           oled_write_P(PSTR("MOUSE   "), false);
        break;
        case 7:
           oled_write_P(PSTR("MOUSWIN "), false);
        break;
        default:
          oled_write_P(PSTR("COLEMAK "), false);
        break;
    }
}

//
// Render right OLED display animation
//
static void render_anim(void) {

    // Idle animation
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,16,8,8,4,4,4,8,48,64,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,100,130,2,2,2,2,2,1,0,0,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,192,193,193,194,4,8,16,32,64,128,0,0,0,128,128,128,128,64,64,
            64,64,32,32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,56,4,3,0,0,0,0,0,0,0,12,12,12,13,1,0,64,160,33,34,18,17,17,17,9,8,8,8,8,4,4,8,8,16,16,16,16,16,17,15,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,1,1,1,2,2,4,4,8,8,8,8,8,7,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,16,8,8,4,4,4,8,48,64,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,100,130,2,2,2,2,2,1,0,0,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,192,193,193,194,4,8,16,32,64,128,0,0,0,128,128,128,128,64,64,
            64,64,32,32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,56,4,3,0,0,0,0,0,0,0,12,12,12,13,1,0,64,160,33,34,18,17,17,17,9,8,8,8,8,4,4,8,8,16,16,16,16,16,17,15,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,1,1,1,2,2,4,4,8,8,8,8,8,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,64,64,64,64,32,32,32,32,16,8,4,2,2,4,24,96,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,194,1,1,2,2,4,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,96,96,0,129,130,130,132,8,16,32,64,128,0,0,0,0,128,128,128,128,64,64,64,64,32,
            32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,112,25,6,0,0,0,0,0,0,0,24,24,24,27,3,0,64,160,34,36,20,18,18,18,11,8,8,8,8,5,5,9,9,16,16,16,16,16,17,15,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,1,1,1,2,2,4,4,8,8,8,8,8,7,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,8,4,2,1,1,2,12,48,64,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,225,0,0,1,1,2,2,1,0,0,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,192,193,193,194,4,8,16,32,64,128,0,0,0,128,128,128,128,64,64,
            64,64,32,32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,112,12,3,0,0,0,0,0,0,0,12,12,12,13,1,0,64,160,33,34,18,17,17,17,9,8,8,8,8,4,4,8,8,16,16,16,16,16,17,15,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,1,1,1,2,2,4,4,8,8,8,8,8,
            7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,8,8,4,2,2,2,4,56,64,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,226,1,1,2,2,2,2,1,0,0,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,192,193,193,194,4,8,16,32,64,128,0,0,0,128,128,128,128,64,64,64,64,
            32,32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,112,12,3,0,0,0,0,0,0,0,12,12,12,13,1,0,64,160,33,34,18,17,17,17,9,8,8,8,8,4,4,8,8,16,16,16,16,16,17,15,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,1,1,1,2,2,4,4,8,8,8,8,8,7,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        }

    };

    // Prep animation
    static const char PROGMEM prep[][ANIM_SIZE] = {

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,8,4,2,1,1,2,12,48,64,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,225,0,0,1,1,2,2,129,128,128,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,0,1,225,26,6,9,49,53,1,138,124,0,0,128,128,128,128,64,64,
            64,64,32,32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,112,12,3,0,0,24,6,5,152,153,132,195,124,65,65,64,64,32,33,34,18,17,17,17,9,8,8,8,8,4,4,4,4,4,4,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        }

    };

    // Typing animation
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,8,4,2,1,1,2,12,48,64,128,0,0,0,0,0,0,0,248,248,248,248,0,0,0,0,0,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,225,0,0,1,1,2,2,129,128,128,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,0,1,1,2,4,8,16,32,67,135,7,1,0,184,188,190,159,
            95,95,79,76,32,32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,112,12,3,0,0,24,6,5,152,153,132,67,124,65,65,64,64,32,33,34,18,17,17,17,9,8,8,8,8,4,4,8,8,16,16,16,16,16,17,15,1,61,124,252,252,252,252,252,60,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,2,2,1,1,1,
            1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },

        {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,0,0,0,0,0,128,64,64,32,32,32,32,16,16,16,16,8,4,2,1,1,2,12,48,64,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,225,0,0,1,1,2,2,1,0,0,0,0,128,128,0,0,0,0,0,0,0,0,0,128,0,48,48,0,0,1,225,26,6,9,49,53,1,138,124,0,0,128,128,128,128,64,64,64,64,32,
            32,32,32,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,112,12,3,0,0,0,0,0,0,0,0,0,0,1,1,0,64,160,33,34,18,17,17,17,9,8,8,8,8,4,4,4,4,4,4,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,64,64,64,64,64,32,32,32,32,32,16,16,16,16,16,8,8,8,8,8,4,4,4,4,4,2,3,122,122,121,121,121,121,57,49,2,2,4,4,8,8,8,136,136,135,128,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        }

    };

    void animation_phase(void) {

        if (get_current_wpm() <=IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES-1)-current_idle_frame)], ANIM_SIZE);
        }

        if (get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED) {
            oled_write_raw_P(prep[0], ANIM_SIZE);
        }

        if (get_current_wpm() >=TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
        }
    }

    if (get_current_wpm() != 000) {
        oled_on();

        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }

        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > oled_timeout) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

//
// OLED display rendering
//
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Left side
        render_status();
    } else {
        // Right side
        render_anim();
    }

	return 0;
}
