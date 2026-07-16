// Global tColour banks used while building runtime track geometry.
#ifndef TRACK_COLOUR_BANKS_H
#define TRACK_COLOUR_BANKS_H

#include "sprite.h"

enum {
    TRACK_COLOUR_BANK_CAPACITY = 51,
    TRACK_COLOUR_BANK_B_C_CAPACITY = 102,
};

// Android and iOS preserve the original gLocColourLookup* names and the same
// BuildColours call order. Windows keeps two physical Slide banks where both
// mobile calls address the single gLocColourLookupSlide owner.
struct TrackFloorSlideColourBanks {
    tColour floor[TRACK_COLOUR_BANK_CAPACITY];
    tColour slide_0[TRACK_COLOUR_BANK_CAPACITY];
};

typedef char TrackFloorSlideColourBanks_must_be_0x660[
    (sizeof(TrackFloorSlideColourBanks) == 0x660) ? 1 : -1];

extern tColour
    g_loc_colour_lookup_check_black[TRACK_COLOUR_BANK_CAPACITY]; // data_74e7e8
extern TrackFloorSlideColourBanks
    g_loc_colour_lookup_floor_slide_0; // data_6437f8
extern tColour
    g_loc_colour_lookup_slide_1[TRACK_COLOUR_BANK_CAPACITY]; // data_53cb30
extern tColour g_loc_colour_lookup_wall[TRACK_COLOUR_BANK_CAPACITY]; // data_53ce60
extern tColour
    g_loc_colour_lookup_trampoline[TRACK_COLOUR_BANK_CAPACITY]; // data_6434c8
extern tColour g_loc_colour_lookup_ramp[TRACK_COLOUR_BANK_CAPACITY]; // data_6444b8
extern tColour g_loc_colour_lookup_empty[TRACK_COLOUR_BANK_CAPACITY]; // data_644188
extern tColour g_loc_colour_lookup_path[TRACK_COLOUR_BANK_CAPACITY]; // data_643e58
extern tColour
    g_loc_colour_lookup_path_worm[TRACK_COLOUR_BANK_CAPACITY]; // data_53c800
extern tColour
    g_loc_colour_lookup_path_warp[TRACK_COLOUR_BANK_CAPACITY]; // data_643198

#endif
