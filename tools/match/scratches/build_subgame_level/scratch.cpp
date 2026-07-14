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
#include "runtime_config.h"
#include "salt_hazard_types.h"
#include "slug_voice_manager.h"
#include "star_manager.h"
#include "subgame_runtime.h"
#include "sub_lazer_types.h"
#include "track_parcel_runtime.h"
#include "voice_manager.h"

extern GameRoot* g_game;
extern VoiceManager g_voice_manager;
extern char g_blank_text[];

int next_math_random_value();
float random_float_below(float upper_bound, const char* tag);
char cache_music_file(char* path, int unused, char* unused_default_path);
int report_errorf(char* format, ...);
int sprintf(char* buffer, char* format, ...);
void set_input_controller_pointer_authored_xy(int controller, float x, float y);

void SubgameRuntime::build_subgame_level(int level_index)
{
    char* game = (char*)this;

    g_game->star_manager.unhide_star_field();
    if (level_mode == 7)
        hide_gameplay_scores();
    else
        unhide_gameplay_scores();

    int zero = 0;
    switch ((unsigned int)(next_math_random_value() * 0.000122070312f)) {
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
    player.damage_gauge.initialize_damage_gauge();
    player.progress_bar.noop_runtime_ai();
    sub_lazers.initialize_sub_lazer_pool();
    salt_hazards.initialize_salt_hazard_pool();
    g_voice_manager.reset_voice_manager();

    level_definition.load_frontend_level_by_mode_and_index(level_mode, level_index);

    if (selected_level_record_active != zero
        || selected_level_record_persistent != zero) {
        base_rate = selected_level_record->replay_speed_scalar;
        level_mode = selected_level_record->replay_mode_id;
        completion_bonus_y_source = selected_level_record->challenge_difficulty_value;
        completion_bonus_x_source = selected_level_record->challenge_speed_value;
        challenge_difficulty_scalar =
            (float)selected_level_record->challenge_difficulty_value * 0.00999999978f;
    } else {
        int mode = level_mode;
        if (mode == 3) {
            base_rate = g_runtime_config.default_challenge_speed_slider;
        } else if (mode == 0 || mode == 4 || mode == 7) {
            if (level_definition.selected_speed_bits == (int)0xbf800000) {
                base_rate = calc_slider_to_rate(0.0f);
            } else {
                float normalized_speed =
                    level_definition.selected_speed * 0.00999999978f;
                base_rate = normalized_speed * 0.900000036f + 0.200000003f;
            }
        } else if (mode == 1) {
            base_rate = calc_slider_to_rate(
                (float)g_runtime_config.completion_bonus_x_source * 0.00999999978f);
            challenge_difficulty_scalar =
                (float)g_runtime_config.completion_bonus_y_source * 0.00999999978f;
        } else if (mode == 2) {
            base_rate = calc_slider_to_rate(
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
                (float)g_runtime_config.completion_bonus_y_source * 0.00999999978f;
            garbage_frequency =
                normalized_garbage_difficulty * 0.800000012f;
            float normalized_salt_difficulty =
                (float)g_runtime_config.completion_bonus_y_source * 0.00999999978f;
            salt_frequency =
                normalized_salt_difficulty * 0.800000012f;
        }
    }

    parcel_manager.initialize_track_parcel_slots();
    if (*(unsigned char*)((char*)g_game + 0x4f2e0) == 1) {
        top_score_widget->hide_border_init();
        bottom_score_widget->hide_border_init();
    }

    rebuild_track_runtime_from_segments(level_index);

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
    {
        BodNode* start_row = (BodNode*)(game + 0x359080);
        if ((start_row->list_flags & 0x200) != zero) {
            report_errorf("List ADDafter");
        } else {
            start_row->list_prev = track_bod_list;
            start_row->list_next = track_bod_list->list_next;
            track_bod_list->list_next = start_row;
            if (start_row->list_next != 0)
                start_row->list_next->list_prev = start_row;
            start_row->list_flags |= 0x200;
        }
    }

    *(int*)(game + 0x359098) = zero;
    *(int*)(game + 0x359094) = zero;
    *(int*)(game + 0x359090) = zero;
    unsigned int start_flags = *(unsigned int*)(game + 0x359084);
    *(Player**)(game + 0x3590d4) = embedded_player();
    *(float*)(game + 0x359098) = (float)*(int*)(game + 0x50);
    int row_alpha = 0x3f7fbe77;
    *(unsigned int*)(game + 0x359084) = start_flags & ~0x20;
    *(int*)(game + 0x3590b4) = row_alpha;

    {
        BodNode* completion_row = (BodNode*)(game + 0x3590e0);
        if ((completion_row->list_flags & 0x200) != zero) {
            report_errorf("List ADDafter");
        } else {
            completion_row->list_prev = track_bod_list;
            completion_row->list_next = track_bod_list->list_next;
            track_bod_list->list_next = completion_row;
            if (completion_row->list_next != 0)
                completion_row->list_next->list_prev = completion_row;
            completion_row->list_flags |= 0x200;
        }
    }

    *(int*)(game + 0x3590f8) = zero;
    *(int*)(game + 0x3590f4) = zero;
    *(int*)(game + 0x3590f0) = zero;
    unsigned int completion_flags = *(unsigned int*)(game + 0x3590e4);
    *(Player**)(game + 0x359134) = embedded_player();
    *(float*)(game + 0x3590f8) = (float)*(int*)(game + 0x58);
    ((unsigned char*)&completion_flags)[0] &= 0xdf;
    *(unsigned int*)(game + 0x3590e4) = completion_flags;
    *(int*)(game + 0x359114) = row_alpha;

    track_state_latch = (unsigned char)zero;
    replay_update_cursor = zero;
    times_up.state = zero;
    subgame_state = 2;

    int one = 1;
    g_game->render_skip_count = one;
    g_game->players[0].mouse_cursor.release_mouse_cursor();
    player.movement_mode_selector = one;
    player.steering_mode_selector = zero;
    player.initialize_subgoldy(one);

    BodNode* node =
        (BodNode*)&embedded_player()->presentation.jetpack_channel;
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)&embedded_player()->presentation.weapon_channels[0];
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)&embedded_player()->presentation.weapon_channels[1];
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)&embedded_player()->presentation.weapon_channels[2];
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)&embedded_player()->presentation.invincible_shell;
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }
    unsigned int visible_flags = node->list_flags;
    ((unsigned char*)&visible_flags)[0] |= 0x80;
    node->list_flags = visible_flags;

    node = (BodNode*)&embedded_player()->presentation;
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    BodNode* player_node = (BodNode*)embedded_player();
    if ((player_node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = player_node;
            player_node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = player_node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        player_node->list_flags |= 0x200;
    }

    slug_voice_manager.initialize_slug_voice_manager();

    BodNode* barrier_node = &barrier;
    BodNode* barrier_list = &barrier_sub_lazer_list_head;
    if ((barrier_node->list_flags & 0x200) != zero) {
        report_errorf("List ADDafter");
    } else {
        barrier_node->list_prev = barrier_list;
        barrier_node->list_next = barrier_list->list_next;
        barrier_list->list_next = barrier_node;
        if (barrier_node->list_next != 0)
            barrier_node->list_next->list_prev = barrier_node;
        barrier_node->list_flags |= 0x200;
    }
    barrier.owner_player = embedded_player();

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
    calc_subgame_rate();
}
