#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _MOD 1
#define _FUNC 2
#define _MOUSE 3
#define _DEV 4



#define MOD MO(_MOD)
#define FUNC MO(_FUNC)
#define MOUSE MO(_MOUSE)
#define DEV MO(_DEV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_MINS,
        MOUSE  , KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_M  , KC_N  , KC_E  , KC_I  ,   KC_O,KC_QUOT,
        KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LALT, KC_LCMD,                                                       KC_RCMD, KC_RALT,
                                            MOD, KC_LSFT,                        KC_SPC,    MOD,
                                        KC_LCTL, KC_BSPC,                        KC_ENT,  MOUSE,
                                           FUNC,     DEV,                       KC_RCTL, KC_GRV
    ),

    [_MOD] = LAYOUT_5x6(
          KC_NUHS, KC_F1 ,       KC_F2 ,      KC_F3 ,       KC_F4 ,    KC_F5 ,                        KC_F6  ,    KC_F7 ,    KC_F8 ,   KC_F9 ,KC_F10 , KC_F11,
           KC_GRV,_______,LCMD(KC_LBRC),  LCMD(KC_T),LCMD(KC_RBRC),S(KC_BSLS),                        KC_PGUP,   KC_HOME,     KC_UP,   KC_END,KC_DEL , KC_F12,
          _______,_______,SCMD(KC_LBRC),LCMD(KC_TAB),SCMD(KC_RBRC), S(KC_GRV),                        KC_PGDN,   KC_LEFT,   KC_DOWN, KC_RIGHT,KC_INS ,_______,
          _______,_______,      _______,  LCMD(KC_W),      _______,    KC_GRV,                        _______,S(KC_LBRC),S(KC_RBRC),  KC_LBRC,KC_RBRC,_______,
                                                  _______,_______,          LCMD(KC_SPC) ,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    ),

    [_FUNC] = LAYOUT_5x6(
          RCS(KC_F2),_______,_______,_______,_______,_______,                        _______,_______,_______,_______,    _______,       _______,
          _______   ,_______,_______,_______,RGB_TOG,_______,                        KC_MSTP,KC_MPLY,KC_VOLU,_______,  LCA(KC_U),     LCA(KC_I),
          _______   ,_______,_______,_______,_______,_______,                        _______,KC_MPRV,KC_VOLD,KC_MNXT,LCA(KC_LEFT),LCA(KC_RIGHT),
          _______   ,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,   LCA(KC_J),    LCA(KC_K),
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            LCA(KC_ENT),_______,
                                                  _______,_______,            _______,_______
    ),

    [_MOUSE] = LAYOUT_5x6(
          KC_F12 , KC_F1 ,    KC_F2 ,    KC_F3 ,    KC_F4 , KC_F5 ,                            KC_F6  ,       KC_F7 ,    KC_F8 ,         KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,   _______,   _______,   _______,_______,                        KC_MS_WH_UP,KC_MS_WH_LEFT,  KC_MS_UP, KC_MS_WH_RIGHT,_______,_______,
          _______,_______,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,_______,                        KC_MS_WH_DOWN, KC_MS_LEFT,KC_MS_DOWN,    KC_MS_RIGHT,_______,_______,
          _______,_______,   _______,   _______   ,_______,_______,                        _______,_______,_______,_______,_______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    ),

    [_DEV] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,_______,_______,_______,S(KC_F6),                       _______,_______,_______,_______,_______,_______,
          _______,_______,_______,_______,_______,RCS(KC_F10),                     _______,_______,_______,_______,_______,_______,
          _______,_______,_______,_______,_______,LOPT(KC_F7),                    _______,_______,_______,_______,_______,_______,
                                                  _______,_______,                       _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    )
};
