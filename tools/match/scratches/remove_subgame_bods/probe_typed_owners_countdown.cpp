// remove_subgame_bods @ 0x440910 (thiscall, ret)

#include "bod_list.h"
#include "game_root.h"
#include "golb.h"
#include "runtime_slot.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "segment_cache.h"

typedef unsigned int DWORD;


int report_errorf(char* format, ...);

#define REMOVE_BOD_NODE_FROM_NEXT_LINK(next_link_expr)            \
    do {                                                         \
        BodNode** next_link = (next_link_expr);                  \
        BodList* list = &g_game->active_bod_list;                 \
        list->remove_bod(BOD_NODE_FROM_NEXT_LINK(next_link));    \
    } while (0)

#define REMOVE_INLINE_BOD_NODE(node_expr)                        \
    do {                                                         \
        BodList* list = &g_game->active_bod_list;                 \
        list->remove_bod((node_expr));                           \
    } while (0)

void cRSubGame::RemoveBods()
{
    cRSubLoc* cell = &runtime_cells[0][0];
    SubRow* current_row = &runtime_rows[0];
    int row_count = sizeof(runtime_rows) / sizeof(runtime_rows[0]);
    do {
        if ((current_row->row_model.list_flags & BOD_FLAG_LINKED) != 0)
            REMOVE_INLINE_BOD_NODE(&current_row->row_model);

        int lane_count = sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]);
        do {
            cell->Remove();
            ++cell;
        } while (--lane_count != 0);

        ++current_row;
        --row_count;
    } while (row_count != 0);

    segment_cache.remove_track_render_cache_bods();

    cRSubHealth* health_slot = &health_pickups[0];
    int health_count = sizeof(health_pickups) / sizeof(health_pickups[0]);
    do {
        if ((health_slot->list_flags & BOD_FLAG_LINKED) != 0) {
            REMOVE_INLINE_BOD_NODE(health_slot);
            health_slot->state =
                TRACK_PICKUP_STATE_INACTIVE;
        }
        ++health_slot;
        --health_count;
    } while (health_count != 0);

    BodNode* speedup = &speedup_pickup;
    if ((speedup->list_flags & BOD_FLAG_LINKED) != 0) {
        REMOVE_INLINE_BOD_NODE(speedup);
        speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
    }

    BodNode* jetpack = &jetpack_pickup;
    if ((jetpack->list_flags & BOD_FLAG_LINKED) != 0) {
        REMOVE_INLINE_BOD_NODE(jetpack);
        jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
    }

    cRSubGarbage* garbage_slot = &garbage_hazards.slots[0];
    int garbage_count =
        sizeof(garbage_hazards.slots) / sizeof(garbage_hazards.slots[0]);
    do {
        if ((garbage_slot->list_flags & BOD_FLAG_LINKED) != 0) {
            garbage_slot->state =
                SUB_GARBAGE_STATE_INACTIVE;
            REMOVE_INLINE_BOD_NODE(garbage_slot);
        }
        ++garbage_slot;
        --garbage_count;
    } while (garbage_count != 0);

    cRSlug* slug_slot = &slug_hazards.slots[0];
    int slug_count = sizeof(slug_hazards.slots) / sizeof(slug_hazards.slots[0]);
    do {
        if ((slug_slot->list_flags & BOD_FLAG_LINKED) != 0) {
            slug_slot->state =
                SUB_SLUG_STATE_INACTIVE;
            REMOVE_INLINE_BOD_NODE(slug_slot);
        }
        ++slug_slot;
        --slug_count;
    } while (slug_count != 0);

    SubRing* ring_slot = &ring_effects.slots[0];
    int ring_count = sizeof(ring_effects.slots) / sizeof(ring_effects.slots[0]);
    do {
        if (ring_slot->state
            != SUB_RING_STATE_INACTIVE) {
            REMOVE_INLINE_BOD_NODE(ring_slot);
        }
        ring_slot->state =
            SUB_RING_STATE_INACTIVE;
        ++ring_slot;
        --ring_count;
    } while (ring_count != 0);

    {
        cRSubGoldy& player_owner = player;
        if ((((BodNode*)&player_owner)->list_flags & BOD_FLAG_LINKED) != 0) {
            REMOVE_INLINE_BOD_NODE((BodNode*)&player_owner);
            REMOVE_INLINE_BOD_NODE(
                (BodNode*)&player_owner.presentation);
            REMOVE_INLINE_BOD_NODE(
                &player_owner.presentation.jetpack_channel);
            REMOVE_INLINE_BOD_NODE(
                &player_owner.presentation.weapon_channels[0]);

            BodList* list = &g_game->active_bod_list;
            list->recycle_bod_to_free_list(
                &player_owner.presentation.weapon_channels[1]);
            g_game->active_bod_list.recycle_bod_to_free_list(
                &player_owner.presentation.weapon_channels[2]);
            g_game->active_bod_list.recycle_bod_to_free_list(
                (BodNode*)&player_owner.presentation.invincible_shell);

            player_owner.movement_mode_selector = 0;
            // Windows folds the cRSubGoldy teardown hook to the shared
            // one-byte stub.
            ((RuntimeSlot*)&player_owner)->noop_runtime_ai();
        }
    }

    cRSubGolb* shot = player.golb_shots;
    for (int m = 0;
         m < (int)(sizeof(player.golb_shots) / sizeof(player.golb_shots[0]));
         ++m) {
        if (shot->state == 1)
            shot->Kill();
        ++shot;
    }

    if ((player.click_start.list_flags & BOD_FLAG_LINKED) != 0) {
        g_game->active_bod_list.recycle_bod_to_free_list(
            (BodNode*)&player.click_start);
        player.click_start.state = CLICK_START_STATE_INACTIVE;
    }
    g_sprite_manager.KillGame();
}
