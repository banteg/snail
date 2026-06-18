// update_new_game_menu @ 0x417eb0 (thiscall, ret)

#include "new_game_menu.h"

void NewGameMenu::update_new_game_menu()
{
    HighScoreGameView* game;
    unsigned int flags;

    if (read_pressed_text_input_key_code() != 0
        || ((*(GameInputOwner**)(g_game_base + 0x28c))->input.pressed_buttons & 0x4000) != 0) {
        replay_probe_progress = 0.0f;
        if (hide_for_replay_latch == 1) {
            postal_button->unhide_border_init();
            tutorial_button->unhide_border_init();
            time_trial_button->unhide_border_init();
            challenge_button->unhide_border_init();
            help_button->unhide_border_init();
            back_button->unhide_border_init();
            ((MouseCursorState*)(g_game_base + 0x290))->capture_mouse_cursor();
            hide_for_replay_latch = 0;
        }
    }

    flags = postal_button->widget_flags;
    if ((flags & 0x20) != 0) {
        postal_button->widget_flags = flags & ~0x20;
        destroy_main_menu();
        game = (HighScoreGameView*)g_game_base;
        game->frontend_next_state = 10;
        game->frontend_state_dirty = 1;
        game->selected_subgame_mode = 0;
        *(int*)(g_game_base + 0x12e55e0) = 2;
        return;
    }

    flags = time_trial_button->widget_flags;
    if ((flags & 0x20) != 0) {
        time_trial_button->widget_flags = flags & ~0x20;
        destroy_main_menu();
        game = (HighScoreGameView*)g_game_base;
        game->frontend_next_state = 10;
        game->frontend_state_dirty = 1;
        game->selected_subgame_mode = 4;
        return;
    }

    flags = tutorial_button->widget_flags;
    if ((flags & 0x20) != 0) {
        tutorial_button->widget_flags = flags & ~0x20;
        destroy_main_menu();
        game = (HighScoreGameView*)g_game_base;
        game->frontend_next_state = 10;
        game->frontend_state_dirty = 1;
        game->selected_subgame_mode = 7;
        ((TutorialController*)(g_game_base + 0x7ee70))->initialize_tutorial();
        g_new_game_tutorial_started = 1;
        return;
    }

    flags = challenge_button->widget_flags;
    if ((flags & 0x20) != 0) {
        challenge_button->widget_flags = flags & ~0x20;
        destroy_main_menu();
        game = (HighScoreGameView*)g_game_base;
        game->frontend_next_state = 10;
        game->frontend_state_dirty = 1;
        game->selected_subgame_mode = 1;
        return;
    }

    flags = back_button->widget_flags;
    if ((flags & 0x20) != 0) {
        back_button->widget_flags = flags & ~0x20;
        destroy_main_menu();
        game = (HighScoreGameView*)g_game_base;
        game->frontend_next_state = 4;
        game->frontend_state_dirty = 1;
    } else {
        flags = help_button->widget_flags;
        if ((flags & 0x20) != 0) {
            help_button->widget_flags = flags & ~0x20;
            destroy_main_menu();
            game = (HighScoreGameView*)g_game_base;
            game->frontend_next_state = 31;
            game->frontend_state_dirty = 1;
        }
    }

    float progress = replay_probe_step + replay_probe_progress;
    replay_probe_progress = progress;
    if (progress <= 1.0f)
        return;

    replay_probe_progress = 0.0f;

    int attempts = 0;
    ((HighScoreGameView*)g_game_base)->replay_launch_record = 0;
    do {
        ++attempts;
        int cursor = replay_attract_bank_cursor;
        if (cursor == 0) {
            int index = (int)((float)next_math_random_value() * 0.000122070312f);
            HighScoreRecord* record =
                (HighScoreRecord*)(g_game_base + 0x6ffae8 + index * HIGH_SCORE_RECORD_STRIDE);
            if (record->active == 1) {
                ((HighScoreGameView*)g_game_base)->replay_launch_record = record;
                ((HighScoreGameView*)g_game_base)->selected_subgame_mode = 0;
            }
        } else if (cursor == 1) {
            int index = (int)((float)next_math_random_value() * 0.000122070312f);
            HighScoreRecord* record =
                (HighScoreRecord*)(g_game_base + 0x85c128 + index * HIGH_SCORE_RECORD_STRIDE);
            if (record->active == 1) {
                ((HighScoreGameView*)g_game_base)->replay_launch_record = record;
                ((HighScoreGameView*)g_game_base)->selected_subgame_mode = 1;
            }
        } else if (cursor == 3) {
            int index = (int)((float)next_math_random_value() * 0.00155639648f);
            HighScoreRecord* record =
                (HighScoreRecord*)(g_game_base + 0x9b8768 + index * HIGH_SCORE_RECORD_STRIDE);
            if (record->active == 1) {
                ((HighScoreGameView*)g_game_base)->replay_launch_record = record;
                ((HighScoreGameView*)g_game_base)->selected_subgame_mode = 4;
            }
        }

        int next_cursor = replay_attract_bank_cursor + 1;
        replay_attract_bank_cursor = next_cursor;
        if (next_cursor == 5)
            replay_attract_bank_cursor = 0;

        if (((HighScoreGameView*)g_game_base)->replay_launch_record != 0)
            break;
        if (attempts >= 1000) {
            attract_reset_progress = 0.0f;
            attract_reset_step = 0.000277777784f;
            return;
        }
    } while (1);

    if (attempts >= 1000) {
        attract_reset_progress = 0.0f;
        attract_reset_step = 0.000277777784f;
        return;
    }

    hide_for_replay_latch = 1;
    game = (HighScoreGameView*)g_game_base;
    game->frontend_next_state = 10;
    game->frontend_state_dirty = 1;
    game->replay_launch_active = 1;
    game->replay_launch_return_state = 2;
    game->replay_launch_from_frontend = 1;
    attract_reset_progress = 0.0f;
    attract_reset_step = 0.000277777784f;
    destroy_main_menu();
}
