// initialize_global_color4f_bank_32 @ 0x410c10 (cdecl)

#include "sprite.h"

enum { GLOBAL_COLOR4F_BANK_CAPACITY = 32 };

extern Color4f g_color4f_bank_32[GLOBAL_COLOR4F_BANK_CAPACITY]; // data_4f6e50

void initialize_global_color4f_bank_32()
{
    Color4f* color = g_color4f_bank_32;
    int count = GLOBAL_COLOR4F_BANK_CAPACITY;
    do {
        color->noop_this_constructor();
        ++color;
    } while (--count != 0);
}
