// update_cutscene @ 0x4466d0 (thiscall, ret)

#include "audio_system.h"
#include "completion_screen.h"
#include "font_system.h"
#include "player.h"
#include "voice_manager.h"

extern char g_player_intro_cutscene_latch_offset[]; // 0x42fec4 = g_player_block + 0x148

void CutsceneAI::update_cutscene()
{
    int current_state = state;
    force_camera_update = 0;

    TransformMatrix look_at_matrix;
    TransformMatrix source_matrix;
    Vector3 target_delta;
    Vector3 skid_stop;
    Vector3 intro_talk;

    switch (current_state) {
    case 1:
        state = 2;
        progress = 0.0f;
        progress_step = 0.00833333377f;
        force_camera_update = 1;
        presentation->dispatch_cutscene_animation(9, 1, -1);
        presentation->dispatch_cutscene_animation(9, 0, -1);
        presentation->dispatch_cutscene_animation(1, 0, -1);
        // fall through

    case 2:
        camera_mode = 1;
        set_matrix_identity(&live_matrix);
        live_matrix.position = presentation->snail_hotspots_world[18];
        live_matrix.look_at_point(&presentation->live_matrix.position);
        progress = progress + progress_step;
        if (progress > 1.0f) {
            progress_step = 0.00833333377f;
            state = 8;
            progress = 0.0f;
        }
        return;

    case 8: {
        *(g_player_intro_cutscene_latch_offset + (int)g_game_base) = 0;
        camera_mode = 1;

        set_matrix_identity(&look_at_matrix);
        look_at_matrix.position = presentation->snail_hotspots_world[18];
        float swing = sine(progress * 3.1415927f);
        look_at_matrix.position.x = swing + swing + look_at_matrix.position.x;
        look_at_matrix.look_at_point(&presentation->live_matrix.position);

        source_matrix = *(TransformMatrix*)((char*)presentation->owner_player + 0x200);
        float alpha = sine(progress * 1.5707964f);
        live_matrix.linear_interpolate_matrix(&look_at_matrix, &source_matrix, alpha);

        target_delta.x = live_matrix.position.x - presentation->live_matrix.position.x;
        target_delta.y = live_matrix.position.y - presentation->live_matrix.position.y;
        target_delta.z = live_matrix.position.z - presentation->live_matrix.position.z;
        float distance = target_delta.normalize_vector();
        if (distance < 1.5f) {
            float push = 1.5f - distance;
            live_matrix.position.x = target_delta.x * push + live_matrix.position.x;
            live_matrix.position.y = target_delta.y * push + live_matrix.position.y;
            live_matrix.position.z = push * target_delta.z + live_matrix.position.z;
        }

        progress = progress + progress_step;
        if (progress > 1.0f) {
            state = 9;
            progress = 0.0f;
            progress_step = 0.00833333377f;
        }
        return;
    }

    case 9:
        live_matrix = *(TransformMatrix*)((char*)presentation->owner_player + 0x200);
        state = 0;
        return;

    case 10:
        camera_mode = -1;
        presentation->dispatch_cutscene_animation(7, 1, -1);
        state = 11;
        progress = 0.0f;
        progress_step = 0.00833333377f;
        force_camera_update = 1;
        g_voice_manager.play_voice_manager(3, 2, -1);
        presentation->owner_player->attachment_exit_gate_a = 1;
        presentation->release_snail_weapons();
        // fall through

    case 11: {
        camera_mode = -1;
        set_matrix_identity(&look_at_matrix);
        look_at_matrix.position = presentation->snail_hotspots_world[18];
        float swing = sine(progress * 3.1415927f);
        look_at_matrix.position.x = swing + swing + look_at_matrix.position.x;
        if (look_at_matrix.position.y < 0.0f)
            look_at_matrix.position.y = 0.0f;
        look_at_matrix.look_at_point(&presentation->live_matrix.position);

        source_matrix = *(TransformMatrix*)((char*)presentation->owner_player + 0x200);
        float alpha = sine(progress * 1.5707964f);
        live_matrix.linear_interpolate_matrix(&source_matrix, &look_at_matrix, alpha);

        progress = progress + progress_step;
        if (progress > 1.0f) {
            state = 12;
            progress = 0.0f;
            progress_step = 0.0166666675f;
        }
        break;
    }

    case 12:
        camera_mode = -1;
        force_camera_update = 1;
        set_matrix_identity(&live_matrix);
        live_matrix.position = presentation->snail_hotspots_world[18];
        if (live_matrix.position.y < 0.0f)
            live_matrix.position.y = 0.0f;
        live_matrix.look_at_point(&presentation->live_matrix.position);

        if (player->resurrect_active != 0 || (player->initialize_subgoldy_death(), player->attachment_exit_gate_b != 0)) {
            progress = progress_step + progress;
        } else {
            g_voice_manager.play_voice_manager(11, 2, -1);
            player->attachment_exit_gate_b = 1;
            player->attachment_exit_gate_a = 1;
            progress = progress_step + progress;
        }
        break;

    case 5: {
        state = 7;
        camera_mode = -1;
        presentation->dispatch_cutscene_animation(8, 1, -1);
        presentation->dispatch_cutscene_animation(9, 0, -1);
        presentation->dispatch_cutscene_animation(9, 0, -1);

        state = 6;
        progress = 0.0f;
        progress_step = 0.00833333377f;
        presentation->invincible_shell.cutscene_roll_step = 0.0166666675f;
        presentation->invincible_shell.cutscene_roll_progress =
            presentation->invincible_shell.cutscene_roll_step;
        force_camera_update = 1;

        int delivered_count = player->parcels_collected;
        CompletionResultScreen* completion_screen =
            (CompletionResultScreen*)(g_game_base + 0x12e6df0);
        CompletionGameView* game = (CompletionGameView*)g_game_base;
        if (game->selected_subgame_mode != 0) {
            if (game->selected_subgame_mode == 1)
                completion_screen->initialize_completion_screen(delivered_count, 1);
        } else {
            completion_screen->initialize_completion_screen(
                delivered_count,
                delivered_count == *(int*)(g_game_base + 0x2247f8));
        }
        g_sound_effect_manager.play_sound_effect(46);
        // fall through
    }

    case 6: {
        camera_mode = -1;
        set_matrix_identity(&look_at_matrix);

        skid_stop = presentation->snail_hotspots_world[12];
        intro_talk = presentation->snail_hotspots_world[18];
        float blend_x = (intro_talk.x - skid_stop.x) * progress + skid_stop.x;
        float blend_y = (intro_talk.y - skid_stop.y) * progress + skid_stop.y;
        float blend_z = (intro_talk.z - skid_stop.z) * progress + skid_stop.z;
        look_at_matrix.position.x = blend_x;
        look_at_matrix.position.y = blend_y;
        look_at_matrix.position.z = blend_z;

        float skid_arc = sine(progress * 3.1415927f);
        look_at_matrix.position.x = look_at_matrix.position.x - skid_arc * 0.5f;
        look_at_matrix.look_at_point(&presentation->live_matrix.position);

        source_matrix = *(TransformMatrix*)((char*)presentation->owner_player + 0x200);
        float alpha = sine(progress * 1.5707964f);
        live_matrix.linear_interpolate_matrix(&source_matrix, &look_at_matrix, alpha);

        progress = progress + progress_step;
        if (progress > 1.0f) {
            state = 7;
            progress = 0.0f;
            progress_step = 0.0166666675f;
        }
        return;
    }

    case 7:
        camera_mode = -1;
        force_camera_update = 1;
        set_matrix_identity(&live_matrix);
        live_matrix.position = presentation->snail_hotspots_world[18];
        live_matrix.look_at_point(&presentation->live_matrix.position);
        if (presentation->anim_manager.queue_count == 0)
            presentation->dispatch_cutscene_animation(9, 0, -1);
        progress = progress + progress_step;
        break;

    default:
        return;
    }
}
