// destroy_help_screen @ 0x4168c0 (cdecl)

extern char* g_game_base; // data_4df904

class BorderManager {
public:
    int kill_all_borders();
};

int destroy_help_screen()
{
    return ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
}
