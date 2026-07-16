// remove_sub_loc @ 0x439bc0 (thiscall, ret)

#include <stddef.h>

#include "fringe_object.h"
#include "game_root.h"
#include "track_attachment_types.h"

typedef unsigned int DWORD;


int report_errorf(char* format, ...);

enum {
    ROOT_RUNTIME_ROWS_BASE =
        offsetof(GameRoot, subgame) + offsetof(SubgameRuntime, runtime_rows),
};

#define OUTER_RUNTIME_ROW(cursor_expr) \
    ((SubRow*)((cursor_expr) + ROOT_RUNTIME_ROWS_BASE))

#define REMOVE_BOD_NODE(node_expr, unlink_mask_expr)              \
    do {                                                          \
        BodList* list = &g_game->active_bod_list;                 \
        BodNode* node = (node_expr);                              \
        DWORD flags = node->list_flags;                           \
        if ((flags & BOD_FLAG_LINKED) == 0) {                    \
            report_errorf("List remove");                        \
        } else if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {  \
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
        BodList* list = &g_game->active_bod_list;                 \
        if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {         \
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
    DWORD unlink_mask = ~BOD_FLAG_LINKED;

    if (tile == 0x1d || tile == 0x1e) {
        char* row_record = (char*)g_game + row_index * sizeof(SubRow);
        if ((OUTER_RUNTIME_ROW(row_record)->flags
                & SUBROW_FLAG_PATH_OR_MODEL_VELOCITY)
            != 0) {
            if ((OUTER_RUNTIME_ROW(row_record)->attachment_body.list_flags
                    & BOD_FLAG_LINKED) != 0)
                REMOVE_BOD_NODE(&OUTER_RUNTIME_ROW(row_record)->attachment_body, unlink_mask);
        }
    }

    if ((list_flags & BOD_FLAG_LINKED) != 0)
        REMOVE_PRECHECKED_BOD_NODE(this, unlink_mask);

    Fringe** fringe = fringes;
    for (int i = 0; i < (int)(sizeof(fringes) / sizeof(fringes[0])); ++i) {
        Fringe* object = fringe[i];
        if (object != 0 && (object->list_flags & BOD_FLAG_LINKED) != 0)
            REMOVE_BOD_NODE(object, unlink_mask);
    }
}
