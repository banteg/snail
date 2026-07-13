// update_slug_hazard_ai @ 0x43f930 (thiscall, ret)

#include "bod_list.h"
#include "contact_target.h"
#include "font_system.h"
#include "player.h"
#include "slug_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "voice_manager.h"

typedef unsigned int DWORD;

extern char* g_game_base; // data_4df904

int next_math_random_value();
int report_errorf(char* format, ...);
double random_float_below(float upper_bound, const char* tag);
double random_signed_float_below(float upper_bound, const char* tag);

#define REMOVE_SLUG_FROM_BOD_LIST_AND_KILL()                         \
    do {                                                             \
        state = 0;                                                   \
        BodList* list = (BodList*)(g_game_base + 0x5a8);             \
        DWORD flags = list_flags;                                    \
        if ((flags & 0x200) == 0) {                                  \
            report_errorf("List remove");                           \
            sprite->kill_sprite();                                   \
            return;                                                  \
        }                                                           \
        if ((flags & 0x40) != 0) {                                   \
            report_errorf("List remove NEXTBOD");                   \
            sprite->kill_sprite();                                   \
            return;                                                  \
        }                                                           \
        BodNode* next = list_next;                                   \
        if (next != 0)                                               \
            next->list_prev = list_prev;                             \
        BodNode* prev = list_prev;                                   \
        if (prev != 0)                                               \
            prev->list_next = list_next;                             \
        else                                                         \
            list->first = list_next;                                 \
        list_next = list->free_top;                                  \
        list->free_top = this;                                       \
        DWORD updated = list_flags;                                  \
        updated &= ~0x200u;                                          \
        list_flags = updated;                                        \
        sprite->kill_sprite();                                       \
        return;                                                      \
    } while (0)

void Slug::update_slug_hazard_ai()
{
    if (owner_game->subgame_pause_gate != 0)
        return;

    int random_value;
    int side;
    Vector3 random_velocity;

    switch (state) {
    case 0:
        return;

    case 1:
        if (hit_flash_pending != 0 && g_render_queue_active != 0) {
            hit_flash_pending = 0;
            hit_flash_progress = hit_flash_progress_step;
        }

        if (hit_flash_progress != 0.0f) {
            float next_flash = hit_flash_progress_step + hit_flash_progress;
            hit_flash_progress = next_flash;
            if (next_flash > 1.0f) {
                hit_flash_progress = 0.0f;
                blink_progress = 1.0f;
                blink_step = -0.166666672f;
                sprite->draw_mode = 0;
                sprite->color.store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
                sprite->set_sprite_texture_ref(0x77, 0);
            } else {
                sprite->draw_mode = 5;
                sprite->set_sprite_texture_ref(0x78, 0);
                sprite->color.store_color4f(1.0f, 0.0f, 0.0f, 0.99000001f);
                goto active_state_tail;
            }
        } else {
            blink_progress = blink_step + blink_progress;
            if (blink_step > 0.0f) {
                sprite->set_sprite_texture_ref(0x76, 0);
                sprite->draw_mode = 0;
            } else {
                sprite->set_sprite_texture_ref(0x77, 0);
                sprite->draw_mode = 0;
            }
            sprite->color.store_color4f(1.0f, 1.0f, 1.0f, 1.0f);

            if (blink_progress < 0.0f) {
                blink_progress = 0.0f;
                blink_step =
                    (float)((SubgameRuntime*)(g_game_base + 0x74618))
                        ->advance_blink_random();
            } else if (blink_progress > 1.0f) {
                blink_progress = 1.0f;
                blink_step = -0.166666672f;
            }
        }

active_state_tail:
        if (player->position.z + 1.0f > transform.position.z
            && player_encounter_latched == 0) {
            player_encounter_latched = 1;
            random_value = next_math_random_value();
            if ((float)random_value * 0.000030517578f > 0.600000024f) {
                random_value = next_math_random_value();
                int variant = (int)((float)random_value * -0.000122070312f);
                play_slug_voice(30 - variant);
            }
        }

        if (transform.position.z < player->position.z && passed_player == 0)
            passed_player = 1;

        if (engagement_voice_gate == 1
            && player->position.z + 16.0f > transform.position.z) {
            engagement_voice_gate = 0;
            g_voice_manager.play_voice_manager(2, 1, -1);
        }

        sprite->position = transform.position;
        if (transform.position.z < player->interaction_max_z) {
            REMOVE_SLUG_FROM_BOD_LIST_AND_KILL();
        }
        if (player->nuke_effect_progress > 0.0f)
            kill_slug_hazard();
        owner_game->enemy_manager.append_subgame_contact_target(
            &transform.position,
            2.0f,
            1,
            (ContactTargetObject*)this);
        break;

    case 4:
        lateral_phase = lateral_phase_step + lateral_phase;
        if (lateral_phase > 6.28318548f)
            lateral_phase = lateral_phase - 6.28318548f;
        transform.position.x = sine(lateral_phase) * 3.0f;
        if (transform.position.z < player->position.z && passed_player == 0)
            passed_player = 1;
        sprite->position = transform.position;
        if (transform.position.z < player->interaction_max_z) {
            REMOVE_SLUG_FROM_BOD_LIST_AND_KILL();
        }
        if (player->nuke_effect_progress > 0.0f)
            kill_slug_hazard();
        owner_game->enemy_manager.append_subgame_contact_target(
            &transform.position,
            2.0f,
            1,
            (ContactTargetObject*)this);
        break;

    case 2: {
        state = 3;
        random_velocity.z = (float)random_float_below(0.300000012f, 0);
        random_velocity.y =
            (float)random_float_below(0.200000003f, 0) + 0.100000001f;
        random_velocity.x =
            (float)random_signed_float_below(0.100000001f, "SDI");
        velocity = random_velocity;

        if (death_toss_direction == 1) {
            if (velocity.x < 0.0f)
                velocity.x = -velocity.x;
        } else if (death_toss_direction == 2) {
            if (velocity.x > 0.0f)
                velocity.x = -velocity.x;
        }

        side = 0;
        if (velocity.x < 0.0f)
            side = -1;
        else if (velocity.x > 0.0f)
            side = 1;

        velocity.x = (float)side * 0.200000003f + velocity.x;
        *(int*)((char*)this + 0x9c) = 0;
        *(float*)((char*)this + 0xa0) = owner_game->subgame_rate * 0.00833333377f;
        *(int*)((char*)this + 0xa4) = 0;
        *(float*)((char*)this + 0xa8) = owner_game->subgame_rate * 0.166666672f;
        REMOVE_SLUG_FROM_BOD_LIST_AND_KILL();
    }

    case 3:
        REMOVE_SLUG_FROM_BOD_LIST_AND_KILL();

    default:
        break;
    }

    sprite->facing_angle = player->heading_roll + attachment_facing_angle;
    if (player->follow_active == 1)
        sprite->facing_angle += player->follow_orientation_b;
    update_slug_voice_ai();
}
