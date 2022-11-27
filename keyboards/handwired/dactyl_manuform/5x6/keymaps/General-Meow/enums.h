#pragma once


#define _PROCESS_RECORD_RESULT_H

typedef enum {
    PROCESS_RECORD_RETURN_TRUE,
    PROCESS_RECORD_RETURN_FALSE,
    PROCESS_RECORD_CONTINUE
} process_record_result_t;

//tap dance
enum {
  TD_Q,
  TD_W,
  TD_F,
  TD_P,
  TD_B,
  TD_A,
  TD_R,
  TD_S,
  TD_T,
  TD_G,
  TD_C,
  TD_Z,
  TD_X,
  TD_D,
  TD_V,
  TD_J,
  TD_L,
  TD_U,
  TD_Y,
  TD_M,
  TD_N,
  TD_E,
  TD_K,
  TD_H,
  TD_QUO,
  TD_SCLN,
  TD_LBR,
  TD_RBR,
  TD_DELW,
  //win
  TD_WQ,
  TD_WW,
  TD_WF,
  TD_WP,
  TD_WB,
  TD_WA,
  TD_WR,
  TD_WS,
  TD_WT,
  TD_WG,
  TD_WC,
  TD_WZ,
  TD_WX,
  TD_WD,
  TD_WV,
  TD_WJ,
  TD_WL,
  TD_WU,
  TD_WY,
  TD_WM,
  TD_WN,
  TD_WE,
  TD_WK,
  TD_WH,
  TD_WQUO,
  TD_WSCLN,
  TD_WLBR,
  TD_WRBR,
  TD_WDELW,

  //swapper
  // MC_MODP, MC_MODM, MC_SWLE, MC_SWRI,
  MC_SWMAC, MC_SWWIN,
};
