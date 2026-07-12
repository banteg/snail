// update_ring_or_special_effect_parent @ 0x43e830 (thiscall, void)

#include "game_root.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(const char* format, ...);
float sine(float radians);

void SubRing::update_ring_or_special_effect_parent()
{
    RingEffectRateSource* rate = rate_source;
    if (rate->subgame_pause_gate != 0)
        return;

    star_shower_counter++;
    if (star_shower_counter == 3)
        star_shower_counter = 0;

    int current_state = state;
    if ((unsigned int)current_state > 5)
        return;

    switch (current_state) {
    case 0:
        return;

    case 1:
        if (oscillate_x != 0) {
            float phase = active_phase + active_phase_step;
            active_phase = phase;
            if (phase > 6.28318548f) {
                active_phase = phase - 6.28318548f;
            } else if (phase < 0.0f) {
                active_phase = phase + 6.28318548f;
            }
            transform.position.x = sine(active_phase) * 3.0f;
        }

        {
        SubRingStar* particle = particles;
        int count = 10;
        do {
            particle->update_ring_or_special_effect_particle();
            particle++;
            count--;
        } while (count != 0);
        }

        if (transform.position.z < owner_player->interaction_max_z) {
            state = 0;
            g_game->active_bod_list.remove_bod(this);

            SubRingStar* particle =
                particles;
            int count = 10;
            do {
                particle->sprite->kill_sprite();
                particle++;
                count--;
            } while (count != 0);
            return;
        } else {
            int current_lives = owner_player->lives;
            if (current_lives < owner_lives_snapshot)
                state = 4;
            return;
        }

    case 2:
        state = 3;
        transition_progress = 0.0f;
        transition_step = rate->subgame_rate * 0.0694444478f;
        // fall through

    case 3:
        {
        SubRingStar* particle = particles;
        int count = 10;
        do {
            particle->update_ring_or_special_effect_particle();
            particle++;
            count--;
        } while (count != 0);
        }

        transition_progress += transition_step;
        if (transition_progress > 1.0f) {
            state = 0;
            g_game->active_bod_list.remove_bod(this);

            SubRingStar* particle =
                particles;
            int count = 10;
            do {
                particle->sprite->kill_sprite();
                particle++;
                count--;
            } while (count != 0);
            return;
        } else {
            int count = 0;
            Vector3* target_source =
                &owner_player->cached_camera_target_world;
            Vector3 target_position;
            target_position.x = target_source->x;
            target_position.z = target_source->z + 0.200000003f;
            target_position.y = target_source->y;
            Vector3* current_position = &transform.position;
            Vector3 delta;
            delta.x = target_position.x - current_position->x;
            delta.y = target_position.y - current_position->y;
            delta.z = target_position.z - current_position->z;
            Vector3 scaled_delta;
            scaled_delta.x = delta.x * 0.939999998f;
            scaled_delta.y = delta.y * 0.939999998f;
            scaled_delta.z = delta.z * 0.939999998f;
            current_position->x += scaled_delta.x;
            current_position->y += scaled_delta.y;
            current_position->z += scaled_delta.z;

            do {
                particles[count].radius *= 0.939999998f;
                particles[count].base_position = *current_position;
                count++;
            } while (count < 10);
            return;
        }

    case 4:
        state = 5;
        transition_progress = 0.0f;
        transition_step = rate->subgame_rate * 0.0694444478f;
        // fall through

    case 5:
        {
        SubRingStar* particle = particles;
        int count = 10;
        do {
            particle->update_ring_or_special_effect_particle();
            particle++;
            count--;
        } while (count != 0);
        }

        transition_progress += transition_step;
        if (transition_progress > 1.0f) {
            state = 0;
            g_game->active_bod_list.remove_bod(this);

            SubRingStar* particle =
                particles;
            int count = 10;
            do {
                particle->sprite->kill_sprite();
                particle++;
                count--;
            } while (count != 0);
            return;
        } else {
            int count = 0;
            do {
                particles[count].radius *= 1.10000002f;
                particles[count].base_position = transform.position;
                count++;
            } while (count < 10);
            return;
        }

    default:
        break;
    }

    return;
}
