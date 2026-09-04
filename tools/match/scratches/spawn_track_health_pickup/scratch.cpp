// spawn_track_health_pickup @ 0x43d6c0 (thiscall, ret 0x8)

#include "game_root.h"
#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_health_pickup.h"


int report_errorf(char* format, ...);

void cRSubGame::AddHealth(cRSubLoc* cell, cRSubGoldy* player)
{
    int slot_index = 0;
    cRSubHealth* scan = health_pickups;
    while (slot_index < 8
        && scan->state != TRACK_PICKUP_STATE_INACTIVE) {
        ++slot_index;
        ++scan;
        if (slot_index >= 8)
            return;
    }

    health_pickups[slot_index].state = TRACK_PICKUP_STATE_ACTIVE;
    health_pickups[slot_index].owner = player;

    Vector3 staged_position =
        cell->position + Vector3(0.0f, 0.60000002f, 0.0f);
    Vector3* live_position = &health_pickups[slot_index].position;
    *live_position = staged_position;

    BodNode* node = &health_pickups[slot_index];
    g_game->active_bod_list.add_bod(node);

    // The cRSubGame slot owns the inline cRSubHealth actor and its BOD/lifecycle.
    // SpriteManager owns the visual; the slot retains a borrowed pointer.
    cRSprite* pickup_sprite =
        g_sprite_manager.New(player->player_slot, 57, -1, -1);
    health_pickups[slot_index].sprite = pickup_sprite;
    unsigned int flags = pickup_sprite->flags;
    flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
    pickup_sprite->flags = flags;
    health_pickups[slot_index].sprite->gravity_step = 0.0f;
    health_pickups[slot_index].sprite->progress = 0.0f;
    health_pickups[slot_index].sprite->progress_step = 0.0f;
    health_pickups[slot_index].sprite->size_start = 0.60000002f;
    health_pickups[slot_index].sprite->size_end = 0.60000002f;

    health_pickups[slot_index].sprite->position = *live_position;
    health_pickups[slot_index].source_cell = cell;
    float* bob_phase = &health_pickups[slot_index].bob_phase;
    *bob_phase = 0.0f;
    if (((int)health_pickups[slot_index].position.z & 1) != 0)
        *bob_phase = 0.0f;
    else
        *bob_phase = 0.5f;

    health_pickups[slot_index].bob_phase_step = 0.012820513f;
}
