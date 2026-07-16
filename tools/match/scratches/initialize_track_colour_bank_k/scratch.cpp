// initialize_track_colour_bank_k @ 0x434b40 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_k()
{
    tColour* colour = g_loc_colour_lookup_path_warp;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
