// is_bod_after_sprites @ 0x42f5c0 (thiscall)

#include "bod_types.h"

bool cRBod::IsAfterSprites()
{
    if ((list_flags & BOD_FLAG_AFTER_SPRITES) != 0)
        return true;
    return false;
}
