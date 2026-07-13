// Narrow out-of-line endpoint operations for the shared intrusive BOD list.
#ifndef BOD_LIST_ENDPOINTS_VIEW_H
#define BOD_LIST_ENDPOINTS_VIEW_H

#include "bod_list.h"

class BodListEndpointsView : public BodList {
public:
    void add_bod_to_front(BodNode* node); // @ 0x4113b0
    void append_bod_to_end(BodNode* node); // @ 0x411420
};

typedef char BodListEndpointsView_must_be_0x0c[
    (sizeof(BodListEndpointsView) == 0x0c) ? 1 : -1];

#endif
