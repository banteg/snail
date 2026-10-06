// initialize_track_colour_bank_i @ 0x434ae0 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_i()
{
    tColour* colour = g_loc_colour_lookup_path;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
