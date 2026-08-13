#ifndef PROGRESS_BAR_TYPES_H
#define PROGRESS_BAR_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRProgressBar child at Player +0x3f0. Android and iOS preserve the authored
 * class and AI method; the one-byte extent is the C++ empty-class object, with
 * the following three bytes belonging to Player alignment rather than state.
 */

typedef unsigned char uint8_t;

typedef struct cRProgressBar {
    uint8_t _empty;
} cRProgressBar;

typedef char cRProgressBar_must_be_0x1[
    (sizeof(cRProgressBar) == 0x1) ? 1 : -1];

#endif
