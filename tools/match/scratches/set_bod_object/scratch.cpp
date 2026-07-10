// set_bod_object @ 0x42f5d0 (thiscall, ret 4)

#include "bod_types.h"

int BodBase::set_bod_object(void* object_)
{
    object = (Object*)object_;
    list_flags |= 2;
    return list_flags;
}
