// remove_subgame_bods @ 0x440910 (thiscall, ret)

#include "bod_list.h"
#include "golb.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_render_cache.h"

typedef unsigned int DWORD;

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

#define BOD_NEXT_LINK_FLAGS(next_link) (*(DWORD*)((char*)(next_link) - 8))
#define BOD_NEXT_LINK_PREV(next_link) (*(BodNode**)((char*)(next_link) - 4))
#define BOD_NODE_FROM_NEXT_LINK(next_link) ((BodNode*)((char*)(next_link) - 0x0c))

#define REMOVE_BOD_NODE_FROM_NEXT_LINK(next_link_expr)             \
    do {                                                          \
        BodNode** next_link = (next_link_expr);                   \
        BodList* list = (BodList*)(g_game_base + 0x5a8);          \
        DWORD flags = BOD_NEXT_LINK_FLAGS(next_link);             \
        if ((flags & 0x200) == 0) {                               \
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
            updated &= ~0x200u;                                   \
            BOD_NEXT_LINK_FLAGS(next_link) = updated;             \
        }                                                         \
    } while (0)

#define REMOVE_INLINE_BOD_NODE(node_expr)                         \
    do {                                                          \
        BodList* list = (BodList*)(g_game_base + 0x5a8);          \
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
            DWORD updated = node->list_flags;                     \
            updated &= ~0x200u;                                   \
            node->list_flags = updated;                           \
        }                                                         \
    } while (0)

#define REMOVE_INLINE_BOD_NODE_IF_LINKED(node_expr)               \
    do {                                                          \
        BodNode* node = (node_expr);                              \
        if ((node->list_flags & 0x200) != 0)                      \
            REMOVE_INLINE_BOD_NODE(node);                         \
    } while (0)

void SubgameRuntime::remove_subgame_bods()
{
    char* game = (char*)this;

    TrackRowCell* cell = (TrackRowCell*)(game + 0x3bfac8);
    BodNode** row_next = (BodNode**)(game + 0x5ccad8);
    int row_count = 0xc80;
    do {
        if ((BOD_NEXT_LINK_FLAGS(row_next) & 0x200) != 0)
            REMOVE_BOD_NODE_FROM_NEXT_LINK(row_next);

        int lane_count = 8;
        do {
            cell->destroy_sub_lazer_projectile();
            ++cell;
            --lane_count;
        } while (lane_count != 0);

        row_next = (BodNode**)((char*)row_next + 0xf4);
        --row_count;
    } while (row_count != 0);

    ((TrackRenderCacheManager*)(game + 0x5c))->remove_track_render_cache_bods();

    BodNode** health_next = (BodNode**)(game + 0x35600c);
    int health_count = 8;
    do {
        if ((BOD_NEXT_LINK_FLAGS(health_next) & 0x200) != 0)
            REMOVE_BOD_NODE_FROM_NEXT_LINK(health_next);
        *(int*)((char*)health_next + 0x2c) = 0;
        health_next = (BodNode**)((char*)health_next + 0x74);
        --health_count;
    } while (health_count != 0);

    BodNode* speedup = (BodNode*)(game + 0x355db0);
    if ((speedup->list_flags & 0x200) != 0)
        REMOVE_INLINE_BOD_NODE(speedup);
    *(int*)(game + 0x355e30) = 0;

    BodNode* jetpack = (BodNode*)(game + 0x355e64);
    if ((jetpack->list_flags & 0x200) != 0)
        REMOVE_INLINE_BOD_NODE(jetpack);
    *(int*)(game + 0x355e9c) = 0;

    BodNode** garbage_next = (BodNode**)(game + 0x359150);
    int garbage_count = 50;
    do {
        if ((BOD_NEXT_LINK_FLAGS(garbage_next) & 0x200) != 0) {
            *(int*)((char*)garbage_next + 0x78) = 0;
            REMOVE_BOD_NODE_FROM_NEXT_LINK(garbage_next);
        }
        garbage_next = (BodNode**)((char*)garbage_next + 0xc4);
        --garbage_count;
    } while (garbage_count != 0);

    BodNode** slug_next = (BodNode**)(game + 0x3563ac);
    int slug_count = 8;
    do {
        if ((BOD_NEXT_LINK_FLAGS(slug_next) & 0x200) != 0) {
            *(int*)((char*)slug_next + 0x74) = 0;
            REMOVE_BOD_NODE_FROM_NEXT_LINK(slug_next);
        }
        slug_next = (BodNode**)((char*)slug_next + 0xec);
        --slug_count;
    } while (slug_count != 0);

    BodNode** ring_next = (BodNode**)(game + 0x35b798);
    int ring_count = 2;
    do {
        if (*(int*)((char*)ring_next + 0x74) != 0) {
            REMOVE_BOD_NODE_FROM_NEXT_LINK(ring_next);
            *(int*)((char*)ring_next + 0x74) = 0;
        }
        ring_next = (BodNode**)((char*)ring_next + 0x1f8);
        --ring_count;
    } while (ring_count != 0);

    REMOVE_INLINE_BOD_NODE_IF_LINKED((BodNode*)(game + 0x3bb764));
    REMOVE_INLINE_BOD_NODE((BodNode*)(game + 0x3be0e8));
    REMOVE_INLINE_BOD_NODE((BodNode*)(game + 0x3bf2c8));
    REMOVE_INLINE_BOD_NODE((BodNode*)(game + 0x3be734));

    BodList* list = (BodList*)(g_game_base + 0x5a8);
    list->recycle_bod_to_free_list((BodNode*)(game + 0x3beb10));
    ((BodList*)(g_game_base + 0x5a8))->recycle_bod_to_free_list((BodNode*)(game + 0x3beeec));
    ((BodList*)(g_game_base + 0x5a8))->recycle_bod_to_free_list((BodNode*)(game + 0x3bf97c));

    *(int*)(game + 0x3bbb70) = 0;

    GolbShot* shot = (GolbShot*)(game + 0x3bbbb4);
    for (int m = 0; m < 12; ++m) {
        if (shot->state == 1)
            shot->kill_golb();
        shot = (GolbShot*)((char*)shot + 0x2e8);
    }

    if ((*(DWORD*)(game + 0x3bb808) & 0x200) != 0)
        ((BodList*)(g_game_base + 0x5a8))->recycle_bod_to_free_list((BodNode*)(game + 0x3bb804));

    *(int*)(game + 0x3bb884) = 0;
    g_sprite_manager.kill_game_sprites();
}
