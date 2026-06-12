// initialize_fringe_manager @ 0x447090 (thiscall, ret)

class FringeManager {
public:
    void initialize_fringe_manager();

    char objects[0x5fb40]; // +0x00000, 7000 * 0x38
    int count;             // +0x5fb40
};

void FringeManager::initialize_fringe_manager()
{
    count = 0;
}
