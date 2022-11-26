#pragma once

#include QMK_KEYBOARD_H
#include "os_toggle.h"

typedef enum {
  NONE,
  SWAPPING_START,
  TABBING_START,
  ZOOMING_START,
  BROWSING_START,
  SWAPPING_CONTINUE,
  TABBING_CONTINUE,
  ZOOMING_CONTINUE,
  BROWSING_CONTINUE
} swapper_state_t;

typedef struct {
    swapper_state_t state;
} swapper_t;

process_record_result_t process_swapper(uint16_t keycode, keyrecord_t *record);
