// update_damage_gauge @ 0x440fd0 (thiscall, ret)
// Advances the contact-damage gauge state machine and queues its HUD quads.

#include "sprite.h"
#include "snail_skin.h"

struct WarningActor {
    void start_warning(); // @ 0x446f30, matched
    void stop_warning();  // @ 0x446f50, matched
    void stop_warning_sample(); // @ 0x446f60, matched; ecx is ignored

    int state;
    float progress;
    float progress_step;
    void* border;
};

struct VoiceManager {
    int play_voice_manager(int set_id, unsigned int mode, int sample_override); // @ 0x4492d0, matched
};

struct Game {
    char unknown_000000[0x74621];
    unsigned char damage_gauge_suspended; // +0x74621
    char unknown_074622[0x42fde8 - 0x74622];
    int player_ground_height_bits; // +0x42fde8, 0.49f gate
    char unknown_42fdec[0x42fe08 - 0x42fdec];
    float player_exit_gate; // +0x42fe08
    char unknown_42fe0c[0x430170 - 0x42fe0c];
    WarningActor warning; // +0x430170
    char unknown_430180[0x430199 - 0x430180];
    unsigned char follow_live_flag; // +0x430199
    char unknown_43019a[0x4301bc - 0x43019a];
    unsigned char follow_force_drain; // +0x4301bc
    char unknown_4301bd[0x4301c0 - 0x4301bd];
    float follow_exit_gate; // +0x4301c0
    char unknown_4301c4[0x434038 - 0x4301c4];
    SnailSkinTransition snail_skin_transition; // +0x434038
    char unknown_434058[0x434064 - 0x434058];
    int drain_exit_word; // +0x434064
};

extern Game* volatile g_game; // data_4df904
extern VoiceManager g_voice_manager; // 0x751498

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

struct DamageGaugeController {
    void update_damage_gauge();
    void apply_damage_gauge_delta(float delta, char force); // @ 0x4413f0

    int state;                         // +0x00
    float pulse_progress;              // +0x04
    float pulse_step;                  // +0x08
    char unknown_0c[0x10 - 0x0c];
    float warning_transition_progress; // +0x10
    float warning_transition_step;     // +0x14
    int skin_hold_ticks;               // +0x18
    float fill;                        // +0x1c
    float display_fill;                // +0x20
    float hit_flash_progress;          // +0x24
    float hit_flash_step;              // +0x28
};

void DamageGaugeController::update_damage_gauge()
{
    Game* game = g_game;
    if (!game->damage_gauge_suspended) {
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
                if (game->follow_live_flag || game->follow_force_drain)
                    goto render;
                state = 1;
                warning_transition_progress = 0.0f;
                warning_transition_step = 0.16666667f;
                g_game->warning.start_warning();
            }
            goto render_after_refresh;
        }

        case 1: {
            if (g_game->follow_force_drain)
                warning_transition_progress = 1.0f;
            float next_warning = warning_transition_step + warning_transition_progress;
            warning_transition_progress = next_warning;
            if (next_warning >= 1.0f) {
                game = g_game;
                if (game->player_ground_height_bits != 0x3efae148)
                    goto render;
                state = 2;
                g_voice_manager.play_voice_manager(14, 0, -1);
            }
            goto render_after_refresh;
        }

        case 2: {
            Game* skin_game = g_game;
            skin_game->snail_skin_transition.change_snail_skin(1, 0.2f);
            apply_damage_gauge_delta(-0.0016666667f, 1);
            skin_hold_ticks = 5;
            game = g_game;
            if (game->follow_force_drain) {
                apply_damage_gauge_delta(-0.0066666668f, 0);
                game = g_game;
            }
            if ((fill == 0.0f && game->player_ground_height_bits == 0x3efae148)
                || game->follow_exit_gate > 0.0f
                || game->player_exit_gate > 0.0f
                || game->drain_exit_word) {
                state = 0;
                g_game->warning.stop_warning();
                g_game->warning.stop_warning_sample();
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
    if (display_fill <= 0.99900001f) {
        if (display_fill >= 0.0099999998f)
            mask_height = 351.0f - display_fill * 308.0f;
        else
            mask_height = 396.0f;
    } else {
        mask_height = 0.0f;
    }

    if (!game->damage_gauge_suspended)
        pulse_progress = pulse_step + pulse_progress;
    if (pulse_progress > 1.0f)
        pulse_progress = pulse_progress - 1.0f;

    Color4f color;
    if (display_fill > 0.89999998f || state) {
        if (display_fill <= 0.89999998f) {
            if (display_fill < 0.1f)
                alpha = display_fill * 10.0f;
            else
                alpha = 1.0f;
        } else if (!state) {
            alpha = (display_fill - 0.89999998f) * 10.0f;
        } else {
            alpha = 1.0f;
        }

        float flash_alpha = alpha - (sine(pulse_progress * 6.2831855f) + 1.0f) * 0.5f * alpha * 0.5f;
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
