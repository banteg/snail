// update_garbage_hazard @ 0x43f200 (thiscall, ret)
// cRSubGarbage::AI(): hover/contact registration, nuke/contact burst setup,
// burst integration, smoke cadence, teardown, and final sprite roll update.

#include "garbage_hazard_slot.h"
#include "player.h"
#include "subgame_runtime.h"

double random_signed_float_below(float upper_bound, const char* tag);
double random_float_below(float upper_bound, const char* tag);

void SubGarbage::update_garbage_hazard()
{
    SubgameRuntime* pause_game = owner_game;
    if (!pause_game->subgame_pause_gate) {
        int current_state = state;
        switch ((unsigned int)current_state) {
        case SUB_GARBAGE_STATE_INACTIVE:
            goto function_return;

        case SUB_GARBAGE_STATE_ACTIVE: {
            Vector3* position = &transform.position;
            Vector3* visual_position = &sprite->position;
            *visual_position = *position;

            Player* owner = owner_player;
            if (transform.position.z < owner->interaction_max_z)
            {
                destroy_garbage_hazard();
                return;
            }

            if (owner->nuke_effect_progress > 0.0f) {
                float x = position->x;
                state = SUB_GARBAGE_STATE_BURST_PENDING;
                if (x > 0.0f)
                    collision_side = SUB_GARBAGE_COLLISION_SIDE_RIGHT;
                else
                    collision_side = SUB_GARBAGE_COLLISION_SIDE_LEFT;
                owner->add_subgoldy_score(SUBGOLDY_SCORE_GARBAGE, 0);
            }

            owner_game->enemy_manager.append_subgame_contact_target(
                &transform.position,
                radius,
                0,
                this);
            break;
        }

        case SUB_GARBAGE_STATE_BURST_PENDING: {
            state = SUB_GARBAGE_STATE_BURST;
            Vector3 random_velocity;
            random_velocity.x = (float)random_signed_float_below(0.1f, "GDI");
            random_velocity.y = (float)random_float_below(0.2f, 0) + 0.1f;
            double random_z = random_float_below(0.30000001f, 0);
            SubgameRuntime* rate_game = owner_game;
            Vector3* burst_velocity = &velocity;
            float rate = rate_game->subgame_rate;
            Vector3 staged_velocity;

            staged_velocity.x = rate * random_velocity.x;
            double wide_rate = rate;
            staged_velocity.y = float(random_velocity.y * wide_rate);
            staged_velocity.z = float(random_z * wide_rate);
            *burst_velocity = staged_velocity;

            int side = collision_side;
            if (side == SUB_GARBAGE_COLLISION_SIDE_RIGHT) {
                double adjusted_x = burst_velocity->x < 0.0f
                    ? -(double)burst_velocity->x
                    : (double)burst_velocity->x;
                burst_velocity->x = (float)adjusted_x;
            } else if (side == SUB_GARBAGE_COLLISION_SIDE_LEFT) {
                burst_velocity->x = -(burst_velocity->x < 0.0f
                    ? -burst_velocity->x
                    : burst_velocity->x);
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

        case SUB_GARBAGE_STATE_BURST: {
            Vector3* position = &transform.position;
            Vector3* movement = &velocity;
            float next_x = movement->x + position->x;
            position->x = next_x;
            position->y = movement->y + position->y;
            position->z = movement->z + position->z;

            sprite->position = *position;

            SubgameRuntime* gravity_game = owner_game;
            float gravity_step = gravity_game->subgame_rate
                * gravity_game->subgame_rate
                * -0.0099999998f;
            velocity.y = gravity_step + velocity.y;

            if (transform.position.y < -10.0f
                || transform.position.z < owner_player->interaction_max_z) {
                destroy_garbage_hazard();
                return;
            }

            Player* owner = owner_player;
            float next_smoke_timer = smoke_timer_step + smoke_timer;
            smoke_timer = next_smoke_timer;
            if (next_smoke_timer > 1.0f) {
                smoke_timer = 0.0f;
                spawn_garbage_smoke_particle(&transform.position, &velocity, owner);
            }
            break;
        }

        default:
            break;
        }

        sprite->facing_angle =
            owner_player->heading_roll + attachment_facing_angle;
        Player* roll_result = owner_player;
        if (roll_result->follow_state.active == 1)
            sprite->facing_angle = roll_result->follow_state.orientation_b + sprite->facing_angle;
        return;
    }
function_return:
    return;
}
