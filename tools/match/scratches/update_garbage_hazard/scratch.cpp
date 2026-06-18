// update_garbage_hazard @ 0x43f200 (thiscall, ret)
// cRSubGarbage::AI(): hover/contact registration, nuke/contact burst setup,
// burst integration, smoke cadence, teardown, and final sprite roll update.

#include "garbage_hazard_slot.h"
#include "player.h"

class Game {
public:
    char unknown_00[0x09];
    unsigned char pause_gate; // +0x09
    char unknown_0a[0x38 - 0x0a];
    float subgame_rate; // +0x38
    char unknown_3c[0x1270fd4 - 0x3c];
    ContactTargetRegistry contact_targets; // +0x1270fd4
};

double random_signed_float_below(float upper_bound, const char* tag);
double random_float_below(float upper_bound, const char* tag);

GarbageHazardSlot* GarbageHazardSlot::update_garbage_hazard()
{
    Game* result = game;
    if (!result->pause_gate) {
        switch (state) {
        case 0:
            return 0;

        case 1: {
            Vector3* position = &world_position;
            Sprite* visual = sprite;
            Vector3* visual_position = &visual->position;
            visual_position->x = position->x;
            visual_position->y = position->y;
            visual_position->z = position->z;

            Player* owner = player;
            if (world_position.z < owner->interaction_max_z)
                return destroy_garbage_hazard();

            if (owner->nuke_effect_progress > 0.0f) {
                float x = position->x;
                state = 2;
                if (x > 0.0f)
                    collision_side = 1;
                else
                    collision_side = 2;
                owner->add_subgoldy_score(0, 0);
            }

            game->contact_targets.append_subgame_contact_target(
                &world_position,
                radius,
                0,
                this);
            break;
        }

        case 2: {
            state = 3;
            float random_x = (float)random_signed_float_below(0.1f, "GDI");
            float random_y = (float)random_float_below(0.2f, 0) + 0.1f;
            double random_z = random_float_below(0.30000001f, 0);
            Game* rate_game = game;
            Vector3* burst_velocity = &velocity;
            double rate = rate_game->subgame_rate;
            Vector3 staged_velocity;

            staged_velocity.x = (float)(rate * random_x);
            staged_velocity.y = (float)(random_y * rate);
            staged_velocity.z = (float)(random_z * rate);
            *burst_velocity = staged_velocity;

            int side = collision_side;
            if (side == 1) {
                float adjusted_x = burst_velocity->x;
                if (adjusted_x < 0.0f)
                    adjusted_x = -adjusted_x;
                burst_velocity->x = adjusted_x;
            } else if (side == 2) {
                float adjusted_x = burst_velocity->x;
                if (adjusted_x < 0.0f)
                    adjusted_x = -adjusted_x;
                burst_velocity->x = -adjusted_x;
            }

            int sign;
            if (burst_velocity->x < 0.0f) {
                sign = -1;
            } else {
                sign = 0;
                if (burst_velocity->x != 0.0f)
                    sign = 1;
            }
            float signed_push = (float)sign * 0.2f;
            signed_push *= rate_game->subgame_rate;
            unknown_a4 = 0;
            burst_velocity->x = signed_push + burst_velocity->x;
            float rate_step = rate_game->subgame_rate * 0.0083333338f;
            smoke_timer = 0.0f;
            burst_rate_step = rate_step;
            smoke_timer_step = rate_game->subgame_rate * 0.27777779f;
        }
            // fall through

        case 3: {
            float next_x = velocity.x + world_position.x;
            Vector3* movement = &velocity;
            Vector3* position = &world_position;
            position->x = next_x;
            position->y = movement->y + position->y;
            position->z = movement->z + position->z;

            sprite->position = *position;

            Game* owner_game = game;
            float gravity_step = owner_game->subgame_rate
                * owner_game->subgame_rate
                * -0.0099999998f;
            velocity.y = gravity_step + velocity.y;

            if (world_position.y < -10.0f || world_position.z < player->interaction_max_z)
                return destroy_garbage_hazard();

            Player* owner = player;
            float next_smoke_timer = smoke_timer_step + smoke_timer;
            smoke_timer = next_smoke_timer;
            if (next_smoke_timer > 1.0f) {
                smoke_timer = 0.0f;
                spawn_garbage_smoke_particle(&world_position, &velocity, owner);
            }
            break;
        }

        default:
            break;
        }

        sprite->facing_angle = player->heading_roll + sprite_y_offset;
        Player* roll_result = player;
        if (roll_result->follow_active == 1)
            sprite->facing_angle = roll_result->follow_orientation_b + sprite->facing_angle;
        return (GarbageHazardSlot*)roll_result;
    }
    return (GarbageHazardSlot*)result;
}
