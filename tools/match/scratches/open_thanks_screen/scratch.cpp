// open_thanks_screen @ 0x433fc0 (thiscall, ret)

extern char* g_game_base; // data_4df904

class ThanksScreenOwner {
public:
    char* open_thanks_screen();

    char* thanks_screen; // +0x00
};

char* ThanksScreenOwner::open_thanks_screen()
{
    char* result = g_game_base + 0x74618;
    thanks_screen = result;
    return result;
}
