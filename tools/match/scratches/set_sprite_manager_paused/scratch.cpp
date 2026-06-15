// set_sprite_manager_paused @ 0x44e540 (thiscall, ret byte)

class SpriteManagerPause {
public:
    char set_sprite_manager_paused(char paused);

    char paused; // +0x00
};

char SpriteManagerPause::set_sprite_manager_paused(char paused_)
{
    paused = paused_;
    return paused_;
}
