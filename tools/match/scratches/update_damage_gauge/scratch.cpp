// update_damage_gauge @ 0x440fd0 (thiscall, ret)
// Advances the contact-damage gauge state machine and queues its HUD quads.

#include "damage_guage.h"
#include "game_root.h"
#include "sprite.h"
#include "snail_skin.h"
#include "voice_manager.h"
#include "warning.h"

extern GameRoot* g_game; // data_4df904

float sine(float angle);
int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    int flags,
    Color4f* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend);

void DamageGuage::update_damage_gauge()
{
    GameRoot* game = g_game;
    if (!game->subgame.subgame_pause_gate) {
        display_fill = (fill - display_fill) * 0.2f + display_fill;

        if (hit_flash_progress > 0.0f) {
            float next_hit_flash = hit_flash_step + hit_flash_progress;
            hit_flash_progress = next_hit_flash;
            if (next_hit_flash > 1.0f)
                hit_flash_progress = 0.0f;
        }

        switch (state) {
        case 0: {
            if (*(int*)&fill == 0x3f800000) {
                game = g_game;
                if (game->subgame.embedded_player()->attachment_exit_pending
                    || game->subgame.embedded_player()->completion_handoff_active)
                    goto render;
                state = 1;
                warning_transition_progress = 0.0f;
                warning_transition_step = 0.16666667f;
                g_game->subgame.embedded_player()->warning.start_warning();
            }
            goto render_after_refresh;
        }

        case 1: {
            if (g_game->subgame.embedded_player()->completion_handoff_active)
                warning_transition_progress = 1.0f;
            float next_warning = warning_transition_step + warning_transition_progress;
            warning_transition_progress = next_warning;
            if (next_warning >= 1.0f) {
                game = g_game;
                if (*(int*)&game->subgame.embedded_player()->live_matrix.position.y != 0x3efae148)
                    goto render;
                state = 2;
                g_voice_manager.play_voice_manager(14, 0, -1);
            }
            goto render_after_refresh;
        }

        case 2: {
            GameRoot* skin_game = g_game;
            skin_game->subgame.embedded_player()
                ->presentation.snail_skin.change_snail_skin(1, 0.2f);
            apply_damage_gauge_delta(-0.0016666667f, 1);
            skin_hold_ticks = 5;
            game = g_game;
            if (game->subgame.embedded_player()->completion_handoff_active) {
                apply_damage_gauge_delta(-0.0066666668f, 0);
                game = g_game;
            }
            if ((fill == 0.0f
                    && *(int*)&game->subgame.embedded_player()->live_matrix.position.y == 0x3efae148)
                || game->subgame.embedded_player()->completion_handoff_timer > 0.0f
                || game->subgame.embedded_player()->resurrect_progress > 0.0f
                || game->subgame.embedded_player()->presentation.cutscene.state) {
                state = 0;
                g_game->subgame.embedded_player()->warning.stop_warning();
                g_game->subgame.embedded_player()->warning.stop_warning_sample();
                goto render_after_refresh;
            }
            break;
        }

        default:
render_after_refresh:
            game = g_game;
        }
    }

render:
    float alpha;
    float mask_height;
    if (display_fill > 0.99900001f) {
        mask_height = 0.0f;
    } else if (display_fill < 0.0099999998f) {
        mask_height = 396.0f;
    } else {
        mask_height = 351.0f - display_fill * 308.0f;
    }

    if (!game->subgame.subgame_pause_gate)
        pulse_progress = pulse_step + pulse_progress;
    if (pulse_progress > 1.0f)
        pulse_progress = pulse_progress - 1.0f;

    Color4f color;
    if (display_fill > 0.89999998f || state) {
        if (display_fill > 0.89999998f) {
            if (!state)
                alpha = (display_fill - 0.89999998f) * 10.0f;
            else
                alpha = 1.0f;
        } else if (display_fill < 0.1f)
            alpha = display_fill * 10.0f;
        else
            alpha = 1.0f;

        float flash_pulse = (sine(pulse_progress * 6.2831855f) + 1.0f) * 0.5f;
        float flash_alpha = alpha - flash_pulse * alpha * 0.5f;
        queue_axis_aligned_textured_quad_uv(
            91,
            560.0f,
            70.0f,
            64.0f,
            396.0f,
            0x1000000,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, flash_alpha),
            0.0f,
            0.0f,
            1.0f,
            0.7734375f,
            3,
            0);
    }

    float mask_v = mask_height * 0.001953125f;
    queue_axis_aligned_textured_quad_uv(
        89,
        560.0f,
        70.0f,
        64.0f,
        mask_height,
        0x1000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        mask_v,
        3,
        0);

    queue_axis_aligned_textured_quad_uv(
        90,
        560.0f,
        mask_height + 70.0f,
        64.0f,
        396.0f - mask_height,
        0x1000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        mask_v,
        1.0f,
        0.7734375f,
        3,
        0);
}
