#ifndef HELP_TYPES_H
#define HELP_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows cRHelp.
 * cRSubGame embeds the four-byte owner at +0x1260008, exactly between cRGUI
 * and the 0x14-byte cRSplash controller. Android and iOS independently
 * preserve the authored Init and AI methods; Android also retains UnInit.
 */

typedef struct FrontendWidget FrontendWidget;

typedef struct cRHelp {
    FrontendWidget* back_button;
} cRHelp;

typedef char cRHelp_must_be_0x04[(sizeof(cRHelp) == 0x04) ? 1 : -1];

#endif
