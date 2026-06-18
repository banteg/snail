// destroy_subgame @ 0x438850 (fastcall, ret)

#include "active_landscape_entry.h"
#include "bod_list.h"
#include "completion_screen.h"
#include "game.h"
#include "row_event_display.h"
#include "times_up_controller.h"
#include "warning_actor.h"

typedef unsigned int DWORD;

extern char* g_game_base; // data_4df904

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release
int report_errorf(char* format, ...);

#define BOD_NEXT_LINK_FLAGS(next_link) (*(DWORD*)((char*)(next_link) - 8))
#define BOD_NEXT_LINK_PREV(next_link) (*(BodNode**)((char*)(next_link) - 4))
#define BOD_NODE_FROM_NEXT_LINK(next_link) ((BodNode*)((char*)(next_link) - 0x0c))

#define REMOVE_BOD_NODE_FROM_NEXT_LINK(next_link_expr, linked_flag_expr) \
    do {                                                          \
        BodNode** next_link = (next_link_expr);                   \
        BodList* list = (BodList*)(g_game_base + 0x5a8);          \
        DWORD flags = BOD_NEXT_LINK_FLAGS(next_link);             \
        if ((flags & (linked_flag_expr)) == 0) {                  \
            report_errorf("List remove");                        \
        } else if ((flags & 0x40) != 0) {                         \
            report_errorf("List remove NEXTBOD");                \
        } else {                                                  \
            BodNode* next = *next_link;                           \
            if (next != 0)                                       \
                next->list_prev = BOD_NEXT_LINK_PREV(next_link);  \
            BodNode* prev = BOD_NEXT_LINK_PREV(next_link);        \
            if (prev != 0)                                       \
                prev->list_next = *next_link;                    \
            else                                                  \
                list->first = *next_link;                        \
            *next_link = list->free_top;                         \
            list->free_top = BOD_NODE_FROM_NEXT_LINK(next_link);  \
            DWORD updated = BOD_NEXT_LINK_FLAGS(next_link);       \
            updated &= ~0x200u;                                  \
            BOD_NEXT_LINK_FLAGS(next_link) = updated;             \
        }                                                         \
    } while (0)

#define REMOVE_INLINE_BOD_NODE(node_expr, linked_flag_expr)       \
    do {                                                          \
        BodList* list = (BodList*)(g_game_base + 0x5a8);          \
        BodNode* node = (node_expr);                              \
        DWORD flags = node->list_flags;                           \
        if ((flags & (linked_flag_expr)) == 0) {                  \
            report_errorf("List remove");                        \
        } else if ((flags & 0x40) != 0) {                         \
            report_errorf("List remove NEXTBOD");                \
        } else {                                                  \
            BodNode* next = node->list_next;                      \
            if (next != 0)                                       \
                next->list_prev = node->list_prev;                \
            BodNode* prev = node->list_prev;                      \
            if (prev != 0)                                       \
                prev->list_next = node->list_next;                \
            else                                                  \
                list->first = node->list_next;                    \
            node->list_next = list->free_top;                     \
            list->free_top = node;                                \
            DWORD updated = node->list_flags;                     \
            updated &= ~0x200u;                                   \
            node->list_flags = updated;                           \
        }                                                         \
    } while (0)

void Game::destroy_subgame()
{
    char* game = (char*)this;

    debug_report_stub("-SubGame::UnInit()\n");
    *(DWORD*)(g_game_base + 0x4f26c) = 1;

    if (*(DWORD*)(game + 0x40) == 7)
        ((TutorialController*)(game + 0xa858))->uninit_tutorial();

    ((WarningActor*)(game + 0x3bbb58))->uninit_warning();
    ((ActiveLandscapeEntry*)(game + 0xff7c00))->clear_active_landscape_entries();
    ((TimesUpController*)(game + 0x1272828))->uninit_times_up();
    remove_subgame_bods();

    DWORD subgame_state = *(DWORD*)(game + 0x3c);
    DWORD linked_flag = 0x200;
    if (subgame_state != 1) {
        DWORD level_mode = *(DWORD*)(game + 0x40);
        if (level_mode == 0 || level_mode == 1)
            ((RowEventDisplayController*)(game + 0x12727d8))->flush_row_event_display();

        BodNode** sub_lazer_next = &((BodNode*)(game + 0x356b00))->list_next;
        for (int i = 0; i < 20; ++i) {
            if ((BOD_NEXT_LINK_FLAGS(sub_lazer_next) & linked_flag) != 0)
                REMOVE_BOD_NODE_FROM_NEXT_LINK(sub_lazer_next, linked_flag);
            sub_lazer_next = (BodNode**)((char*)sub_lazer_next + 0xb0);
        }

        BodNode** salt_next = &((BodNode*)(game + 0x3578c0))->list_next;
        for (int j = 0; j < 40; ++j) {
            if ((BOD_NEXT_LINK_FLAGS(salt_next) & linked_flag) != 0)
                REMOVE_BOD_NODE_FROM_NEXT_LINK(salt_next, linked_flag);
            salt_next = (BodNode**)((char*)salt_next + 0x98);
        }

        BodNode** ring_next = &((BodNode*)(game + 0x359080))->list_next;
        for (int k = 0; k < 2; ++k) {
            if ((BOD_NEXT_LINK_FLAGS(ring_next) & linked_flag) != 0)
                REMOVE_BOD_NODE_FROM_NEXT_LINK(ring_next, linked_flag);
            ring_next = (BodNode**)((char*)ring_next + 0x60);
        }
    }

    if ((*(DWORD*)(game + 0xff7bc8) & linked_flag) != 0) {
        BodNode* selected_record_node = (BodNode*)(game + 0xff7bc4);
        REMOVE_INLINE_BOD_NODE(selected_record_node, linked_flag);
    }

    BorderManager* borders = (BorderManager*)(g_game_base + 0xb4c);
    borders->kill_border(*(FrontendWidget**)(game + 0x35bb88));
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(*(FrontendWidget**)(game + 0x35bb8c));

    if (*(unsigned char*)(game + 0xff25d1) != 0) {
        *(DWORD*)(g_game_base + 0x1bc) = 0x12;
        *(unsigned char*)(game + 0xff25d1) = 0;
    }

    if (*(DWORD*)(game + 0x40) == 3)
        *(DWORD*)(g_game_base + 0x74658) = 2;

    if (*(DWORD*)(game + 0x40) == 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(*(FrontendWidget**)(game + 0x35bb90));
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(*(FrontendWidget**)(game + 0x35bb94));

        FrontendWidget** widget = (FrontendWidget**)(game + 0x35bb98);
        for (int n = 0; n < 9; ++n)
            ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget[n]);
    }
}
