// initialize_bod @ 0x4088c0 (thiscall, ret)

#include "bod_types.h"

extern void* g_bod_vtable; // off_497368 / data_497368
extern int g_bod_count;    // unk_4dfadc / data_4dfadc

class Bod : public BodBase {
public:
    Bod* initialize_bod();
};

Bod* Bod::initialize_bod()
{
    initialize_bod_base();
    vtable = &g_bod_vtable;
    ++g_bod_count;
    return this;
}
