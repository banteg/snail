// initialize_game_last @ 0x410720 (thiscall, ret)

class Backdrop {
public:
    void* initialize_backdrop(int last_mode);
};

class GameRoot {
public:
    void* initialize_game_last();
};

void* GameRoot::initialize_game_last()
{
    return ((Backdrop*)((char*)this + 0x4ec10))->initialize_backdrop(1);
}
