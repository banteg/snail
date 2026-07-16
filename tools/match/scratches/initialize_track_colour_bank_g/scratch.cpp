// initialize_track_colour_bank_g @ 0x434a80 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_g()
{
    tColour* colour = g_loc_colour_lookup_ramp;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
