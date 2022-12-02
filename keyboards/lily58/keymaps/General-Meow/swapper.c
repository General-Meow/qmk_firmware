#include QMK_KEYBOARD_H

#include "swapper.h"
#include "enums.h"
//Swapper feature based on https://github.com/rafaelromao/keyboards/blob/main/src/qmk/users/rafaelromao/features/swapper.c

swapper_t swapper = {.state = NONE};

bool is_swapper_keycode(uint16_t keycode) {
    switch (keycode) {
        case MC_SWMAC:
        case MC_SWWIN:
        case MC_IDEASWAPM:
        case MC_IDEASWAPW:
            return true;
        default:
            return false;
    }
}

process_record_result_t process_swapper(uint16_t keycode, keyrecord_t *record) {
    if (record != NULL && record->event.pressed) {
        return PROCESS_RECORD_CONTINUE;
    }

    // Finish swapper
    if (!is_swapper_keycode(keycode)) {
        if (swapper.state != NONE) {
            clear_mods();
            swapper.state = NONE;
        }
        return PROCESS_RECORD_CONTINUE;
    }

    bool isShifted =  get_mods() & MOD_MASK_SHIFT;

    // Determine swapper mode
    if (swapper.state == NONE) {
        switch(keycode) {
            case MC_SWMAC:
            case MC_SWWIN:
                swapper.state = SWAPPING_START;
                break;
            case MC_IDEASWAPM:
            case MC_IDEASWAPW:
                swapper.state = TABBING_START;
                break;
        }
        clear_mods();
    }

    // Start swapper
    switch (swapper.state) {
        case SWAPPING_START:
            switch (keycode) {
                case MC_SWMAC:
                  register_mods(MOD_LGUI);
                  swapper.state = SWAPPING_CONTINUE;
                  break;
                case MC_SWWIN:
                  register_mods(MOD_LALT);
                  swapper.state = SWAPPING_CONTINUE;
                  break;
            }
            break;
        case TABBING_START:
            switch (keycode) {
                case MC_IDEASWAPM:
                case MC_IDEASWAPW:
                  register_mods(MOD_LCTL);
                  swapper.state = TABBING_CONTINUE;
                  break;
            }
            break;
        default:
            break;
    }

    // Check if action was reversed since started
    switch (swapper.state) {
        case SWAPPING_CONTINUE:
        case TABBING_CONTINUE:
            switch (keycode) {
                case MC_SWMAC:
                case MC_SWWIN:
                case MC_IDEASWAPM:
                case MC_IDEASWAPW:
                  if(isShifted)
                    register_mods(MOD_LSFT);
                  else {
                    unregister_mods(MOD_LSFT);
                  }
                  break;
            }
        default:
            break;
    }

    // Process swap action
    switch (swapper.state) {
        case SWAPPING_CONTINUE:
        case TABBING_CONTINUE:
            tap_code(KC_TAB);
            break;
        default:
            break;
    }

    return PROCESS_RECORD_RETURN_FALSE;
}
