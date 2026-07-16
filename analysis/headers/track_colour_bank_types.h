#ifndef TRACK_COLOUR_BANK_TYPES_H
#define TRACK_COLOUR_BANK_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for cRSubGame::BuildColours.
 * Android and iOS preserve the original gLocColourLookup* names and a
 * 53-entry capacity. The Windows build uses 51-entry banks and keeps two
 * physical Slide views where both mobile calls address one Slide owner.
 */

#define TRACK_COLOUR_BANK_CAPACITY 51

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct TrackFloorSlideColourBanks {
    tColour floor[TRACK_COLOUR_BANK_CAPACITY];
    tColour slide_0[TRACK_COLOUR_BANK_CAPACITY];
} TrackFloorSlideColourBanks;

extern tColour
    g_loc_colour_lookup_check_black[TRACK_COLOUR_BANK_CAPACITY];
extern TrackFloorSlideColourBanks g_loc_colour_lookup_floor_slide_0;
/*
 * g_loc_colour_lookup_slide_0 is the field-first symbol at +0x330 inside the
 * combined owner above; it is not an independent allocation.
 */
extern tColour g_loc_colour_lookup_slide_1[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_wall[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_trampoline[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_ramp[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_empty[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_path[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_path_worm[TRACK_COLOUR_BANK_CAPACITY];
extern tColour g_loc_colour_lookup_path_warp[TRACK_COLOUR_BANK_CAPACITY];

#endif
