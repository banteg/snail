#ifndef GUI_TYPES_H
#define GUI_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows cRGUI.
 * The Windows size ledger fixes the owner at 0x28 bytes and cRSubGame embeds
 * it at +0x125ffe0, immediately before cRHelp at +0x1260008. Android and iOS
 * independently preserve the authored Open, Init, UnInit, and AI class
 * surface plus the borrowed game pointer and widget slots used by Windows.
 */

typedef unsigned char uint8_t;

typedef struct cRSubGame cRSubGame;
typedef struct FrontendWidget FrontendWidget;

typedef struct cRGUI {
    cRSubGame* game;
    FrontendWidget* next_level_button;
    FrontendWidget* previous_level_button;
    FrontendWidget* level_name_widget;
    FrontendWidget* play_button;
    uint8_t _pad_14[0x18 - 0x14];
    FrontendWidget* back_button;
    FrontendWidget* speed_slider;
    FrontendWidget* difficulty_slider;
    FrontendWidget* replay_button;
} cRGUI;

typedef char cRGUI_must_be_0x28[(sizeof(cRGUI) == 0x28) ? 1 : -1];

#endif
