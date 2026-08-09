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

int next_math_random_value();
char cache_music_file(char* path, int unused, char* unused_default_path);
int report_errorf(char* format, ...);
int sprintf(char* buffer, char* format, ...);
void set_input_controller_pointer_authored_xy(int controller, float x, float y);

void cRSubGame::StartLevel(int level_index)
{
    g_game->star_manager.unhide_star_field();
    if (level_mode == 7)
        HideScores();
    else
        UnHideScores();

    int zero = 0;
    switch ((unsigned int)(
        next_math_random_value() * 0.0000305175781f * 4.0f)) {
    case 0:
        cache_music_file("music/1.ogg", zero, g_blank_text);
        break;
    case 1:
        cache_music_file("music/2.ogg", zero, g_blank_text);
        break;
    case 3:
        cache_music_file("music/4.ogg", zero, g_blank_text);
        break;
    case 2:
    case 4:
        cache_music_file("music/3.ogg", zero, g_blank_text);
        break;
    }

    next_slug_voice_trigger_z = 50.0f;
    slug_voice_trigger_spacing_z = 100.0f;
    enemy_manager.initialize_enemy_manager();
    player.damage_gauge.Init();
    player.progress_bar.noop_runtime_ai();
    sub_lazers.Init();
    salt_hazards.Init();
    g_voice_manager.reset_voice_manager();

    level_definition.load_frontend_level_by_mode_and_index(level_mode, level_index);

    if (selected_level_record_active != zero
        || selected_level_record_persistent != zero) {
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

    if (selected_level_record_active != zero
        || selected_level_record_persistent != zero) {
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
        top_score_widget->hide_border_init();
        bottom_score_widget->hide_border_init();
    }

    GenerateLevel(level_index);

    if (level_definition.track_texture_set == 5) {
        int landscape_index;
        switch ((unsigned int)random_float_below(4.0f, 0)) {
        case 0:
            landscape_index =
                g_game->subgame.landscape_manager
                    .load_landscape_script_by_name("SpaceBluesWhorl.txt");
            break;
        case 1:
            landscape_index =
                g_game->subgame.landscape_manager
                    .load_landscape_script_by_name("SpaceGreenWarp.txt");
            break;
        case 2:
            landscape_index =
                g_game->subgame.landscape_manager
                    .load_landscape_script_by_name("SpacePurple.txt");
            break;
        case 3:
            landscape_index =
                g_game->subgame.landscape_manager
                    .load_landscape_script_by_name("SpaceRed.txt");
            break;
        default:
            landscape_index = level_index;
            break;
        }

        landscape_manager.activate_landscape_entry(landscape_index);
        if (random_float_below(1.0f, 0) > 0.5f)
            g_game->backdrop.pending_flip = 1;
        else
            g_game->backdrop.pending_flip = (unsigned char)zero;
    } else {
        landscape_manager.activate_landscape_entry(level_definition.landscape_script_index);
    }

    BodNode* track_bod_list = &track_body_list_head;
    banners.slots[0].add_bod_after(track_bod_list);

    {
        tVector* start_position = &banners.slots[0].position;
        start_position->z = 0.0f;
        start_position->y = 0.0f;
        start_position->x = 0.0f;
    }
    unsigned int start_flags = banners.slots[0].list_flags;
    cRSubGoldy* player_owner = embedded_player();
    banners.slots[0].owner_player = player_owner;
    banners.slots[0].position.z = (float)first_block_row_count;
    banners.slots[0].list_flags = start_flags & ~BOD_FLAG_RENDER_ENABLED;
    banners.slots[0].color.a = 0.999f;

    banners.slots[1].add_bod_after(track_bod_list);

    *(int*)&banners.slots[1].position.z = zero;
    *(int*)&banners.slots[1].position.y = zero;
    *(int*)&banners.slots[1].position.x = zero;
    unsigned int completion_flags = banners.slots[1].list_flags;
    float completion_z = (float)completion_row_start;
    Banner* completion_banner = &banners.slots[1];
    completion_flags &= ~BOD_FLAG_RENDER_ENABLED;
    completion_banner->owner_player = player_owner;
    banners.slots[1].list_flags = completion_flags;
    banners.slots[1].position.z = completion_z;
    banners.slots[1].color.a = 0.999f;

    track_state_latch = (unsigned char)zero;
    replay_update_cursor = zero;
    times_up.state = TIMES_UP_STATE_INACTIVE;
    subgame_state = 2;

    int one = 1;
    g_game->render_skip_count = one;
    g_game->players[0].mouse_cursor.release_mouse_cursor();
    player.movement_mode_selector = one;
    player.steering_mode_selector = zero;
    player_owner->Init(one);

    g_game->active_bod_list.add_bod(
        &embedded_player()->presentation.jetpack_channel);

    g_game->active_bod_list.add_bod(
        &embedded_player()->presentation.weapon_channels[0]);

    g_game->active_bod_list.add_bod(
        &embedded_player()->presentation.weapon_channels[1]);

    g_game->active_bod_list.add_bod(
        &player_owner->presentation.weapon_channels[2]);

    BodNode* node =
        (BodNode*)&embedded_player()->presentation.invincible_shell;
    g_game->active_bod_list.add_bod(node);
    unsigned int visible_flags = node->list_flags;
    visible_flags |= 0x80;
    node->list_flags = visible_flags;

    g_game->active_bod_list.add_bod(
        (BodNode*)&player_owner->presentation);

    g_game->active_bod_list.add_bod((BodNode*)player_owner);

    slug_voice_manager.Init();

    BodNode* barrier_node = &barrier;
    BodNode* barrier_list = &barrier_sub_lazer_list_head;
    if ((barrier_node->list_flags & BOD_FLAG_LINKED) != zero) {
        report_errorf("List ADDafter");
    } else {
        barrier_node->list_prev = barrier_list;
        barrier_node->list_next = barrier_list->list_next;
        barrier_list->list_next = barrier_node;
        if (barrier_node->list_next != 0)
            barrier_node->list_next->list_prev = barrier_node;
        barrier_node->list_flags |= BOD_FLAG_LINKED;
    }
    barrier.owner_player = player_owner;

    if (level_mode == zero) {
        sprintf(lives_text_widget->text_buffer,
            "0/%i", level_definition.parcel_count);
        lives_icon_widget->unhide_border_init();
        lives_text_widget->unhide_border_init();
    }

    set_input_controller_pointer_authored_xy(0, 320.0f, 240.0f);
    set_input_controller_pointer_authored_xy(1, 320.0f, 240.0f);
    player.track_z_offset = 320.0f;
    player.track_z_anchor = 320.0f;
    scan_reset = 1;
    CalcRate();
}
