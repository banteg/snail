// initialize_track_colour_bank_h @ 0x434ab0 (cdecl)

#include "track_colour_banks.h"

void initialize_track_colour_bank_h()
{
    Color4f* colour = g_track_colour_bank_h;
    int count = TRACK_COLOUR_BANK_CAPACITY;
    do {
        colour->noop_this_constructor();
        ++colour;
    } while (--count != 0);
}
