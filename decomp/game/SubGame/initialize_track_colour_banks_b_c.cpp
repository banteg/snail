// initialize_track_colour_banks_b_c @ 0x4349c0 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_banks_b_c()
{
    tColour* colour = g_loc_colour_lookup_floor_slide_0.floor;
    int count = TRACK_COLOUR_BANK_B_C_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
