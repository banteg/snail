// initialize_global_font3d_bods @ 0x449c20 (cdecl)

#include "bod_types.h"

void initialize_global_font3d_bods()
{
    BodBase* bod = g_font3d_bods;
    for (int count = 128; count != 0; --count) {
        bod->initialize_bod_base();
        ++bod;
    }
}
