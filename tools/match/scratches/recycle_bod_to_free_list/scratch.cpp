// recycle_bod_to_free_list @ 0x447290 (thiscall, ret 0x4)

#include "bod_list.h"

int report_errorf(char* format, ...);

int BodList::recycle_bod_to_free_list(BodNode* node)
{
    int result = (int)node;
    unsigned int flags = node->list_flags;
    if ((flags & 0x200) == 0)
        return report_errorf("List remove");
    if ((flags & 0x40) != 0)
        return report_errorf("List remove NEXTBOD");

    BodNode* next = node->list_next;
    if (next != 0)
        next->list_prev = node->list_prev;

    BodNode* prev = node->list_prev;
    if (prev != 0)
        prev->list_next = node->list_next;
    else
        first = node->list_next;

    node->list_next = free_top;
    free_top = node;

    unsigned int updated = node->list_flags;
    updated &= ~0x200;
    node->list_flags = updated;
    return result;
}
