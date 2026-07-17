// kill_golb @ 0x414670 (thiscall, ret)

#include "bod_flags.h"
#include "game_root.h"
#include "golb.h"

int report_errorf(char* format, ...);


void GolbShot::kill_golb()
{
    BodList* list = &g_game->active_bod_list;
    unsigned int flags = primary_body.list_flags;
    if ((flags & BOD_FLAG_LINKED) == 0) {
        report_errorf("List remove");
    } else if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {
        report_errorf("List remove NEXTBOD");
    } else {
        BodNode* next = primary_body.list_next;
        if (next != 0)
            next->list_prev = primary_body.list_prev;

        BodNode* prev = primary_body.list_prev;
        if (prev != 0)
            prev->list_next = primary_body.list_next;
        else
            list->first = primary_body.list_next;

        primary_body.list_next = list->free_top;
        list->free_top = &primary_body;

        unsigned int updated = primary_body.list_flags;
        updated &= ~BOD_FLAG_LINKED;
        primary_body.list_flags = updated;
    }

    int live_kind = kind;
    state = 0;
    switch (live_kind) {
        case 0:
            render_sprite->kill_sprite();
            break;

        case 1: {
            BodNode* body = &vapour;
            BodList* list_kind1 = &g_game->active_bod_list;
            unsigned int kind1_flags = body->list_flags;
            if ((kind1_flags & BOD_FLAG_LINKED) == 0) {
                report_errorf("List remove");
            } else if ((kind1_flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {
                report_errorf("List remove NEXTBOD");
            } else {
                BodNode* next = body->list_next;
                if (next != 0)
                    next->list_prev = body->list_prev;

                BodNode* prev = body->list_prev;
                if (prev != 0)
                    prev->list_next = body->list_next;
                else
                    list_kind1->first = body->list_next;

                body->list_next = list_kind1->free_top;
                list_kind1->free_top = body;

                unsigned int updated = body->list_flags;
                updated &= ~BOD_FLAG_LINKED;
                body->list_flags = updated;
            }
            break;
        }

        case 2: {
            BodNode* body = &tertiary_body;
            BodList* list_kind2 = &g_game->active_bod_list;
            unsigned int kind2_flags = body->list_flags;
            if ((kind2_flags & BOD_FLAG_LINKED) == 0) {
                report_errorf("List remove");
            } else if ((kind2_flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {
                report_errorf("List remove NEXTBOD");
            } else {
                BodNode* next = body->list_next;
                if (next != 0)
                    next->list_prev = body->list_prev;

                BodNode* prev = body->list_prev;
                if (prev != 0)
                    prev->list_next = body->list_next;
                else
                    list_kind2->first = body->list_next;

                body->list_next = list_kind2->free_top;
                list_kind2->free_top = body;

                unsigned int updated = body->list_flags;
                updated &= ~BOD_FLAG_LINKED;
                body->list_flags = updated;
            }

            ContactTargetObject* target = homing_target_object;
            if (target != 0) {
                unsigned int target_flags = target->list_flags;
                target_flags &= ~BOD_FLAG_SUPPRESS_CONTACT;
                target->list_flags = target_flags;
            }
            break;
        }
    }
}
