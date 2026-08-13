#ifndef SNAIL_SKIN_TYPES_H
#define SNAIL_SKIN_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRSnailSkin child at Snail +0x1938 (Player +0x42bc). Android preserves the
 * complete field flow and all three methods; iOS independently preserves the
 * authored class-qualified Init and method ownership.
 */

typedef int int32_t;

struct Snail;
struct TextureRef;

typedef struct cRSnailSkin {
    int32_t selected_slot;
    struct TextureRef* material_overrides[3];
    struct Snail* owner_snail;
    int32_t active;
    float progress;
    float progress_step;
} cRSnailSkin;

typedef char cRSnailSkin_must_be_0x20[
    (sizeof(cRSnailSkin) == 0x20) ? 1 : -1];

#endif
