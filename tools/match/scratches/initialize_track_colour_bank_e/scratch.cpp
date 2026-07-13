// initialize_track_colour_bank_e @ 0x434a20 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_e()
{
    Color4f* colour = g_track_colour_bank_e;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
