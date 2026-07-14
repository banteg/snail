// BodList::add_bod_to_front @ 0x4113b0

#include "bod_list.h"

void BodList::add_bod_to_front(BodNode* node)
{
    if ((node->list_flags & BOD_FLAG_LINKED) != 0) {
        report_errorf("List ADD");
    } else {
        if (first == 0) {
            first = node;
            node->list_prev = 0;
            first->list_next = 0;
        } else {
            first->list_prev = node;
            first->list_prev->list_next = first;
            first = first->list_prev;
            first->list_prev = 0;
        }
        node->list_flags |= BOD_FLAG_LINKED;
    }
}
