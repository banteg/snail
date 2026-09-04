// spawn_track_jetpack_pickup @ 0x43d890 (thiscall, ret 0x8)

#include "game_root.h"
#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_jetpack_pickup.h"



int report_errorf(char* format, ...);

void cRSubGame::AddJetPack(cRSubLoc* cell, cRSubGoldy* player)
{
    int slot_index = 0;
    JetPack* scan = &jetpack_pickup;
    while (slot_index < 1
        && scan->state != TRACK_PICKUP_STATE_INACTIVE) {
        ++slot_index;
        ++scan;
        if (slot_index >= 1)
            return;
    }

    (&jetpack_pickup)[slot_index].state = TRACK_PICKUP_STATE_ACTIVE;
    (&jetpack_pickup)[slot_index].owner = player;

    Vector3 staged_position =
        cell->position + Vector3(0.0f, 1.5f, 0.0f);
    Vector3* live_position = &(&jetpack_pickup)[slot_index].position;
    *live_position = staged_position;

    if ((cell->lane_and_flags & SUBLOC_LANE_INDEX_MASK) == 3 && cell[-1].tile_id == SUBLOC_TILE_WALL2
        && cell[2].tile_id == SUBLOC_TILE_WALL2) {
        live_position->x = live_position->x + 0.5f;
    } else if ((cell->lane_and_flags & SUBLOC_LANE_INDEX_MASK) == 4 && cell[-2].tile_id == SUBLOC_TILE_WALL2
        && cell[1].tile_id == SUBLOC_TILE_WALL2) {
        live_position->x = live_position->x - 0.5f;
    }

    BodNode* node = &(&jetpack_pickup)[slot_index];
    g_game->active_bod_list.add_bod(node);

    cRSprite* sprite =
        g_sprite_manager.New(player->player_slot, 124, -1, -1);
    (&jetpack_pickup)[slot_index].sprite = sprite;
    unsigned int flags = sprite->flags;
    flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
    sprite->flags = flags;
    (&jetpack_pickup)[slot_index].sprite->gravity_step = 0.0f;
    (&jetpack_pickup)[slot_index].sprite->progress = 0.0f;
    (&jetpack_pickup)[slot_index].sprite->progress_step = 0.0f;
    (&jetpack_pickup)[slot_index].sprite->size_start = 1.5f;
    (&jetpack_pickup)[slot_index].sprite->size_end = 1.5f;

    (&jetpack_pickup)[slot_index].sprite->position = *live_position;
    (&jetpack_pickup)[slot_index].source_cell = cell;
    float* bob_phase = &(&jetpack_pickup)[slot_index].bob_phase;
    *bob_phase = 0.0f;

    int z_as_int = (int)(&jetpack_pickup)[slot_index].position.z;
    if ((z_as_int & 1) != 0) {
        *bob_phase = 0.0f;
        (&jetpack_pickup)[slot_index].bob_phase_step = 0.012820513f;
        return;
    }
    *bob_phase = 0.5f;
    (&jetpack_pickup)[slot_index].bob_phase_step = 0.012820513f;
}
