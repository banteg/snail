// update_slug_hazard_ai @ 0x43f930 (thiscall, ret)

#include "bod_list.h"
#include "contact_target.h"
#include "font_system.h"
#include "game_root.h"
#include "player.h"
#include "slug_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "voice_manager.h"

extern GameRoot* g_game; // data_4df904

int next_math_random_value();
int report_errorf(char* format, ...);
double random_float_below(float upper_bound, const char* tag);
double random_signed_float_below(float upper_bound, const char* tag);

void Slug::update_slug_hazard_ai()
{
    if (owner_game->subgame_pause_gate != 0)
        return;

    int random_value;
    int side;

    switch (state) {
    case SUB_SLUG_STATE_INACTIVE:
        return;

    case SUB_SLUG_STATE_ACTIVE:
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
                    (float)g_game->subgame.advance_blink_random();
            } else if (blink_progress > 1.0f) {
                blink_progress = 1.0f;
                blink_step = -0.166666672f;
            }
        }

active_state_tail:
        if (owner_player->transform.position.z + 1.0f > transform.position.z
            && player_encounter_latched == 0) {
            player_encounter_latched = 1;
            random_value = next_math_random_value();
            if ((float)random_value * 0.000030517578f > 0.600000024f) {
                random_value = next_math_random_value();
                int variant = (int)((float)random_value * -0.000122070312f);
                play_slug_voice(30 - variant);
            }
        }

        if (transform.position.z < owner_player->transform.position.z && passed_player == 0)
            passed_player = 1;

        if (engagement_voice_gate == 1
            && owner_player->transform.position.z + 16.0f > transform.position.z) {
            engagement_voice_gate = 0;
            g_voice_manager.play_voice_manager(
                VOICE_SET_ENEMIES, VOICE_PLAY_AFTER_GLOBAL_COOLDOWN, -1);
        }

        sprite->position = transform.position;
        if (transform.position.z < owner_player->interaction_max_z) {
            state = SUB_SLUG_STATE_INACTIVE;
            g_game->active_bod_list.remove_bod(this);
            sprite->kill_sprite();
            return;
        }
        if (owner_player->nuke_effect_progress > 0.0f)
            kill_slug_hazard();
        owner_game->enemy_manager.append_subgame_contact_target(
            &transform.position,
            2.0f,
            1,
            (ContactTargetObject*)this);
        goto update_tail;

update_tail:
        sprite->facing_angle = owner_player->heading_roll + attachment_facing_angle;
        if (owner_player->follow_state.active == 1)
            sprite->facing_angle += owner_player->follow_state.orientation_b;
        update_slug_voice_ai();
        return;

    case SUB_SLUG_STATE_LATERAL_ACTIVE:
        lateral_phase = lateral_phase_step + lateral_phase;
        if (lateral_phase > 6.28318548f)
            lateral_phase = lateral_phase - 6.28318548f;
        transform.position.x = sine(lateral_phase) * 3.0f;
        if (transform.position.z < owner_player->transform.position.z && passed_player == 0)
            passed_player = 1;
        sprite->position = transform.position;
        if (transform.position.z < owner_player->interaction_max_z) {
            state = SUB_SLUG_STATE_INACTIVE;
            g_game->active_bod_list.remove_bod(this);
            sprite->kill_sprite();
            return;
        }
        if (owner_player->nuke_effect_progress > 0.0f)
            kill_slug_hazard();
        goto update_tail;

    case SUB_SLUG_STATE_DEATH_TOSS_PENDING: {
        state = SUB_SLUG_STATE_TEARDOWN_PENDING;
        velocity = Vector3(
            (float)random_signed_float_below(0.100000001f, "SDI"),
            (float)random_float_below(0.200000003f, 0) + 0.100000001f,
            (float)random_float_below(0.300000012f, 0));

        double adjusted_x;
        if (death_toss_direction == SUB_SLUG_DEATH_TOSS_RIGHT) {
            adjusted_x = velocity.x < 0.0f
                ? -(double)velocity.x
                : (double)velocity.x;
        } else if (death_toss_direction == SUB_SLUG_DEATH_TOSS_LEFT) {
            adjusted_x = -(velocity.x < 0.0f
                ? -velocity.x
                : velocity.x);
        } else {
            goto direction_adjustment_complete;
        }
        velocity.x = (float)adjusted_x;
direction_adjustment_complete:

        if (velocity.x < 0.0f) {
            side = -1;
        } else {
            side = 0;
            if (velocity.x != 0.0f)
                side = 1;
        }

        velocity.x = (float)side * 0.200000003f + velocity.x;
        *(int*)((char*)this + 0x9c) = 0;
        *(float*)((char*)this + 0xa0) = owner_game->subgame_rate * 0.00833333377f;
        *(int*)((char*)this + 0xa4) = 0;
        *(float*)((char*)this + 0xa8) = owner_game->subgame_rate * 0.166666672f;
    }

    case SUB_SLUG_STATE_TEARDOWN_PENDING:
        state = SUB_SLUG_STATE_INACTIVE;
        g_game->active_bod_list.remove_bod(this);
        sprite->kill_sprite();
        return;

    default:
        goto update_tail;
    }
}
