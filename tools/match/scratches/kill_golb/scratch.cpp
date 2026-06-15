// kill_golb @ 0x414670 (thiscall, ret)

#include "sprite.h"

int report_errorf(char* format, ...);

struct BodNode {
    int unknown_00;
    unsigned int list_flags; // +0x04
    BodNode* list_prev;      // +0x08
    BodNode* list_next;      // +0x0c
};

struct BodList {
    int unknown_00;
    BodNode* first;    // +0x04
    BodNode* free_top; // +0x08
};

extern char* g_game_base; // data_4df904

class GolbProjectile {
public:
    void kill_golb();

    BodNode primary_body;        // +0x000
    char unknown_010[0x080 - 0x010];
    BodNode secondary_body;      // +0x080
    char unknown_090[0x118 - 0x090];
    BodNode tertiary_body;       // +0x118
    char unknown_128[0x198 - 0x128];
    Sprite* attached_sprite;     // +0x198
    char unknown_19c[0x1c0 - 0x19c];
    int kind;                    // +0x1c0
    char unknown_1c4[0x244 - 0x1c4];
    int state;                   // +0x244
    Sprite* body_sprite;         // +0x248
};

void GolbProjectile::kill_golb()
{
    BodList* list = (BodList*)(g_game_base + 0x5a8);
    unsigned int flags = primary_body.list_flags;
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
    } else if ((flags & 0x40) != 0) {
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
        updated &= ~0x200;
        primary_body.list_flags = updated;
    }

    int live_kind = kind;
    state = 0;
    switch (live_kind) {
        case 0:
            body_sprite->kill_sprite();
            break;

        case 1: {
            BodNode* body = &secondary_body;
            BodList* list_kind1 = (BodList*)(g_game_base + 0x5a8);
            unsigned int kind1_flags = body->list_flags;
            if ((kind1_flags & 0x200) == 0) {
                report_errorf("List remove");
            } else if ((kind1_flags & 0x40) != 0) {
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
                updated &= ~0x200;
                body->list_flags = updated;
            }
            break;
        }

        case 2: {
            BodNode* body = &tertiary_body;
            BodList* list_kind2 = (BodList*)(g_game_base + 0x5a8);
            unsigned int kind2_flags = body->list_flags;
            if ((kind2_flags & 0x200) == 0) {
                report_errorf("List remove");
            } else if ((kind2_flags & 0x40) != 0) {
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
                updated &= ~0x200;
                body->list_flags = updated;
            }

            Sprite* sprite = attached_sprite;
            if (sprite != 0) {
                unsigned int sprite_flags = sprite->flags;
                sprite_flags &= ~0x1000;
                sprite->flags = sprite_flags;
            }
            break;
        }
    }
}
