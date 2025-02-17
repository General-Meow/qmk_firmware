/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define USE_SERIAL

#define MASTER_LEFT
//#define MASTER_RIGHT

#define FORCE_NKRO

//ignore mod tap with permissive hold = hel)o
//ignore mod tap = hel)o
//permissive hold = helllo
//none helllo

#undef PERMISSIVE_HOLD

//#define IGNORE_MOD_TAP_INTERRUPT
//#define PERMISSIVE_HOLD
//#define TAPPING_FORCE_HOLD_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define HOLD_ON_OTHER_KEY_PRESS
#define TAPPING_TERM 180
//#define ONESHOT_TAP_TOGGLE 1
#define TAP_CODE_DELAY 30

// #define TAPPING_FORCE_HOLD
//#define EE_HANDS
//#define RGBLIGHT_LAYERS

//#define RGB_DI_PIN D1
//#define RGBLED_NUM 60
#define RGBLED_SPLIT { 30,30 }
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 165
//#define RGBLIGHT_MAX_LAYERS 15
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE
