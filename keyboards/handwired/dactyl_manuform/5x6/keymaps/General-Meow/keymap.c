#include QMK_KEYBOARD_H

#include "swapper.h"
#include "enums.h"

#define _COLEMAK 0
#define _COLEWIN 1
#define _MOD 2
#define _MODWIN 3
#define _FUNC 4
#define _FUNCWIN 5
#define _MOUSE 6
#define _MOUSEWIN 7
#define _DEV 8
#define _DEVWIN 9

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


#define IDEAUP SCMD(LOPT(KC_UP))
#define IDEAUPW MEH(KC_UP)
#define IDEADOWN SCMD(LOPT(KC_DOWN))
#define IDEADOWNW MEH(KC_DOWN)
#define IDEARIGHT SCMD(LOPT(KC_RIGHT))
#define IDEARIGHTW MEH(KC_RIGHT)
#define IDEALEFT SCMD(LOPT(KC_LEFT))
#define IDEALEFTW MEH(KC_LEFT)

#define IDEAIMPO LAG(KC_O) //IDEA Fix Imports
#define IDEAIMPW LCA(KC_O) //win IDEA fix imports
#define IDEAFOR LAG(KC_L)  //IDEA Reformat
#define IDEAFORW LCA(KC_L) //win IDEA reformat
#define IDEAREN S(KC_F6)   //IDEA Rename
#define IDEARENW S(KC_F6) //win IDEA Rename
#define IDEARUN RCS(KC_F10)//IDEA Run
#define IDEARUNW RCS(KC_F10) //win IDEA Run
#define IDEAIMPL LCMD(S(KC_B)) //IDEA see implementation
#define IDEAIMPLW LCTL(LALT(KC_B)) //win IDEA see implementation
#define IDEASPL LCMD(C(KC_S)) //IDEA Split move right



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
        if (state->count == 1 && !state->interrupted){
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
   * ,-------------------------------------------.                    ,-------------------------------------------.
   * |  Esc |   1  |   2  |   3  |   4   |   5   |                    |   6   |   7   |   8  |   9  |  0   | BDel |
   * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
   * |  Tab |  q   |   w  |  f   |   p   |   b   |                    |   j   |   l   |  u   |  y   |  ;   |  |   |
   * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
   * |  Mse |  a   |  r   |  s   |   t   |   g   |                    |   m   |   n   |  e   |  i   |  o   |  '   |
   * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
   * |  Sft |  z   |  x   |  c   |   d   |   v   |                    |   k   |   h   |  ,   |  .   |  /   |  \   |
   * `-------------------------------------------|                    |-------------------------------------------'
   *               |  Ctr |  Opt |                                                    |  Cmd |  Opt |
   *               |      |      |                                                    |      |      |
   *               `-------------|                                                    |-------------'
   *                             |---------------.                    ,---------------|
   *                             |  Mod  |  Sft  |                    |  Spc  |  Mod  |
   *                             |---------------|                    |---------------|
   *                             |  Cmd  |TD_Del |                    |  Ent  |  Mse  |
   *                             |---------------|                    |---------------|
   *                             |  Func |  Dev  |                    |  FDel |ColeWIN|
   *                             |---------------|                    |---------------|
   */
   // [_COLEMAK] = LAYOUT_5x6(
   //     KC_ESC,  KC_1   ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,             KC_6  ,  KC_7  ,  KC_8  ,    KC_9  ,     KC_0  ,KC_BSPC,
   //     KC_TAB ,TD(TD_Q),TD(TD_W),TD(TD_F),TD(TD_P),TD(TD_B),           TD(TD_J),TD(TD_L),TD(TD_U),  TD(TD_Y),TD(TD_SCLN),KC_PIPE,
   //     MOUSE  ,  KC_A  ,TD(TD_R),  KC_S  ,TD(TD_T),TD(TD_G),           TD(TD_M),TD(TD_N),TD(TD_E),    KC_I  ,       KC_O,TD(TD_QUO),
   //     KC_LSFT,TD(TD_Z),TD(TD_X),TD(TD_C),TD(TD_D),TD(TD_V),           TD(TD_K),TD(TD_H),TD(TD_LBR),TD(TD_RBR),   KC_SLSH,KC_BSLASH,
   //                       KC_LCTL,KC_LALT,                                                  KC_RCMD,KC_RALT,
   //                                             MOD, KC_LSFT,             KC_SPC,     MOD,
   //                                         KC_LGUI,TD(TD_DELW),          KC_ENT,   MOUSE,
   //                                            FUNC,     DEV,             KC_DEL, COLEWIN
   // ),
   [_COLEMAK] = LAYOUT_5x6(
       KC_ESC ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,             KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_BSPC,
       KC_TAB ,  KC_Q  ,  KC_W  ,  KC_F  ,  KC_P  ,  KC_B  ,             KC_J  ,  KC_L  ,  KC_U  ,  KC_Y  , KC_SCLN,KC_PIPE,
       MOUSE  ,  KC_A  ,  KC_R  ,  KC_S  ,  KC_T  ,  KC_G  ,             KC_M  ,  KC_N  ,  KC_E  ,  KC_I  ,  KC_O  ,KC_QUOT,
       KC_LSFT,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_D  ,  KC_V  ,             KC_K  ,  KC_H  , KC_COMM,  KC_DOT, KC_SLSH,KC_BSLASH,
                         KC_LCTL, KC_LALT,                                                KC_RCMD, KC_RALT,
                                               MOD, KC_LSFT,             KC_SPC,     MOD,
                                           KC_LGUI,TD(TD_DELW),          KC_ENT,   MOUSE,
                                              FUNC,     DEV,             KC_DEL, COLEWIN
   ),

    /* COLEMAK WINDOWS
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |  Esc |   1  |   2  |   3  |   4   |   5   |                    |   6   |   7   |   8  |   9  |  0   | BDel |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |  Tab |  q   |   w  |  f   |   p   |   b   |                    |   j   |   l   |  u   |  y   |  ;   |  |   |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |  Mse |  a   |  r   |  s   |   t   |   g   |                    |   m   |   n   |  e   |  i   |  o   |  '   |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |  Sft |  z   |  x   |  c   |   d   |   v   |                    |   k   |   h   |  ,   |  .   |  /   |  \   |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |  Ctr |  Alt |                                                    |  Cmd |  Opt |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |  ModW |  Sft  |                    |  Spc  | ModW  |
    *                             |---------------|                    |---------------|
    *                             |  Ctr  |TD_Del |                    |  Ent  | MseW  |
    *                             |---------------|                    |---------------|
    *                             |FuncWIN|DevWIN |                    |  FDel |Colemak|
    *                             |---------------|                    |---------------|
     */
    // [_COLEWIN] = LAYOUT_5x6(
    //     KC_ESC  ,   KC_1  ,   KC_2  ,   KC_3  ,   KC_4  ,   KC_5  ,              KC_6  ,   KC_7  ,   KC_8  ,   KC_9  ,      KC_0  , KC_BSPC,
    //     KC_TAB  ,TD(TD_WQ),TD(TD_WW),TD(TD_WF),TD(TD_WP),TD(TD_WB),           TD(TD_WJ),TD(TD_WL),TD(TD_WU),TD(TD_WY),TD(TD_WSCLN), KC_PIPE,
    //     MOUSEWIN,  KC_A  ,TD(TD_WR),  KC_S   ,TD(TD_WT),TD(TD_WG),           TD(TD_WM),TD(TD_WN),TD(TD_WE),   KC_I  ,        KC_O,TD(TD_WQUO),
    //     KC_LSFT ,TD(TD_WZ),TD(TD_WX),TD(TD_WC),TD(TD_WD),TD(TD_WV),           TD(TD_WK),TD(TD_WH),TD(TD_WLBR),TD(TD_WRBR), KC_SLSH,KC_BSLASH,
    //                          KC_LALT, KC_LCTL,                                                        KC_RCTL,    KC_RALT,
    //                                               MODWIN,  KC_LSFT,              KC_SPC,  MODWIN,
    //                                              KC_LCTL,TD(TD_WDELW),           KC_ENT,MOUSEWIN,
    //                                              FUNCWIN,   DEVWIN,              KC_DEL, COLEMAK
    // ),
    [_COLEWIN] = LAYOUT_5x6(
        KC_ESC  ,  KC_1  ,  KC_2 ,  KC_3  ,  KC_4  ,  KC_5,             KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_BSPC,
        KC_TAB  ,  KC_Q  ,  KC_W ,  KC_F  ,  KC_P  ,  KC_B,             KC_J  ,  KC_L  ,  KC_U  ,  KC_Y  , KC_SCLN, KC_PIPE,
        MOUSEWIN,  KC_A  ,  KC_R ,  KC_S  ,  KC_T  ,  KC_G,             KC_M  ,  KC_N  ,  KC_E  ,  KC_I  ,  KC_O  , KC_QUOT,
        KC_LSFT ,  KC_Z  ,  KC_X ,  KC_C  ,  KC_D  ,  KC_V,             KC_K  ,  KC_H  , KC_COMM,  KC_DOT, KC_SLSH,KC_BSLASH,
                          KC_LALT, KC_LCTL,                                              KC_RCTL, KC_RALT,
                                             MODWIN,  KC_LSFT,          KC_SPC,  MODWIN,
                                            KC_LCTL,TD(TD_WDELW),       KC_ENT,MOUSEWIN,
                                            FUNCWIN,   DEVWIN,          KC_DEL, COLEMAK
    ),
    /* MOD
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |Tilda |  F1  |  F2  |  F3  |  F4   |  F5   |                    |  F6   |  F7   |  F8  |  F9  |  F10 |  F11 |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   `  | Quit | BPage| Ntab | NPage |   _   |                    |   PUp |  Home |  Up  | End  |  Del |  F12 |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   | BTab | NApp |  NTab |Ideatab|                    |  PDwn |  Left | Down | Right|  Ins |  _   |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  | NWin |  _   |Close |   _   |   _   |                    |   _   |   {   |  }   |  [   |  ]   |  _   |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |  _   |   _  |                                                    |  _   |  _   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |   _   |   _   |                    |C_Space|   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |IdeaUp |IdeaLef|
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |IdeaDow|IdeaRig|
    *                             |---------------|                    |---------------|
     */

    [_MOD] = LAYOUT_5x6(
        KC_TILD,   KC_F1  ,       KC_F2 ,      KC_F3 ,       KC_F4 ,    KC_F5 ,            KC_F6  ,    KC_F7 ,    KC_F8 ,   KC_F9 ,KC_F10 , KC_F11,
         KC_GRV,LCMD(KC_Q),LCMD(KC_LBRC),  LCMD(KC_T),LCMD(KC_RBRC),   _______,            KC_PGUP,   KC_HOME,     KC_UP,   KC_END,KC_DEL , KC_F12,
        _______,   _______,SCMD(KC_LBRC),    MC_SWMAC,SCMD(KC_RBRC),MC_IDEASWAPM,          KC_PGDN,   KC_LEFT,   KC_DOWN, KC_RIGHT,KC_INS ,_______,
        _______,LCMD(KC_GRV),    _______,  LCMD(KC_W),      _______,   _______,            _______,S(KC_LBRC),S(KC_RBRC),  KC_LBRC,KC_RBRC,_______,
                                 _______,     _______,                                                           _______,  _______,
                                                            _______,_______,               KC_LSFT,LCMD(KC_SPC),
                                                            _______,_______,                IDEAUP,IDEALEFT,
                                                            _______,_______,              IDEADOWN,IDEARIGHT
    ),
    /* MOD WINDOWS
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |Tilda |  F1  |  F2  |  F3  |  F4   |  F5   |                    |   F6  |  F7   |  F8  |  F9  |  F10 |  F11 |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   `  | C_Q  | BPage| Ntab | NPage |   _   |                    |   PUp |  Home |  Up  | End  |  Del |  F12 |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   | BTab | NApp |  NTab |Ideatab|                    |  PDwn |  Left | Down | Right|  Ins |  _   |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |  _   |Close |   _   |   _   |                    |   _   |   {   |  }   |  [   |  ]   |  _   |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |  _   |   _  |                                                    |  _   |  _   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |   _   |   _   |                    |Windows|   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |IdeaUp |IdeaLef|
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |IdeaDow|IdeaRig|
    *                             |---------------|                    |---------------|
     */

    [_MODWIN] = LAYOUT_5x6(
          KC_TILD,     KC_F1 ,       KC_F2 ,      KC_F3 ,        KC_F4 ,     KC_F5,            KC_F6  ,    KC_F7 ,    KC_F8 ,   KC_F9 ,KC_F10 , KC_F11,
           KC_GRV,LALT(KC_F4),LALT(KC_LEFT),  LCTL(KC_T),LALT(KC_RIGHT),   _______,            KC_PGUP,   KC_HOME,     KC_UP,   KC_END,KC_DEL , KC_F12,
          _______,    _______,LCTL(KC_PGUP),    MC_SWWIN, LCTL(KC_PGDN),MC_IDEASWAPW,          KC_PGDN,   KC_LEFT,   KC_DOWN, KC_RIGHT, KC_INS,_______,
          _______,    _______,      _______,  LCTL(KC_W),      _______,    _______,            _______,S(KC_LBRC),S(KC_RBRC),  KC_LBRC,KC_RBRC,_______,
                                    _______,     _______,                                                            _______,  _______,
                                                                   _______,_______,            KC_LSFT,   KC_LWIN,
                                                                   _______,_______,            IDEAUPW, IDEALEFTW,
                                                                   _______,_______,          IDEADOWNW, IDEARIGHTW
    ),
    /* FUNC
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |RGBRot|RGBTogF|   _   |                    |MedStop|MedPlay|VolUp | End  |Win TL|Win TR|
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |RGB Xm|R stat|R Twik|RGBRoR|   _   |   _   |                    |MedLaun|MedPrev|VolDow|MedNex|Win L |Win R |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |R stat|R Brea|R Rain|R Swir|R Snake|R Knigh|                    |   _   |   {   |  }   |  [   |Win BL|Win BR|
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |  _   |   _  |                                                    |  _   |  _   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |   _   |   _   |                    |   _   |   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |MaxWin |   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |AppleMen|  _   |
    *                             |---------------|                    |---------------|
     */

    [_FUNC] = LAYOUT_5x6(
          _______,_______, _______, _______,_______,_______,          _______,_______,_______,_______,    _______,       _______,
          _______,_______, _______, RGB_MOD,RGB_TOG,_______,          KC_MSTP,KC_MPLY,KC_VOLU,_______,  LCA(KC_U),     LCA(KC_I),
          RGB_M_X,RGB_M_G,RGB_M_TW,RGB_RMOD,_______,_______,          KC_MSEL,KC_MPRV,KC_VOLD,KC_MNXT,LCA(KC_LEFT),LCA(KC_RIGHT),
          RGB_M_P,RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,         _______,_______,_______,_______,   LCA(KC_J),    LCA(KC_K),
                           _______, _______,                                          _______,_______,
                                               _______,_______,       _______,_______,
                                               _______,_______,    LCA(KC_ENT),_______,
                                               _______,_______,    RCS(KC_F2),_______
    ),
    /* FUNC WINDOWS
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |RGBRot|RGBTogF|   _   |                    |MedStop|MedPlay|VolUp | End  |Win T|Win TR |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |RGB Xm|R stat|R Twik|RGBRoR|   _   |   _   |                    |MedLaun|MedPrev|VolDow|MedNex|Win L |Win R |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |R stat|R Brea|R Rain|R Swir|R Snake|R Knigh|                    |   _   |   {   |  }   |  [   |Win D |   _  |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |  _   |   _  |                                                    |  _   |  _   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |   _   |   _   |                    |   _   |   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    | WMenu |   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |   _   |  _   |
    *                             |---------------|                    |---------------|
     */

    [_FUNCWIN] = LAYOUT_5x6(
          RCS(KC_F2),_______, _______, _______, _______,_______,           _______,_______,_______,_______,    _______,       _______,
          _______   ,_______, _______, RGB_MOD, RGB_TOG,_______,           KC_MSTP,KC_MPLY,KC_VOLU,_______,  LWIN(KC_UP),     _______,
          RGB_M_X   ,RGB_M_G,RGB_M_TW,RGB_RMOD, _______,_______,           KC_MSEL,KC_MPRV,KC_VOLD,KC_MNXT,LWIN(KC_LEFT),LWIN(KC_RIGHT),
          RGB_M_P   ,RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,           KC_EJCT,_______,_______,_______,   LWIN(KC_DOWN),   _______,
                              _______,_______,                                             _______,_______,
                                                _______,_______,           _______,_______,
                                                _______,_______,         A(KC_SPC),_______,
                                                _______,_______,           _______,_______
    ),
    /* MOUSE
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    | ScrUp | ScrLf | MS Up| ScrR |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   | MS RC| MS MC| MS LfC|   _   |                    | ScrDo | MS Lf | MS Dw| MS R |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |   _  | MSAc2|                                                    |  _   |  _   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             | MSAce1|MSAce0 |                    |   _   |   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |   _   |   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |   _   |   _   |
    *                             |---------------|                    |---------------|
     */
    [_MOUSE] = LAYOUT_5x6(
          _______,_______,   _______,   _______,   _______,_______,             _______,      _______,   _______,       _______,_______,_______,
          _______,_______,   _______,   _______,   _______,_______,       KC_MS_WH_DOWN,KC_MS_WH_LEFT,  KC_MS_UP,KC_MS_WH_RIGHT,_______,_______,
          _______,_______,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,_______,         KC_MS_WH_UP,   KC_MS_LEFT,KC_MS_DOWN,   KC_MS_RIGHT,_______,_______,
          _______,_______,   _______,   _______,   _______,_______,             _______,      _______,   _______,       _______,_______,_______,
                             _______,   KC_ACL2,                                                         _______,       _______,
                                                   KC_ACL1,KC_ACL0,             _______,_______,
                                                   _______,_______,             _______,_______,
                                                   _______,_______,             _______,_______
    ),
    /* MOUSE WINDOWS
     * ,-------------------------------------------.                    ,-------------------------------------------.
     * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
     * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
     * |   _  |  _   |   _  |  _   |   _   |   _   |                    | ScrUp | ScrLf | MS Up| ScrR |   _  |   _  |
     * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
     * |   _  |  _   | MS RC| MS MC| MS LfC|   _   |                    | ScrDo | MS Lf | MS Dw| MS R |   _  |   _  |
     * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
     * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
     * `-------------------------------------------|                    |-------------------------------------------'
     *               |   _  | MSAc2|                                                    |  _   |  _   |
     *               |      |      |                                                    |      |      |
     *               `-------------|                                                    |-------------'
     *                             |---------------.                    ,---------------|
     *                             | MSAce1|MSAce0 |                    |   _   |   _   |
     *                             |---------------|                    |---------------|
     *                             |   _   |   _   |                    |   _   |   _   |
     *                             |---------------|                    |---------------|
     *                             |   _   |   _   |                    |   _   |   _   |
     *                             |---------------|                    |---------------|
     */

    [_MOUSEWIN] = LAYOUT_5x6(
          _______,_______,   _______,   _______,   _______,_______,              _______,      _______,   _______,       _______,_______,_______,
          _______,_______,   _______,   _______,   _______,_______,          KC_MS_WH_UP,KC_MS_WH_LEFT,  KC_MS_UP, KC_MS_WH_RIGHT,_______,_______,
          _______,_______,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,_______,        KC_MS_WH_DOWN,   KC_MS_LEFT,KC_MS_DOWN,    KC_MS_RIGHT,_______,_______,
          _______,_______,   _______,   _______,   _______,_______,              _______,      _______,   _______,        _______,_______,_______,
                             _______,   KC_ACL2,                                                          _______,        _______,
                                                   KC_ACL1,KC_ACL0,              _______,_______,
                                                   _______,_______,              _______,_______,
                                                   _______,_______,              _______,_______
    ),
    /* DEV
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |  _   | IDEA  | IDEA  |                    |   (   |   )   |   {  |   }  |   _  |   _  |
    * |      |      |      |      |Imports|Rename |                    |       |       |      |      |      |      |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  | IDEA | IDEA  | IDEA  |                    |   @   |   -   |   =  |   _  |   _  |   _  |
    * |      |      |      |Split | Format|  Run  |                    |       |       |      |      |      |      |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |  _   |   _   | IDEA  |                    |   #   |   !   |   [  |   ]  |   -  |   -  |
    * |      |      |      |      |       | Impl  |                    |       |       |      |      |      |      |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |   _  |  _   |                                                    |   -  |  -   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |   _   |   _   |                    |R_Shift|   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    | PadEnt|   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |   _   |   _   |
    *                             |---------------|                    |---------------|
     */
    [_DEV] = LAYOUT_5x6(
          _______,_______,_______,_______, _______, _______,             _______,_______,_______,_______,_______,_______,
          _______,_______,_______,_______,IDEAIMPO, IDEAREN,             KC_LPRN,KC_RPRN,KC_LCBR,KC_RCBR,_______,_______,
          _______,_______,_______,IDEASPL, IDEAFOR, IDEARUN,             KC_AT  ,KC_MINS,KC_EQL ,_______,_______,_______,
          _______,_______,_______,_______, _______,IDEAIMPL,             A(KC_3),KC_EXLM,KC_LBRC,KC_RBRC,_______,_______,
                          _______,_______,                                               _______,_______,
                                           _______, _______,             KC_RSFT,_______,
                                           _______, _______,             KC_PENT,_______,
                                           _______, _______,             _______,_______
    ),
    /* DEV WINDOWS
    * ,-------------------------------------------.                    ,-------------------------------------------.
    * |   _  |  _   |   _  |  _   |   _   |   _   |                    |   _   |   _   |  _   |  _   |   _  |   _  |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |  _   | IDEA  | IDEA  |                    |   (   |   )   |   {  |   }  |   _  |   _  |
    * |      |      |      |      |Imports|Rename |                    |       |       |      |      |      |      |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |   _  | IDEA  | IDEA  |                    |   @   |   -   |   =  |   _  |   _  |   _  |
    * |      |      |      |      | Format|  Run  |                    |       |       |      |      |      |      |
    * |------+------+------+------+-------+-------|                    |-------+-------+------+------+------+------|
    * |   _  |  _   |   _  |  _   |   _   | IDEA  |                    |   #   |   !   |   [  |   ]  |   -  |   -  |
    * |      |      |      |      |       | Impl  |                    |       |       |      |      |      |      |
    * `-------------------------------------------|                    |-------------------------------------------'
    *               |   _  |  _   |                                                    |   -  |  -   |
    *               |      |      |                                                    |      |      |
    *               `-------------|                                                    |-------------'
    *                             |---------------.                    ,---------------|
    *                             |   _   |   _   |                    |R_Shift|   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    | PadEnt|   _   |
    *                             |---------------|                    |---------------|
    *                             |   _   |   _   |                    |Context|   _   |
    *                             |---------------|                    |---------------|
     */

    [_DEVWIN] = LAYOUT_5x6(
          _______,_______,_______,_______, _______,  _______,          _______,_______,_______,_______,_______,_______,
          _______,_______,_______,_______,IDEAIMPW, IDEARENW,          KC_LPRN,KC_RPRN,KC_LCBR,KC_RCBR,_______,_______,
          _______,_______,_______,_______,IDEAFORW, IDEARUNW,          KC_AT  ,KC_MINS,KC_EQL ,_______,_______,_______,
          _______,_______,_______,_______, _______,IDEAIMPLW,          KC_HASH,KC_EXLM,KC_LBRC,KC_RBRC,_______,_______,
                         _______, _______,                                             _______,_______,
                                             _______,_______,            KC_RSFT,_______,
                                             _______,_______,            KC_PENT,_______,
                                             _______,_______,             KC_APP,_______
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


// layer switching for RGB
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _COLEMAK:
    rgblight_sethsv(HSV_PURPLE);
        break;
    case _COLEWIN:
      rgblight_sethsv(HSV_AZURE);
        break;
    case _MOD:
    case _MODWIN:
      rgblight_sethsv(HSV_GREEN);
        break;
    case _FUNC:
    case _FUNCWIN:
        rgblight_sethsv(HSV_MAGENTA);
        break;
    case _MOUSE:
    case _MOUSEWIN:
        rgblight_sethsv(HSV_BLUE);
        break;
    case _DEV:
    case _DEVWIN:
          rgblight_sethsv(HSV_RED);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv(HSV_RED);
        break;
    }
  return state;
}
