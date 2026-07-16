// update_thanks_for_playing_screen @ 0x4340f0 (thiscall)

#include "audio_system.h"
#include "game_root.h"
#include "thanks_screen.h"

extern char g_click_to_continue_text[]; // 0x4a11c4

char read_pressed_text_input_key_code(); // @ 0x432440
void __cdecl rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0

void ThanksScreen::update_thanks_for_playing_screen()
{
    int flags = g_game->players[0].game_input->input.pressed_buttons;
    if (((flags & INPUT_BUTTON_PRIMARY) != 0
            || read_pressed_text_input_key_code() == 0xb)
        && message_state >= 2
        && g_game->fade.state == 0) {
        g_sound_effect_manager.play_sound_effect(8);
        g_game->fade.begin_frontend_fade_out(0);
    }

    if (g_game->fade.state == 4) {
        uninit_thanks_screen();
    }

    message_progress = message_progress + message_progress_step;
    if (message_progress <= 1.0f) {
        return;
    }

    int current_state = message_state;
    message_progress = 0.0f;
    switch (current_state) {
    case 0:
        message_state = 1;
        message_progress_step = 0.0333333351f;
        message_widget->hide_border_init();
        return;

    case 1:
        message_state = 2;
        message_progress_step = 0.00416666688f;
        rstrcpy_checked_ascii(
            message_widget->text_buffer, "Test your reflexes in Challenge Mode!");
        message_widget->unhide_border_init();
        return;

    case 2:
        message_state = 3;
        message_progress_step = 0.0333333351f;
        message_widget->hide_border_init();
        return;

    case 3:
        message_state = 4;
        message_progress_step = 0.00416666688f;
        rstrcpy_checked_ascii(
            message_widget->text_buffer, "Improve your skills in Time Trial!");
        message_widget->unhide_border_init();
        return;

    case 4:
        message_state = 5;
        message_progress_step = 0.0333333351f;
        message_widget->hide_border_init();
        return;

    case 5:
        message_state = 6;
        message_progress_step = 0.00416666688f;
        rstrcpy_checked_ascii(message_widget->text_buffer, g_click_to_continue_text);
        message_widget->unhide_border_init();
        return;

    case 6:
        message_state = 7;
        // Fall through.
    case 7:
        message_progress_step = 0.0f;
        return;
    }
}
