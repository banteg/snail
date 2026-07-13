// initialize_track_colour_bank_j @ 0x434b10 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_j()
{
    Color4f* colour = g_track_colour_bank_j;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
