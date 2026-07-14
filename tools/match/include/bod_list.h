// Intrusive BOD active/free list views, partial.
#ifndef BOD_LIST_H
#define BOD_LIST_H

#include "contact_target.h"

int report_errorf(char* format, ...);

struct BodNode : public ContactTargetObject {
    // Inlined cLinkedList<cRBod>::AddAfter used by the subgame group heads
    // and their live members.
    void add_bod_after(BodNode* previous)
    {
        if ((list_flags & BOD_FLAG_LINKED) != 0) {
            report_errorf("List ADDafter");
        } else {
            list_prev = previous;
            list_next = previous->list_next;
            previous->list_next = this;
            if (list_next != 0)
                list_next->list_prev = this;
            list_flags |= BOD_FLAG_LINKED;
        }
    }

    BodNode* list_prev;      // +0x08
    BodNode* list_next;      // +0x0c
};
typedef char BodNode_must_be_0x10[(sizeof(BodNode) == 0x10) ? 1 : -1];

class BodList {
public:
    void add_bod_to_front(BodNode* node); // @ 0x4113b0
    void append_bod_to_end(BodNode* node); // @ 0x411420
    int recycle_bod_to_free_list(BodNode* node); // @ 0x447290

    // Inlined cLinkedList<cRBod>::Add used by pickup allocators.
    void add_bod(BodNode* node)
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

    // Inlined cLinkedList<cRBod>::Remove; 0x447290 is its exact emitted copy.
    int remove_bod(BodNode* node)
    {
        int result = (int)node;
        unsigned int flags = node->list_flags;
        if ((flags & BOD_FLAG_LINKED) == 0)
            return report_errorf("List remove");
        if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0)
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
        node->list_flags &= ~BOD_FLAG_LINKED;
        return result;
    }

    int unknown_00;
    BodNode* first;    // +0x04
    BodNode* free_top; // +0x08
};
typedef char BodList_must_be_0x0c[(sizeof(BodList) == 0x0c) ? 1 : -1];

#endif
