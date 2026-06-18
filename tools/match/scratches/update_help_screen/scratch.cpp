// update_help_screen @ 0x4168d0 (thiscall)

#include "frontend_widget.h"
#include "high_score_screen.h"

extern char* g_game_base; // data_4df904

int destroy_help_screen(); // @ 0x4168c0

class HelpScreen {
public:
    void update_help_screen();

    FrontendWidget* back_button; // +0x00
};

void HelpScreen::update_help_screen()
{
    FrontendWidget* button = back_button;
    unsigned int flags = button->widget_flags;
    if ((flags & 0x20) != 0) {
        button->widget_flags = flags & ~0x20;
        destroy_help_screen();
        ((HighScoreGameView*)g_game_base)->frontend_next_state = 2;
        ((HighScoreGameView*)g_game_base)->frontend_state_dirty = 1;
    }
}
