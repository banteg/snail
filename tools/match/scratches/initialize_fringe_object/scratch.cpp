// initialize_fringe_object @ 0x408650 (thiscall, ret)

#include "bod_types.h"

extern void* g_fringe_object_vtable; // off_497344 / data_497344

class FringeObject : public BodBase {
public:
    FringeObject* initialize_fringe_object();
};

FringeObject* FringeObject::initialize_fringe_object()
{
    initialize_bod_base();
    vtable = &g_fringe_object_vtable;
    return this;
}
