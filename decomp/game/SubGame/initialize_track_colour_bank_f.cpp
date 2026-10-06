// initialize_track_colour_bank_f @ 0x434a50 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_f()
{
    tColour* colour = g_loc_colour_lookup_trampoline;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
