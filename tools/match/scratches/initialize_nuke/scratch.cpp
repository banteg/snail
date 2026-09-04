// cRNuke::Init @ 0x447110 (thiscall)

#include "game_root.h"
#include "nuke.h"
#include "player.h"
#include "subgame_runtime.h"


void cRNuke::Init()
{
    int zero = NUKE_STATE_INACTIVE;
    if (state == zero) {

        orbit_center_z = owner_player->transform.position.z - 5.0f;
        float rate = g_game->subgame.subgame_rate;
        orbit_phase = 0.0f;
        orbit_phase_step = 0.104719758f;
        state = NUKE_STATE_ACTIVE;
        orbit_center_z_step = rate + rate;

        for (int index = 0; index < NUKE_SPRITE_SLOT_COUNT; ++index) {
            cRSprite* sprite = g_sprite_manager.New(owner_player->player_slot, 0x83, -1, -1);
            sprite_slots[index] = sprite;
            sprite_slots[index]->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;

            sprite_slots[index]->progress = 0.0f;
            sprite_slots[index]->progress_step = 0.0f;
            sprite_slots[index]->size_start = 3.0f;
            sprite_slots[index]->size_end = 3.0f;
            Vector3* velocity = &sprite_slots[index]->velocity;
            velocity->z = 0.0f;
            velocity->y = 0.0f;
            velocity->x = 0.0f;
            Vector3* position = &sprite_slots[index]->position;
            position->z = 0.0f;
            position->y = 0.0f;
            position->x = 0.0f;
            sprite_slots[index]->gravity_step = 0.0f;

        }
    }

    AI();
}
