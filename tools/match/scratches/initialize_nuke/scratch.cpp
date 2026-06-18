// initialize_nuke @ 0x447110 (thiscall, ret)

#include "game.h"
#include "nuke_controller.h"
#include "player.h"

extern Game* g_game_base; // data_4df904

int NukeController::initialize_nuke()
{
    int zero = 0;
    if (state == zero) {
        Sprite** slots = sprite_slots;
        int count = 25;

        orbit_center_z = owner_player->position.z - 5.0f;
        float rate = g_game_base->subgame_rate;
        orbit_phase = 0.0f;
        orbit_phase_step = 0.104719758f;
        state = 1;
        orbit_center_z_step = rate + rate;

        do {
            Sprite* sprite = g_sprite_manager.allocate_sprite(owner_player->player_slot, 0x83, -1, -1);
            *slots = sprite;
            sprite->flags |= 0x800;
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

    return update_nuke();
}
