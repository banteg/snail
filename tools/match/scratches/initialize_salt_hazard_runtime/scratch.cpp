// initialize_salt_hazard_runtime @ 0x408630 (thiscall, ret)
// Authored owner: cRSalt::cRSalt().

#include "bod_types.h"
#include "salt_hazard_types.h"

extern void* g_salt_vtable; // off_497340 / data_497340

cRSalt::cRSalt()
{
    vtable = &g_salt_vtable;
}
