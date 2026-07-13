// BodList::add_bod_to_front @ 0x4113b0

#include "bod_list_endpoints_view.h"

void BodListEndpointsView::add_bod_to_front(BodNode* node)
{
    if ((node->list_flags & 0x200) != 0) {
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
        node->list_flags |= 0x200;
    }
}
