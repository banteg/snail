// destroy_main_menu @ 0x419b30 (cdecl)

extern char* g_game_base; // data_4df904

class BorderManager {
public:
    void kill_all_borders();
};

class SpriteManager {
public:
    void kill_game_sprites();
};

extern SpriteManager g_sprite_manager; // data_790f30

void destroy_main_menu()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
    g_sprite_manager.kill_game_sprites();
}
