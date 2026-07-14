// remove_sub_loc @ 0x439bc0 (thiscall, ret)

#include "fringe_object.h"
#include "game_root.h"
#include "track_attachment_types.h"

typedef unsigned int DWORD;

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

#define OUTER_RUNTIME_ROW(cursor_expr) ((SubRow*)((cursor_expr) + 0x6410e0))

#define REMOVE_BOD_NODE(node_expr, unlink_mask_expr)              \
    do {                                                          \
        BodList* list = &((GameRoot*)g_game_base)->active_bod_list; \
        BodNode* node = (node_expr);                              \
        DWORD flags = node->list_flags;                           \
        if ((flags & 0x200) == 0) {                               \
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
            node->list_flags &= (unlink_mask_expr);               \
        }                                                         \
    } while (0)

#define REMOVE_PRECHECKED_BOD_NODE(node_expr, unlink_mask_expr)   \
    do {                                                          \
        BodNode* node = (node_expr);                              \
        DWORD flags = node->list_flags;                           \
        BodList* list = &((GameRoot*)g_game_base)->active_bod_list; \
        if ((flags & 0x40) != 0) {                                \
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
            node->list_flags &= (unlink_mask_expr);               \
        }                                                         \
    } while (0)

void SubLoc::remove_sub_loc()
{
    int row_index = get_track_cell_row_index();
    unsigned char tile = tile_id;
    DWORD unlink_mask = 0xfffffdffu;

    if (tile == 0x1d || tile == 0x1e) {
        char* row_record = g_game_base + row_index * sizeof(SubRow);
        if ((OUTER_RUNTIME_ROW(row_record)->flags & 0x08) != 0) {
            if ((OUTER_RUNTIME_ROW(row_record)->attachment_body.list_flags & 0x200) != 0)
                REMOVE_BOD_NODE(&OUTER_RUNTIME_ROW(row_record)->attachment_body, unlink_mask);
        }
    }

    if ((bod.list_flags & 0x200) != 0)
        REMOVE_PRECHECKED_BOD_NODE(&bod, unlink_mask);

    Fringe** fringe = &fringe_front;
    for (int i = 0; i < 4; ++i) {
        Fringe* object = fringe[i];
        if (object != 0 && (object->list_flags & 0x200) != 0)
            REMOVE_BOD_NODE(object, unlink_mask);
    }
}
