// reset_landscape_manager @ 0x4182e0 (thiscall, ret)

class LandscapeManager {
public:
    void reset_landscape_manager();

    char pad_000[0x5a0];
    int active_count; // +0x5a0
};

void LandscapeManager::reset_landscape_manager()
{
    active_count = 0;
}
