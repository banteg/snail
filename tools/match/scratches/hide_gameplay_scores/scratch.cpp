// hide_gameplay_scores @ 0x445f10 (thiscall, ret)

struct FrontendWidget {
    void hide_border_init();
};

class Game {
public:
    void hide_gameplay_scores();

    char unknown_00[0x35bb88];
    FrontendWidget* score_widget_a; // +0x35bb88
    FrontendWidget* score_widget_b; // +0x35bb8c
};

void Game::hide_gameplay_scores()
{
    FrontendWidget* widget_b = score_widget_b;
    if (widget_b != 0) {
        widget_b->hide_border_init();
    }

    FrontendWidget* widget_a = score_widget_a;
    if (widget_a != 0) {
        widget_a->hide_border_init();
    }
}
