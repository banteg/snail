// Intrusive BOD active/free list views, partial.
#ifndef BOD_LIST_H
#define BOD_LIST_H

struct BodNode {
    int unknown_00;
    unsigned int list_flags; // +0x04
    BodNode* list_prev;      // +0x08
    BodNode* list_next;      // +0x0c
};

class BodList {
public:
    int recycle_bod_to_free_list(BodNode* node); // @ 0x447290

    int unknown_00;
    BodNode* first;    // +0x04
    BodNode* free_top; // +0x08
};

#endif
