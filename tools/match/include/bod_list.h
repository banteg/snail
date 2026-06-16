// Intrusive BOD active/free list views, partial.
#ifndef BOD_LIST_H
#define BOD_LIST_H

#include "contact_target.h"

struct BodNode : public ContactTargetObject {
    BodNode* list_prev;      // +0x08
    BodNode* list_next;      // +0x0c
};
typedef char BodNode_must_be_0x10[(sizeof(BodNode) == 0x10) ? 1 : -1];

class BodList {
public:
    int recycle_bod_to_free_list(BodNode* node); // @ 0x447290

    int unknown_00;
    BodNode* first;    // +0x04
    BodNode* free_top; // +0x08
};
typedef char BodList_must_be_0x0c[(sizeof(BodList) == 0x0c) ? 1 : -1];

#endif
