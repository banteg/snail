// initialize_global_font3d_bods @ 0x449c20 (cdecl)

#include "font3d_runtime.h"

void initialize_global_font3d_bods()
{
    BodBase* bod = g_font3d_bods;
    for (int count = (int)(sizeof(g_font3d_bods) / sizeof(g_font3d_bods[0]));
         count != 0;
         --count) {
        bod->initialize_bod_base();
        ++bod;
    }
}
