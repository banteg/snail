// recycle_bod_to_free_list @ 0x447290 (thiscall, ret 0x4)

#include "bod_list.h"

int report_errorf(char* format, ...);

int BodList::recycle_bod_to_free_list(BodNode* node)
{
    return remove_bod(node);
}
