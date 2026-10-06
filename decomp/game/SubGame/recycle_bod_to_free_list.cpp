// recycle_bod_to_free_list @ 0x447290 (thiscall, ret 0x4)

#include "bod_list.h"

void BodList::recycle_bod_to_free_list(BodNode* node)
{
    remove_bod(node);
}
