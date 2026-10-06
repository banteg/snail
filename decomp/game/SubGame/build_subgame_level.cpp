// build_subgame_level @ 0x437eb0 (thiscall, ret 0x4)

#include "sub_solution.h"
#include "bod_list.h"
#include "damage_guage.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "landscape_manager.h"
#include "sub_tracks.h"
#include "mouse_cursor_state.h"
#include "progress_bar.h"
#include "rmath_random.h"
#include "runtime_config.h"
#include "salt_hazard_types.h"
#include "slug_voice_manager.h"
#include "star_manager.h"
#include "subgame_runtime.h"
#include "sub_lazer_types.h"
#include "track_parcel_runtime.h"
#include "times_up.h"
#include "voice_manager.h"

extern char g_blank_text[];

int gRMathRand2();
char cache_music_file(char* path, int unused, char* unused_default_path);
int report_errorf(char* format, ...);
int sprintf(char* buffer, char* format, ...);
void set_input_controller_pointer_authored_xy(int controller, float x, float y);

void cRSubGame::StartLevel(int level_index)
{
    g_game->star_manager.UnHide();
    if (level_mode == 7)
        HideScores();
    else
        UnHideScores();

    switch ((unsigned int)(
        gRMathRand2() * 0.0000305175781f * 4.0f)) {
    case 0:
        cache_music_file("music/1.ogg", 0, g_blank_text);
        break;
    case 1:
        cache_music_file("music/2.ogg", 0, g_blank_text);
        break;
    case 3:
        cache_music_file("music/4.ogg", 0, g_blank_text);
        break;
    case 2:
    case 4:
        cache_music_file("music/3.ogg", 0, g_blank_text);
        break;
    }

    next_slug_voice_trigger_z = 50.0f;
    slug_voice_trigger_spacing_z = 100.0f;
    enemy_manager.Init();
    player.damage_gauge.Init();
    player.progress_bar.noop_runtime_ai();
    sub_lazers.Init();
    salt_hazards.Init();
    g_voice_manager.ReSet();

    level_definition.load_frontend_level_by_mode_and_index(level_mode, level_index);

    if (selected_level_record_active != 0
        || selected_level_record_persistent != 0) {
        base_rate = selected_level_record->replay_speed_scalar;
        level_mode = selected_level_record->replay_mode_id;
        challenge_difficulty_value =
            selected_level_record->challenge_difficulty_value;
        challenge_speed_value = selected_level_record->challenge_speed_value;
        challenge_difficulty_scalar =
            (float)selected_level_record->challenge_difficulty_value * 0.00999999978f;
    } else {
        int mode = level_mode;
        if (mode == 3) {
            base_rate = g_runtime_config.default_challenge_speed_slider;
        } else if (mode == 0 || mode == 4 || mode == 7) {
            if (level_definition.selected_speed_bits == (int)0xbf800000) {
                base_rate = CalcSliderToRate(0.0f);
            } else {
                float normalized_speed =
                    level_definition.selected_speed * 0.00999999978f;
                base_rate = normalized_speed * 0.900000036f + 0.200000003f;
            }
        } else if (mode == 1) {
            base_rate = CalcSliderToRate(
                (float)g_runtime_config.challenge_speed_percent
                * 0.00999999978f);
            challenge_difficulty_scalar =
                (float)g_runtime_config.challenge_difficulty_percent
                * 0.00999999978f;
        } else if (mode == 2) {
            base_rate = CalcSliderToRate(
                g_runtime_config.default_challenge_speed_slider);
        }
    }

    if (selected_level_record_active != 0
        || selected_level_record_persistent != 0) {
        garbage_frequency = selected_level_record->garbage_frequency;
        salt_frequency = selected_level_record->salt_frequency;
    } else {
        int mode = level_mode;
        if (mode == 2 || mode == 3 || mode == 0 || mode == 4 || mode == 7) {
            garbage_frequency =
                level_definition.garbage_frequency * 0.00999999978f;
            salt_frequency =
                level_definition.salt_frequency * 0.00999999978f;
        } else if (mode == 1) {
            float normalized_garbage_difficulty =
                (float)g_runtime_config.challenge_difficulty_percent
                * 0.00999999978f;
            garbage_frequency =
                normalized_garbage_difficulty * 0.800000012f;
            float normalized_salt_difficulty =
                (float)g_runtime_config.challenge_difficulty_percent
                * 0.00999999978f;
            salt_frequency =
                normalized_salt_difficulty * 0.800000012f;
        }
    }

    parcel_manager.Init();
    if (g_game->intro.hide_for_replay_latch == 1) {
        top_score_widget->HideInit();
        bottom_score_widget->HideInit();
    }

    GenerateLevel(level_index);

    if (level_definition.track_texture_set == 5) {
        int landscape_index;
        switch ((unsigned int)RAND(4.0f, 0)) {
        case 0:
            landscape_index =
                g_game->subgame.landscape_manager
                    .Import("SpaceBluesWhorl.txt");
            break;
        case 1:
            landscape_index =
                g_game->subgame.landscape_manager
                    .Import("SpaceGreenWarp.txt");
            break;
        case 2:
            landscape_index =
                g_game->subgame.landscape_manager
                    .Import("SpacePurple.txt");
            break;
        case 3:
            landscape_index =
                g_game->subgame.landscape_manager
                    .Import("SpaceRed.txt");
            break;
        }

        landscape_manager.Init(landscape_index);
        if (RAND(1.0f, 0) > 0.5f)
            g_game->backdrop.pending_flip = 1;
        else
            g_game->backdrop.pending_flip = 0;
    } else {
        landscape_manager.Init(level_definition.landscape_script_index);
    }

    banners.slots[0].add_bod_after(&track_body_list_head);

    {
        tVector* start_position = &banners.slots[0].position;
        start_position->z = 0.0f;
        start_position->y = 0.0f;
        start_position->x = 0.0f;
    }
    unsigned int start_flags = banners.slots[0].list_flags;
    banners.slots[0].owner_player = &player;
    banners.slots[0].position.z = (float)first_block_row_count;
    banners.slots[0].list_flags = start_flags & ~BOD_FLAG_RENDER_ENABLED;
    banners.slots[0].color.a = 0.999f;

    banners.slots[1].add_bod_after(&track_body_list_head);

    {
        tVector* completion_position = &banners.slots[1].position;
        completion_position->z = 0.0f;
        completion_position->y = 0.0f;
        completion_position->x = 0.0f;
    }
    unsigned int completion_flags = banners.slots[1].list_flags;
    banners.slots[1].owner_player = &player;
    banners.slots[1].position.z = (float)completion_row_start;
    banners.slots[1].list_flags = completion_flags & ~BOD_FLAG_RENDER_ENABLED;
    banners.slots[1].color.a = 0.999f;

    track_state_latch = 0;
    replay_update_cursor = 0;
    times_up.state = TIMES_UP_STATE_INACTIVE;
    subgame_state = 2;

    g_game->render_skip_count = 1;
    g_game->players[0].mouse_cursor.SetInActive();
    player.movement_mode_selector = 1;
    player.steering_mode_selector = 0;
    player.Init(1);

    g_game->active_bod_list.add_bod(
        &player.presentation.jetpack_channel);

    g_game->active_bod_list.add_bod(
        &player.presentation.weapon_channels[0]);

    g_game->active_bod_list.add_bod(
        &player.presentation.weapon_channels[1]);

    g_game->active_bod_list.add_bod(
        &player.presentation.weapon_channels[2]);

    g_game->active_bod_list.add_bod(
        (BodNode*)&player.presentation.invincible_shell);
    player.presentation.invincible_shell.list_flags |= 0x80;

    g_game->active_bod_list.add_bod(
        (BodNode*)&player.presentation);

    g_game->active_bod_list.add_bod((BodNode*)&player);

    slug_voice_manager.Init();

    barrier.add_bod_after(&barrier_sub_lazer_list_head);
    barrier.owner_player = &player;

    if (level_mode == 0) {
        sprintf(lives_text_widget->text_buffer,
            "0/%i", level_definition.parcel_count);
        lives_icon_widget->UnHideInit();
        lives_text_widget->UnHideInit();
    }

    set_input_controller_pointer_authored_xy(0, 320.0f, 240.0f);
    set_input_controller_pointer_authored_xy(1, 320.0f, 240.0f);
    player.track_z_offset = 320.0f;
    player.track_z_anchor = 320.0f;
    scan_reset = 1;
    CalcRate();
}
