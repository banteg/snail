#ifndef BN_HIGH_SCORE_SCREEN_TYPES_H
#define BN_HIGH_SCORE_SCREEN_TYPES_H

/* Authored cRHighScore front-end controller. The following 0x14 root bytes
   remain unassigned before the exact TipManager boundary. */
typedef struct HighScore {
    int32_t field_00;
    int32_t mode;
    int32_t selected_bank;
    uint8_t _pad_0c[0x10 - 0x0c];
    uint8_t entering_name;
    uint8_t _pad_11[0x14 - 0x11];
    int32_t selected_rank;
    FrontendWidget* title_widget;
    FrontendWidget* back_button;
    FrontendWidget* bank_toggle_button;
    FrontendWidget* cancel_name_button;
    FrontendWidget* submit_name_button;
    FrontendWidget* row_background_widgets[10];
    FrontendWidget* rank_row_widgets[10];
    FrontendWidget* name_row_widgets[10];
    FrontendWidget* score_row_widgets[10];
    FrontendWidget* replay_row_widgets[10];
} HighScore;

#endif
