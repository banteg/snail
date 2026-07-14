// remove_subgame_bods @ 0x440910 (thiscall, ret)

#include <stddef.h>

#include "bod_list.h"
#include "game_root.h"
#include "golb.h"
#include "runtime_slot.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "segment_cache.h"

typedef unsigned int DWORD;

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

#define BOD_NEXT_LINK_FLAGS(next_link) \
    (*(DWORD*)((char*)(next_link) + (int)offsetof(BodNode, list_flags) \
        - (int)offsetof(BodNode, list_next)))
#define BOD_NODE_FROM_NEXT_LINK(next_link) \
    ((BodNode*)((char*)(next_link) - (int)offsetof(BodNode, list_next)))

#define REMOVE_BOD_NODE_FROM_NEXT_LINK(next_link_expr)            \
    do {                                                         \
        BodNode** next_link = (next_link_expr);                  \
        BodList* list = &((GameRoot*)g_game_base)->active_bod_list; \
        list->remove_bod(BOD_NODE_FROM_NEXT_LINK(next_link));    \
    } while (0)

#define REMOVE_INLINE_BOD_NODE(node_expr)                        \
    do {                                                         \
        BodList* list = &((GameRoot*)g_game_base)->active_bod_list; \
        list->remove_bod((node_expr));                           \
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

    TrackRowCell* cell = &runtime_cells[0][0];
    BodNode** row_next = &runtime_rows[0].row_model.list_next;
    int row_count = sizeof(runtime_rows) / sizeof(runtime_rows[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(row_next) & 0x200) != 0)
            REMOVE_BOD_NODE_FROM_NEXT_LINK(row_next);

        int lane_count = sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
        do {
            cell->remove_sub_loc();
            ++cell;
            --lane_count;
        } while (lane_count != 0);

        row_next = (BodNode**)((char*)row_next + sizeof(SubRow));
        --row_count;
    } while (row_count != 0);

    segment_cache.remove_track_render_cache_bods();

    BodNode** health_next = &health_pickups[0].list_next;
    int health_count = sizeof(health_pickups) / sizeof(health_pickups[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(health_next) & 0x200) != 0)
            REMOVE_BOD_NODE_FROM_NEXT_LINK(health_next);
        ((SubHealth*)BOD_NODE_FROM_NEXT_LINK(health_next))->state = 0;
        health_next = (BodNode**)((char*)health_next + sizeof(SubHealth));
        --health_count;
    } while (health_count != 0);

    BodNode* speedup = &speedup_pickup;
    if ((speedup->list_flags & 0x200) != 0)
        REMOVE_INLINE_BOD_NODE(speedup);
    speedup_pickup.state = 0;

    BodNode* jetpack = &jetpack_pickup;
    if ((jetpack->list_flags & 0x200) != 0)
        REMOVE_INLINE_BOD_NODE(jetpack);
    jetpack_pickup.state = 0;

    BodNode** garbage_next = &garbage_hazards.slots[0].list_next;
    int garbage_count =
        sizeof(garbage_hazards.slots) / sizeof(garbage_hazards.slots[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(garbage_next) & 0x200) != 0) {
            ((SubGarbage*)BOD_NODE_FROM_NEXT_LINK(garbage_next))->state = 0;
            REMOVE_BOD_NODE_FROM_NEXT_LINK(garbage_next);
        }
        garbage_next = (BodNode**)((char*)garbage_next + sizeof(SubGarbage));
        --garbage_count;
    } while (garbage_count != 0);

    BodNode** slug_next = &slug_hazards.slots[0].list_next;
    int slug_count = sizeof(slug_hazards.slots) / sizeof(slug_hazards.slots[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(slug_next) & 0x200) != 0) {
            ((Slug*)BOD_NODE_FROM_NEXT_LINK(slug_next))->state = 0;
            REMOVE_BOD_NODE_FROM_NEXT_LINK(slug_next);
        }
        slug_next = (BodNode**)((char*)slug_next + sizeof(Slug));
        --slug_count;
    } while (slug_count != 0);

    BodNode** ring_next = &ring_effects.slots[0].list_next;
    int ring_count = sizeof(ring_effects.slots) / sizeof(ring_effects.slots[0]);
    do {
        if (((SubRing*)BOD_NODE_FROM_NEXT_LINK(ring_next))->state != 0) {
            REMOVE_BOD_NODE_FROM_NEXT_LINK(ring_next);
            ((SubRing*)BOD_NODE_FROM_NEXT_LINK(ring_next))->state = 0;
        }
        ring_next = (BodNode**)((char*)ring_next + sizeof(SubRing));
        --ring_count;
    } while (ring_count != 0);

    REMOVE_INLINE_BOD_NODE_IF_LINKED((BodNode*)embedded_player());
    REMOVE_INLINE_BOD_NODE(
        (BodNode*)&embedded_player()->presentation);
    REMOVE_INLINE_BOD_NODE(
        &embedded_player()->presentation.jetpack_channel);
    REMOVE_INLINE_BOD_NODE(
        &embedded_player()->presentation.weapon_channels[0]);

    BodList* list = &((GameRoot*)g_game_base)->active_bod_list;
    list->recycle_bod_to_free_list(
        &embedded_player()->presentation.weapon_channels[1]);
    ((GameRoot*)g_game_base)->active_bod_list.recycle_bod_to_free_list(
        &embedded_player()->presentation.weapon_channels[2]);
    ((GameRoot*)g_game_base)->active_bod_list.recycle_bod_to_free_list(
        (BodNode*)&embedded_player()->presentation.invincible_shell);

    player.movement_mode_selector = 0;
    // The Windows cRSubGoldy teardown hook folds to the shared one-byte stub.
    ((RuntimeSlot*)embedded_player())->noop_runtime_ai();

    GolbShot* shot = player.golb_shots;
    for (int m = 0; m < 12; ++m) {
        if (shot->state == 1)
            shot->kill_golb();
        ++shot;
    }

    if ((player.click_start.list_flags & 0x200) != 0)
        ((GameRoot*)g_game_base)->active_bod_list.recycle_bod_to_free_list(
            (BodNode*)&player.click_start);

    player.click_start.state = 0;
    g_sprite_manager.kill_game_sprites();
}
