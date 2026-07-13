// BodList::append_bod_to_end @ 0x411420

#include "bod_list_endpoints_view.h"

void BodListEndpointsView::append_bod_to_end(BodNode* node)
{
    if ((node->list_flags & 0x200) != 0) {
        report_errorf("List ADDend");
    } else {
        BodNode* tail = first;
        if (tail == 0) {
            first = node;
            node->list_prev = tail;
            first->list_next = 0;
        } else {
            while (tail->list_next != 0) {
                tail = tail->list_next;
            }
            tail->list_next = node;
            node->list_prev = tail;
            node->list_next = 0;
        }
        node->list_flags |= 0x200;
    }
}
