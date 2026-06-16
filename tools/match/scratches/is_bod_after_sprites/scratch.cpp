// is_bod_after_sprites @ 0x42f5c0 (thiscall)

#include "bod_types.h"

bool BodBase::is_bod_after_sprites()
{
    if ((flags & 0x80) != 0)
        return true;
    return false;
}
