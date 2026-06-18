// update_ring_or_special_effect_parent @ 0x43e830 (thiscall, void)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

extern char* g_game_base; // data_4df904

int report_errorf(const char* format, ...);
float sine(float radians);

void RingOrSpecialEffectParent::update_ring_or_special_effect_parent()
{
    RingEffectRateSource* rate = rate_source;
    if (rate->pause_gate != 0)
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
        RingOrSpecialEffectParticle* particle = particles;
        int count = 10;
        do {
            particle->update_ring_or_special_effect_particle();
            particle++;
            count--;
        } while (count != 0);
        }

        if (transform.position.z < owner_player->interaction_max_z) {
            state = 0;
            RingOrSpecialEffectListAnchor* list =
                (RingOrSpecialEffectListAnchor*)(g_game_base + 0x5a8);

            if ((list_flags & 0x200) == 0) {
                report_errorf("List remove");
            } else if ((list_flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
            } else {
                if (list_next != 0)
                    ((RingOrSpecialEffectParent*)list_next)->list_prev = list_prev;
                if (list_prev != 0)
                    ((RingOrSpecialEffectParent*)list_prev)->list_next = list_next;
                else
                    list->first = list_next;
                list_next = list->free_top;
                list->free_top = this;
                list_flags &= ~0x200u;
            }

            RingOrSpecialEffectParticle* particle =
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
        RingOrSpecialEffectParticle* particle = particles;
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
            RingOrSpecialEffectListAnchor* list =
                (RingOrSpecialEffectListAnchor*)(g_game_base + 0x5a8);

            if ((list_flags & 0x200) == 0) {
                report_errorf("List remove");
            } else if ((list_flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
            } else {
                if (list_next != 0)
                    ((RingOrSpecialEffectParent*)list_next)->list_prev = list_prev;
                if (list_prev != 0)
                    ((RingOrSpecialEffectParent*)list_prev)->list_next = list_next;
                else
                    list->first = list_next;
                list_next = list->free_top;
                list->free_top = this;
                list_flags &= ~0x200u;
            }

            RingOrSpecialEffectParticle* particle =
                particles;
            int count = 10;
            do {
                particle->sprite->kill_sprite();
                particle++;
                count--;
            } while (count != 0);
            return;
        } else {
            Vector3 target = owner_player->cached_camera_target_world;
            Vector3 delta;
            delta.x = target.x - transform.position.x;
            delta.y = target.y - transform.position.y;
            delta.z = (target.z + 0.200000003f) - transform.position.z;
            delta.x *= 0.939999998f;
            delta.y *= 0.939999998f;
            delta.z *= 0.939999998f;
            transform.position.x += delta.x;
            transform.position.y += delta.y;
            transform.position.z += delta.z;

            int count = 10;
            RingOrSpecialEffectParticle* particle =
                particles;
            do {
                particle->radius *= 0.939999998f;
                particle->base_position = transform.position;
                particle++;
                count--;
            } while (count != 0);
            return;
        }

    case 4:
        state = 5;
        transition_progress = 0.0f;
        transition_step = rate->subgame_rate * 0.0694444478f;
        // fall through

    case 5:
        {
        RingOrSpecialEffectParticle* particle = particles;
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
            RingOrSpecialEffectListAnchor* list =
                (RingOrSpecialEffectListAnchor*)(g_game_base + 0x5a8);

            if ((list_flags & 0x200) == 0) {
                report_errorf("List remove");
            } else if ((list_flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
            } else {
                if (list_next != 0)
                    ((RingOrSpecialEffectParent*)list_next)->list_prev = list_prev;
                if (list_prev != 0)
                    ((RingOrSpecialEffectParent*)list_prev)->list_next = list_next;
                else
                    list->first = list_next;
                list_next = list->free_top;
                list->free_top = this;
                list_flags &= ~0x200u;
            }

            RingOrSpecialEffectParticle* particle =
                particles;
            int count = 10;
            do {
                particle->sprite->kill_sprite();
                particle++;
                count--;
            } while (count != 0);
            return;
        } else {
            int count = 10;
            RingOrSpecialEffectParticle* particle =
                particles;
            do {
                particle->radius *= 1.10000002f;
                particle->base_position = transform.position;
                particle++;
                count--;
            } while (count != 0);
            return;
        }

    default:
        break;
    }

    return;
}
