// initialize_nuke @ 0x447110 (thiscall)

#include "game_root.h"
#include "nuke.h"
#include "player.h"
#include "subgame_runtime.h"

extern GameRoot* g_game; // data_4df904

void Nuke::initialize_nuke()
{
    int zero = NUKE_STATE_INACTIVE;
    if (state == zero) {
        Sprite** slots = sprite_slots;
        int count = NUKE_SPRITE_SLOT_COUNT;

        orbit_center_z = owner_player->transform.position.z - 5.0f;
        float rate = g_game->subgame.subgame_rate;
        orbit_phase = 0.0f;
        orbit_phase_step = 0.104719758f;
        state = NUKE_STATE_ACTIVE;
        orbit_center_z_step = rate + rate;

        do {
            Sprite* sprite = g_sprite_manager.allocate_sprite(owner_player->player_slot, 0x83, -1, -1);
            *slots = sprite;
            sprite->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
            slots++;

            (*(slots - 1))->progress = 0.0f;
            (*(slots - 1))->progress_step = 0.0f;
            (*(slots - 1))->size_start = 3.0f;
            (*(slots - 1))->size_end = 3.0f;
            Vector3* velocity = &(*(slots - 1))->velocity;
            velocity->z = 0.0f;
            velocity->y = 0.0f;
            velocity->x = 0.0f;
            Vector3* position = &(*(slots - 1))->position;
            position->z = 0.0f;
            position->y = 0.0f;
            position->x = 0.0f;
            (*(slots - 1))->gravity_step = 0.0f;
            count--;
        } while (count);
    }

    update_nuke();
}
