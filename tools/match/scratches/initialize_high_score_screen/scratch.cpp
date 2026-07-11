// initialize_high_score_screen @ 0x416910 (thiscall, ret 0x8)

#include "backdrop.h"
#include "border_manager.h"
#include "border_runtime.h"
#include "game_root.h"
#include "high_score_screen.h"
#include "landscape_manager.h"
#include "mouse_cursor_state.h"
#include "star_field.h"
#include "subgame_runtime.h"

extern char* g_game_base; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // data_4dfb08

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50

class HighScoreBorderManager {
public:
    FrontendWidget* allocate_border();
};

static void init_score_text_widget(
    FrontendWidget** slot,
    int flags,
    char* text,
    int widget_type,
    float y,
    Color4f* color,
    int align,
    float anchor)
{
    *slot = ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    (*slot)->initialize_frontend_widget(flags, text, widget_type, 0.0f, y, color, align, anchor);
}

int HighScoreScreen::initialize_high_score_screen(int mode_, int rank)
{
    selected_bank = mode_;
    selected_rank = rank;
    entering_name = (rank != -1);

    ((StarField*)(g_game_base + 0x4f33c))->hide_star_field();
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
    ((BorderRuntime*)(g_game_base + 0xb4c))->set_border_justify_centre(0x41c80000);
    ((MouseCursorState*)(g_game_base + 0x290))->capture_mouse_cursor();

    Color4f color;
    Color4f alt_row_color;
    back_button = ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    if (selected_bank == 0) {
        back_button->initialize_frontend_widget(
            0, (char*)"Postal High Scores", 23, 0.0f, 64.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_bank =
            ((GameRoot*)g_game_base)->subgame.sub_high_score.postal_records;
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_count = 10;
    } else if (selected_bank == 1) {
        back_button->initialize_frontend_widget(
            0, (char*)"Challenge High Scores", 23, 0.0f, 64.0f,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 0.0f);
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_bank =
            ((GameRoot*)g_game_base)->subgame.sub_high_score.survival_records;
        ((GameRoot*)g_game_base)->subgame.sub_high_score.active_record_count = 10;
    }

    float row_step = 27.0f;
    if (entering_name != 0) {
        rstrcpy_checked_ascii(back_button->text_buffer, (char*)"Enter your name here!");
        back_button->layout_frontend_widget();
    }

    int record_offset = 0;
    for (int i = 0; i < 10; ++i) {
        replay_row_widgets[i] = 0;
        int highlight = (i == selected_rank) ? 2 : 0;
        SubSolution* record =
            (SubSolution*)((char*)((GameRoot*)g_game_base)
                    ->subgame.sub_high_score.active_record_bank
                + record_offset);
        if (record->active == 1) {
            float y = (float)i * row_step + 111.0f;
            char* row_fill = selected_bank == 0
                ? (char*)"                                               "
                : (char*)"                                           ";
            float score_anchor = selected_bank == 0 ? 160.0f : 125.0f;
            float replay_anchor = selected_bank == 0 ? 125.0f : 170.0f;

            init_score_text_widget(
                &name_row_widgets[i - 20],
                highlight | 0x20000000,
                row_fill,
                22,
                y,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                1,
                -228.0f);

            init_score_text_widget(
                &name_row_widgets[i - 10],
                highlight | 0x20400000,
                g_blank_text,
                22,
                y,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                1,
                -222.0f);
            name_row_widgets[i - 10]->border_add_text_number(i + 1);
            name_row_widgets[i - 10]->layout_frontend_widget();

            init_score_text_widget(
                &name_row_widgets[i],
                highlight | 0x20400000,
                record->player_name,
                22,
                y,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                1,
                -180.0f);
            if (i == selected_rank) {
                name_row_widgets[i]->border_input_text_init(
                    16, g_runtime_config.last_entered_player_name, 16);
                name_row_widgets[i]->widget_flags |= 0x2000;
            }
            name_row_widgets[i]->layout_frontend_widget();

            init_score_text_widget(
                &name_row_widgets[i + 10],
                highlight | 0x20400000,
                g_blank_text,
                22,
                y,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                3,
                score_anchor);
            name_row_widgets[i + 10]->border_add_text_number(record->score);
            name_row_widgets[i + 10]->layout_frontend_widget();

            replay_row_widgets[i] =
                ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
            replay_row_widgets[i]->initialize_frontend_widget(
                highlight | 0x20000014,
                (char*)"Replay",
                22,
                0.0f,
                y,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                replay_anchor);
            if (entering_name == 0)
                replay_row_widgets[i]->hide_border_init();

            if ((i & 1) != 0) {
                *(Color4f*)((char*)name_row_widgets[i - 20] + 0x1bc) =
                    *alt_row_color.set_color_rgba(0.32941177f, 0.18431373f, 0.41960785f, 0.69999999f);
                *(Color4f*)((char*)replay_row_widgets[i] + 0x1bc) =
                    *alt_row_color.set_color_rgba(0.32941177f, 0.18431373f, 0.41960785f, 0.69999999f);
            }
        }
        record_offset += SUB_SOLUTION_STRIDE;
    }

    float footer_y = row_step * 10.0f + 111.0f;
    if (entering_name != 0) {
        cancel_name_button = ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        cancel_name_button->initialize_frontend_widget(
            0x20000014, (char*)"Cancel", 23, 0.0f, footer_y,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, -110.0f);
        cancel_name_button->set_frontend_widget_shortcut_key(11);

        submit_name_button = ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        submit_name_button->initialize_frontend_widget(
            0x20000014, (char*)"Submit", 23, 0.0f, footer_y,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 55.0f);
        return submit_name_button->set_frontend_widget_shortcut_key(5);
    }

    back_button = ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    back_button->initialize_frontend_widget(
        0x20000014, (char*)"Back", 23, 0.0f, footer_y,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, -132.0f);

    bank_toggle_button = ((HighScoreBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    if (selected_bank == 0) {
        bank_toggle_button->initialize_frontend_widget(
            0x20000014, (char*)"Challenge Scores", 23, 0.0f, footer_y,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 33.0f);
    } else if (selected_bank == 1) {
        bank_toggle_button->initialize_frontend_widget(
            0x20000014, (char*)"Postal Scores", 23, 0.0f, footer_y,
            color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f), 2, 33.0f);
    }

    return selected_bank;
}
