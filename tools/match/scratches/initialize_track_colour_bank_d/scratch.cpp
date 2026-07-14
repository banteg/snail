// initialize_track_colour_bank_d @ 0x4349f0 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_d()
{
    tColour* colour = g_track_colour_bank_d;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
