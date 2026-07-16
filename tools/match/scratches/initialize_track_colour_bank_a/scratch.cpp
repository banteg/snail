// initialize_track_colour_bank_a @ 0x434990 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_a()
{
    tColour* colour = g_loc_colour_lookup_check_black;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
