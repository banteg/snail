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


static inline cRSubLoc* remove_row_cells(cRSubLoc* cell, int count)
{
    do {
        cell->Remove();
        ++cell;
        --count;
    } while (count != 0);
    return cell;
}

void cRSubGame::RemoveBods()
{
    cRSubLoc* cell = &runtime_cells[0][0];
    BodNode** row_next = &runtime_rows[0].row_model.list_next;
    int row_count = sizeof(runtime_rows) / sizeof(runtime_rows[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(row_next) & BOD_FLAG_LINKED) != 0)
            REMOVE_BOD_NODE_FROM_NEXT_LINK(row_next);

        cell = remove_row_cells(cell, sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]));

        row_next = (BodNode**)((char*)row_next + sizeof(SubRow));
        --row_count;
    } while (row_count != 0);

    segment_cache.remove_track_render_cache_bods();

    BodNode** health_next = &health_pickups[0].list_next;
    int health_count = sizeof(health_pickups) / sizeof(health_pickups[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(health_next) & BOD_FLAG_LINKED) != 0) {
            REMOVE_BOD_NODE_FROM_NEXT_LINK(health_next);
            ((cRSubHealth*)BOD_NODE_FROM_NEXT_LINK(health_next))->state =
                TRACK_PICKUP_STATE_INACTIVE;
        }
        health_next = (BodNode**)((char*)health_next + sizeof(cRSubHealth));
        --health_count;
    } while (health_count != 0);

    if ((speedup_pickup.list_flags & BOD_FLAG_LINKED) != 0) {
        g_game->active_bod_list.remove_bod(&speedup_pickup);
        speedup_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
    }

    if ((jetpack_pickup.list_flags & BOD_FLAG_LINKED) != 0) {
        g_game->active_bod_list.remove_bod(&jetpack_pickup);
        jetpack_pickup.state = TRACK_PICKUP_STATE_INACTIVE;
    }

    BodNode** garbage_next = &garbage_hazards.slots[0].list_next;
    int garbage_count =
        sizeof(garbage_hazards.slots) / sizeof(garbage_hazards.slots[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(garbage_next) & BOD_FLAG_LINKED) != 0) {
            ((cRSubGarbage*)BOD_NODE_FROM_NEXT_LINK(garbage_next))->state =
                SUB_GARBAGE_STATE_INACTIVE;
            REMOVE_BOD_NODE_FROM_NEXT_LINK(garbage_next);
        }
        garbage_next = (BodNode**)((char*)garbage_next + sizeof(cRSubGarbage));
        --garbage_count;
    } while (garbage_count != 0);

    BodNode** slug_next = &slug_hazards.slots[0].list_next;
    int slug_count = sizeof(slug_hazards.slots) / sizeof(slug_hazards.slots[0]);
    do {
        if ((BOD_NEXT_LINK_FLAGS(slug_next) & BOD_FLAG_LINKED) != 0) {
            ((cRSlug*)BOD_NODE_FROM_NEXT_LINK(slug_next))->state =
                SUB_SLUG_STATE_INACTIVE;
            REMOVE_BOD_NODE_FROM_NEXT_LINK(slug_next);
        }
        slug_next = (BodNode**)((char*)slug_next + sizeof(cRSlug));
        --slug_count;
    } while (slug_count != 0);

    BodNode** ring_next = &ring_effects.slots[0].list_next;
    int ring_count = sizeof(ring_effects.slots) / sizeof(ring_effects.slots[0]);
    do {
        if (((SubRing*)BOD_NODE_FROM_NEXT_LINK(ring_next))->state
            != SUB_RING_STATE_INACTIVE) {
            REMOVE_BOD_NODE_FROM_NEXT_LINK(ring_next);
        }
        ((SubRing*)BOD_NODE_FROM_NEXT_LINK(ring_next))->state =
            SUB_RING_STATE_INACTIVE;
        ring_next = (BodNode**)((char*)ring_next + sizeof(SubRing));
        --ring_count;
    } while (ring_count != 0);

    {
        if ((player.list_flags & BOD_FLAG_LINKED) != 0) {
            g_game->active_bod_list.remove_bod((BodNode*)&player);
            g_game->active_bod_list.remove_bod(
                (BodNode*)&player.presentation);
            g_game->active_bod_list.remove_bod(
                &player.presentation.jetpack_channel);
            g_game->active_bod_list.remove_bod(
                &player.presentation.weapon_channels[0]);

            BodList* list = &g_game->active_bod_list;
            list->recycle_bod_to_free_list(
                &player.presentation.weapon_channels[1]);
            g_game->active_bod_list.recycle_bod_to_free_list(
                &player.presentation.weapon_channels[2]);
            g_game->active_bod_list.recycle_bod_to_free_list(
                (BodNode*)&player.presentation.invincible_shell);

            player.movement_mode_selector = 0;
            // Windows folds the cRSubGoldy teardown hook to the shared
            // one-byte stub.
            ((RuntimeSlot*)&player)->noop_runtime_ai();
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
