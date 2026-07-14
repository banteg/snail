// update_cutscene @ 0x4466d0 (thiscall, ret)

#include <stddef.h>

#include "audio_system.h"
#include "completion.h"
#include "font_system.h"
#include "game_root.h"
#include "player.h"
#include "voice_manager.h"

extern GameRoot* g_game; // data_4df904

enum {
    LEVEL_PARCEL_COUNT_FROM_GAME_ROOT =
        offsetof(GameRoot, subgame)
        + offsetof(SubgameRuntime, level_definition)
        + offsetof(SubTracks, parcel_count),
};

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

void CutScene::update_cutscene()
{
    int current_state = state;
    force_camera_update = 0;

    TransformMatrix camera_matrix_a;
    TransformMatrix camera_matrix_b;
    Vector3 target_delta;
    Vector3 completion_delta;

    switch (current_state) {
    case 1:
        state = 2;
        progress = 0.0f;
        progress_step = 0.00833333377f;
        force_camera_update = 1;
        presentation->dispatch_cutscene_animation(
            9, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
        presentation->dispatch_cutscene_animation(
            9, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
        presentation->dispatch_cutscene_animation(
            1, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
        // fall through

    case 2:
        camera_mode = 1;
        set_matrix_identity(&live_matrix);
        live_matrix.position = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_INTRO_TALK];
        live_matrix.look_at_point(presentation->transform.position);
        progress = progress + progress_step;
        if (progress > 1.0f) {
            progress_step = 0.00833333377f;
            state = 8;
            progress = 0.0f;
        }
        return;

    case 8: {
        g_game->subgame.embedded_player()->click_start.hide_prompt = 0;
        camera_mode = 1;

        set_matrix_identity(&camera_matrix_a);
        camera_matrix_a.position = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_INTRO_TALK];
        float swing = sine(progress * 3.1415927f);
        camera_matrix_a.position.x = swing + swing + camera_matrix_a.position.x;
        camera_matrix_a.look_at_point(presentation->transform.position);

        camera_matrix_b = presentation->owner_player->cameraman.live_matrix;
        live_matrix.linear_interpolate_matrix(
            camera_matrix_a,
            camera_matrix_b,
            sine(progress * 1.5707964f));

        target_delta = live_matrix.position - presentation->transform.position;
        float distance = target_delta.normalize_vector();
        if (distance < 1.5f) {
            float push = 1.5f - distance;
            live_matrix.position += target_delta * push;
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
        live_matrix = presentation->owner_player->cameraman.live_matrix;
        state = 0;
        return;

    case 10:
        camera_mode = -1;
        presentation->dispatch_cutscene_animation(
            7, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
        state = 11;
        progress = 0.0f;
        progress_step = 0.00833333377f;
        force_camera_update = 1;
        g_voice_manager.play_voice_manager(
            VOICE_SET_FALL, VOICE_PLAY_INTERRUPT, -1);
        presentation->owner_player->attachment_exit_gate_a = 1;
        presentation->release_snail_weapons();
        // fall through

    case 11: {
        camera_mode = -1;
        set_matrix_identity(&camera_matrix_b);
        camera_matrix_b.position = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_INTRO_TALK];
        float swing = sine(progress * 3.1415927f);
        camera_matrix_b.position.x = swing + swing + camera_matrix_b.position.x;
        if (camera_matrix_b.position.y < 0.0f)
            camera_matrix_b.position.y = 0.0f;
        camera_matrix_b.look_at_point(presentation->transform.position);

        camera_matrix_a = presentation->owner_player->cameraman.live_matrix;
        live_matrix.linear_interpolate_matrix(
            camera_matrix_a,
            camera_matrix_b,
            sine(progress * 1.5707964f));

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
        live_matrix.position = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_INTRO_TALK];
        if (live_matrix.position.y < 0.0f)
            live_matrix.position.y = 0.0f;
        live_matrix.look_at_point(presentation->transform.position);

        if (player->resurrect_active != 0 || (player->initialize_subgoldy_death(), player->attachment_exit_gate_b != 0)) {
            progress = progress_step + progress;
        } else {
            g_voice_manager.play_voice_manager(
                VOICE_SET_SLUGGED, VOICE_PLAY_INTERRUPT, -1);
            player->attachment_exit_gate_b = 1;
            player->attachment_exit_gate_a = 1;
            progress = progress_step + progress;
        }
        break;

    case 5: {
        state = 7;
        camera_mode = -1;
        presentation->dispatch_cutscene_animation(
            8, 1, OBJECT_ANIMATION_MODE_UNCHANGED);
        presentation->dispatch_cutscene_animation(
            9, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
        presentation->dispatch_cutscene_animation(
            9, 0, OBJECT_ANIMATION_MODE_UNCHANGED);

        state = 6;
        progress = 0.0f;
        progress_step = 0.00833333377f;
        presentation->invincible_shell.cutscene_roll_step = 0.0166666675f;
        presentation->invincible_shell.cutscene_roll_progress =
            presentation->invincible_shell.cutscene_roll_step;
        force_camera_update = 1;

        GameRoot* game = (GameRoot*)g_game_base;
        if (game->subgame.level_mode == 0) {
            int delivered_count = player->parcels_collected;
            unsigned char perfect_delivery =
                delivered_count
                == *(int*)(g_game_base + LEVEL_PARCEL_COUNT_FROM_GAME_ROOT);
            game->subgame.completion.initialize_completion_screen(
                delivered_count,
                perfect_delivery);
        } else if (game->subgame.level_mode == 1) {
            int delivered_count = player->parcels_collected;
            game->subgame.completion.initialize_completion_screen(delivered_count, 1);
        }
        g_sound_effect_manager.play_sound_effect(46);
        // fall through
    }

    case 6: {
        camera_mode = -1;
        set_matrix_identity(&camera_matrix_b);

        camera_matrix_a.position = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_SKID_STOP];
        completion_delta = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_INTRO_TALK];
        completion_delta.x -= camera_matrix_a.position.x;
        completion_delta.y -= camera_matrix_a.position.y;
        completion_delta.z -= camera_matrix_a.position.z;
        camera_matrix_b.position =
            completion_delta * progress
            + camera_matrix_a.position;

        float skid_arc = sine(progress * 3.1415927f);
        camera_matrix_b.position.x = camera_matrix_b.position.x - skid_arc * 0.5f;
        camera_matrix_b.look_at_point(presentation->transform.position);

        camera_matrix_a = presentation->owner_player->cameraman.live_matrix;
        live_matrix.linear_interpolate_matrix(
            camera_matrix_a,
            camera_matrix_b,
            sine(progress * 1.5707964f));

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
        live_matrix.position = presentation->snail_hotspots_world[
            SNAIL_HOTSPOT_CAMERA_INTRO_TALK];
        live_matrix.look_at_point(presentation->transform.position);
        if (presentation->anim_manager.queue_count == 0)
            presentation->dispatch_cutscene_animation(
                9, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
        progress = progress + progress_step;
        break;

    default:
        return;
    }
}
