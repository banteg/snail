// initialize_bod @ 0x4088c0 (thiscall, ret)

#include "track_attachment_types.h"

extern void* g_sub_loc_vtable; // off_497368 / data_497368
extern int g_sub_loc_count;    // unk_4dfadc / data_4dfadc

SubLoc* SubLoc::initialize_bod()
{
    ((BodBase*)this)->initialize_bod_base();
    bod.vtable = &g_sub_loc_vtable;
    ++g_sub_loc_count;
    return this;
}
