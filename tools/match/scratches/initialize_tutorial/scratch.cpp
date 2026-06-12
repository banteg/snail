// initialize_tutorial @ 0x448da0 (fastcall, ret)

extern char* g_game_base; // data_4df904

class Game {
public:
    char unknown_00[0x4c];
    int render_flags; // +0x4c
};

class TutorialController {
public:
    void initialize_tutorial();

    int state; // +0x00
    char unknown_04[0x08];
    Game* game; // +0x0c
};

void TutorialController::initialize_tutorial()
{
    state = 0;
    game = (Game*)(g_game_base + 0x74618);
    game->render_flags |= 0x600000;

    Game* owner = game;
    int flags = owner->render_flags;
    flags &= 0xfffffffd;
    owner->render_flags = flags;
}
