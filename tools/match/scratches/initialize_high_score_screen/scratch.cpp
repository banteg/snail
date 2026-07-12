// initialize_high_score_screen @ 0x416910 (thiscall, ret 0x8)

#include "backdrop.h"
#include "border_manager.h"
#include "game_root.h"
#include "high_score.h"
#include "landscape_manager.h"
#include "mouse_cursor_state.h"
#include "star_manager.h"
#include "subgame_runtime.h"

extern char* g_game_base; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // data_4dfb08
extern char g_back_text[]; // 0x4a20ec

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

int HighScore::initialize_high_score_screen(int mode_, int rank)
{
    // VC6 gives the short-lived color values distinct stack objects. Several
    // slots are reused after their title or row branch has ended.
    Color4f color_43;
    Color4f color_44;
    Color4f color_45;
    Color4f color_46;
    Color4f color_47;
    Color4f color_48;
    Color4f color_49;
    Color4f color_50;
    Color4f color_51;
    Color4f color_52;
    Color4f color_53;
    Color4f color_54;

    selected_bank = mode_;
    selected_rank = rank;
    if (rank == -1)
        entering_name = 0;
    else
        entering_name = 1;

    ((StarManager*)(g_game_base + 0x4f33c))->hide_star_field();
    ((SubgameRuntime*)(g_game_base + 0x74618))->hide_gameplay_scores();
    cache_music_file(g_main_menu_music_path, 0, g_blank_text);
    int script_index =
        ((LandscapeManager*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name(g_menu_background_script_path);
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            &((LandscapeManager*)(g_game_base + 0x106c218))
                ->scripts[script_index],
            0);
    ((BorderManager*)(g_game_base + 0xb4c))->set_border_justify_centre(0x41c80000);
    ((MouseCursorState*)(g_game_base + 0x290))->capture_mouse_cursor();

    title_widget = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    float y;
    int record_offset;
    float row_step;
    switch (selected_bank) {
    case 0:
        title_widget->initialize_frontend_widget(
            0, (char*)"Postal High Scores", 23, 0.0f, 64.0f,
            color_44.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_bank =
            ((GameRoot*)g_game_base)->subgame.sub_high_score.postal_records;
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_count = 10;
        row_step = 27.0f;
        break;
    case 1:
        title_widget->initialize_frontend_widget(
            0, (char*)"Challenge High Scores", 23, 0.0f, 64.0f,
            color_45.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_bank =
            ((GameRoot*)g_game_base)->subgame.sub_high_score.survival_records;
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_count = 10;
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
        int highlight = row_index == selected_rank ? 2 : 0;
        if (((SubSolution*)((char*)((GameRoot*)g_game_base)
                ->subgame.sub_high_score.active_record_bank
                + record_offset))->active == 1) {
            switch (selected_bank) {
            case 0: {
                y = (float)row_index * row_step + 111.0f;

                row_background_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                row_background_widgets[row_index]->initialize_frontend_widget(
                    highlight | 0x20000000,
                    (char*)"                                               ",
                    22, 0.0f, y,
                    color_49.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -228.0f);

                rank_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                int row_flags = highlight | 0x20400000;
                rank_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_53.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -222.0f);
                rank_row_widgets[row_index]->border_add_text_number(row_index + 1);
                rank_row_widgets[row_index]->layout_frontend_widget();

                name_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                name_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags,
                    ((SubSolution*)((char*)((GameRoot*)g_game_base)
                        ->subgame.sub_high_score.active_record_bank
                        + record_offset))->player_name,
                    22, 0.0f, y,
                    color_51.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -180.0f);
                if (row_index == selected_rank) {
                    name_row_widgets[row_index]->border_input_text_init(
                        16, g_runtime_config.last_entered_player_name, 16);
                    name_row_widgets[row_index]->widget_flags |= 0x2000;
                }
                name_row_widgets[row_index]->layout_frontend_widget();

                score_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                score_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_48.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    3, 160.0f);
                score_row_widgets[row_index]->border_add_text_number(
                    ((SubSolution*)((char*)((GameRoot*)g_game_base)
                        ->subgame.sub_high_score.active_record_bank
                        + record_offset))->score);
                score_row_widgets[row_index]->layout_frontend_widget();

                replay_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                replay_row_widgets[row_index]->initialize_frontend_widget(
                    highlight | 0x20000014, (char*)"Replay", 22, 0.0f, y,
                    color_50.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    2, 125.0f);
                replay_row_widgets[row_index]->hide_border_init();
                break;
            }

            case 1: {
                y = (float)row_index * row_step + 111.0f;

                row_background_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                row_background_widgets[row_index]->initialize_frontend_widget(
                    highlight | 0x20000000,
                    (char*)"                                           ",
                    22, 0.0f, y,
                    color_44.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -228.0f);

                rank_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                int row_flags = highlight | 0x20400000;
                rank_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_45.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -222.0f);
                rank_row_widgets[row_index]->border_add_text_number(row_index + 1);
                rank_row_widgets[row_index]->layout_frontend_widget();

                name_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                name_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags,
                    ((SubSolution*)((char*)((GameRoot*)g_game_base)
                        ->subgame.sub_high_score.active_record_bank
                        + record_offset))->player_name,
                    22, 0.0f, y,
                    color_52.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    1, -180.0f);
                if (row_index == selected_rank) {
                    name_row_widgets[row_index]->border_input_text_init(
                        16, g_runtime_config.last_entered_player_name, 16);
                    name_row_widgets[row_index]->widget_flags |= 0x2000;
                }
                name_row_widgets[row_index]->layout_frontend_widget();

                score_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                score_row_widgets[row_index]->initialize_frontend_widget(
                    row_flags, g_blank_text, 22, 0.0f, y,
                    color_47.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    3, 125.0f);
                score_row_widgets[row_index]->border_add_text_number(
                    ((SubSolution*)((char*)((GameRoot*)g_game_base)
                        ->subgame.sub_high_score.active_record_bank
                        + record_offset))->score);
                score_row_widgets[row_index]->layout_frontend_widget();

                replay_row_widgets[row_index] =
                    ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
                replay_row_widgets[row_index]->initialize_frontend_widget(
                    highlight | 0x20000014, (char*)"Replay", 22, 0.0f, y,
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
    } while (record_offset < SUB_SOLUTION_STRIDE * 10);

    y = row_step * 10.0f + 111.0f;
    if (entering_name != 0) {
        cancel_name_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        cancel_name_button->initialize_frontend_widget(
            0x20000014, (char*)"Cancel", 23, 0.0f, y,
            color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, -110.0f);
        cancel_name_button->set_frontend_widget_shortcut_key(11);

        submit_name_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        submit_name_button->initialize_frontend_widget(
            0x20000014, (char*)"Submit", 23, 0.0f, y,
            color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 55.0f);
        return submit_name_button->set_frontend_widget_shortcut_key(5);
    }

    back_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    back_button->initialize_frontend_widget(
        0x20000014, g_back_text, 23, 0.0f, y,
        color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, -132.0f);

    bank_toggle_button = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    switch (selected_bank) {
    case 0:
        return bank_toggle_button->initialize_frontend_widget(
            0x20000014, (char*)"Challenge Scores", 23, 0.0f, y,
            color_46.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 33.0f);
    case 1:
        return bank_toggle_button->initialize_frontend_widget(
            0x20000014, (char*)"Postal Scores", 23, 0.0f, y,
            color_43.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 33.0f);
    }

}
