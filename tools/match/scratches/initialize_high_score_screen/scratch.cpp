// initialize_high_score_screen @ 0x416910 (thiscall, ret 0x8)

#include "backdrop.h"
#include "border_manager.h"
#include "game_root.h"
#include "high_score.h"
#include "landscape_manager.h"
#include "mouse_cursor_state.h"
#include "star_manager.h"
#include "subgame_runtime.h"

extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // data_4dfb08
extern char g_back_text[]; // 0x4a20ec

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

void HighScore::initialize_high_score_screen(int mode_, int rank)
{
    // VC6 gives the short-lived color values distinct stack objects. Several
    // slots are reused after their title or row branch has ended.
    tColour color_43;
    tColour color_44;
    tColour color_45;
    tColour color_46;
    tColour color_47;
    tColour color_48;
    tColour color_49;
    tColour color_50;
    tColour color_51;
    tColour color_52;
    tColour color_53;
    tColour color_54;

    selected_bank = mode_;
    selected_rank = rank;
    if (rank == -1)
        entering_name = 0;
    else
        entering_name = 1;

    g_game->star_manager.hide_star_field();
    g_game->subgame.hide_gameplay_scores();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index = g_game->subgame.landscape_manager
                           .load_landscape_script_by_name(g_menu_background_script_path);
    g_game->backdrop.change_backdrop(
        &g_game->subgame.landscape_manager.scripts[script_index], 0);
    g_game->border_manager.set_border_justify_centre(25.0f);
    g_game->players[0].mouse_cursor.capture_mouse_cursor();

    title_widget = g_game->border_manager.allocate_border();
    float y;
    int record_offset;
    float row_step;
    switch (selected_bank) {
    case 0:
        title_widget->initialize_frontend_widget(
            0, (char*)"Postal High Scores", 23, 0.0f, 64.0f,
            color_44.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        g_game->subgame.sub_high_score.active_record_bank =
            g_game->subgame.sub_high_score.postal_records;
        g_game->subgame.sub_high_score.active_record_count =
            SUB_HIGH_SCORE_TOP_TEN_COUNT;
        row_step = 27.0f;
        break;
    case 1:
        title_widget->initialize_frontend_widget(
            0, (char*)"Challenge High Scores", 23, 0.0f, 64.0f,
            color_45.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        g_game->subgame.sub_high_score.active_record_bank =
            g_game->subgame.sub_high_score.survival_records;
        g_game->subgame.sub_high_score.active_record_count =
            SUB_HIGH_SCORE_TOP_TEN_COUNT;
        row_step = 27.0f;
        break;
    }

    if (entering_name != 0) {
        rstrcpy_checked_ascii(title_widget->text_buffer, (char*)"Enter your name here!");
        title_widget->layout_frontend_widget();
    }

    int row_index = 0;
    record_offset = 0;
    do {
        replay_row_widgets[row_index] = 0;
        int highlight = row_index == selected_rank
            ? FRONTEND_WIDGET_FLAG_HIGHLIGHTED
            : 0;
        if (((SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                + record_offset))->active == 1) {
            switch (selected_bank) {
            case 0: {
                y = (float)row_index * row_step + 111.0f;

                row_background_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                row_background_widgets[row_index]->initialize_frontend_widget(
                    highlight | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN,
                    (char*)"                                               ",
                    22, 0.0f, y,
                    color_49.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -228.0f);

                rank_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                int row_flags = highlight | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                    | FRONTEND_WIDGET_FLAG_FRAMELESS;
                rank_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_53.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -222.0f);
                rank_row_widgets[row_index]->border_add_text_number(row_index + 1);
                rank_row_widgets[row_index]->layout_frontend_widget();

                name_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                name_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags,
                    ((SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                        + record_offset))->player_name,
                    22, 0.0f, y,
                    color_51.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -180.0f);
                if (row_index == selected_rank) {
                    name_row_widgets[row_index]->border_input_text_init(
                        16, g_runtime_config.last_entered_player_name, 16);
                    name_row_widgets[row_index]->widget_flags |=
                        FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE;
                }
                name_row_widgets[row_index]->layout_frontend_widget();

                score_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                score_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_48.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    3, 160.0f);
                score_row_widgets[row_index]->border_add_text_number(
                    ((SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                        + record_offset))->score);
                score_row_widgets[row_index]->layout_frontend_widget();

                replay_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                replay_row_widgets[row_index]->initialize_frontend_widget(
                    highlight | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                        | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                        | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
                    (char*)"Replay", 22, 0.0f, y,
                    color_50.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    2, 125.0f);
                replay_row_widgets[row_index]->hide_border_init();
                break;
            }

            case 1: {
                y = (float)row_index * row_step + 111.0f;

                row_background_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                row_background_widgets[row_index]->initialize_frontend_widget(
                    highlight | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN,
                    (char*)"                                           ",
                    22, 0.0f, y,
                    color_44.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -228.0f);

                rank_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                int row_flags = highlight | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                    | FRONTEND_WIDGET_FLAG_FRAMELESS;
                rank_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_45.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -222.0f);
                rank_row_widgets[row_index]->border_add_text_number(row_index + 1);
                rank_row_widgets[row_index]->layout_frontend_widget();

                name_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                name_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags,
                    ((SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                        + record_offset))->player_name,
                    22, 0.0f, y,
                    color_52.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -180.0f);
                if (row_index == selected_rank) {
                    name_row_widgets[row_index]->border_input_text_init(
                        16, g_runtime_config.last_entered_player_name, 16);
                    name_row_widgets[row_index]->widget_flags |=
                        FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE;
                }
                name_row_widgets[row_index]->layout_frontend_widget();

                score_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                score_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_47.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    3, 125.0f);
                score_row_widgets[row_index]->border_add_text_number(
                    ((SubSolution*)((char*)g_game->subgame.sub_high_score.active_record_bank
                        + record_offset))->score);
                score_row_widgets[row_index]->layout_frontend_widget();

                replay_row_widgets[row_index] =
                    g_game->border_manager.allocate_border();
                replay_row_widgets[row_index]->initialize_frontend_widget(
                    highlight | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                        | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                        | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
                    (char*)"Replay", 22, 0.0f, y,
                    color_54.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    2, 170.0f);
                if (entering_name != 0)
                    replay_row_widgets[row_index]->hide_border_init();
                break;
            }
            }

            if ((row_index & 1) != 0) {
                row_background_widgets[row_index]->idle_fill_color =
                    *color_46.set_color_rgba(
                        0.32941177f, 0.18431373f, 0.41960785f, 0.69999999f);
                replay_row_widgets[row_index]->idle_fill_color =
                    *color_43.set_color_rgba(
                        0.32941177f, 0.18431373f, 0.41960785f, 0.69999999f);
            }
        }
        ++row_index;
        record_offset += SUB_SOLUTION_STRIDE;
    } while (record_offset
        < SUB_SOLUTION_STRIDE * SUB_HIGH_SCORE_TOP_TEN_COUNT);

    y = row_step * (float)SUB_HIGH_SCORE_TOP_TEN_COUNT + 111.0f;
    if (entering_name != 0) {
        cancel_name_button = g_game->border_manager.allocate_border();
        cancel_name_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            (char*)"Cancel", 23, 0.0f, y,
            color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, -110.0f);
        cancel_name_button->set_frontend_widget_shortcut_key(11);

        submit_name_button = g_game->border_manager.allocate_border();
        submit_name_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            (char*)"Submit", 23, 0.0f, y,
            color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 55.0f);
        submit_name_button->set_frontend_widget_shortcut_key(5);
        return;
    }

    back_button = g_game->border_manager.allocate_border();
    back_button->initialize_frontend_widget(
        FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        g_back_text, 23, 0.0f, y,
        color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, -132.0f);

    bank_toggle_button = g_game->border_manager.allocate_border();
    switch (selected_bank) {
    case 0:
        bank_toggle_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            (char*)"Challenge Scores", 23, 0.0f, y,
            color_46.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 33.0f);
        return;
    case 1:
        bank_toggle_button->initialize_frontend_widget(
            FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN
                | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
            (char*)"Postal Scores", 23, 0.0f, y,
            color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 33.0f);
        return;
    }

}
