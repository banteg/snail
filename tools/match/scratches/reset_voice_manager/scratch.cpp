// reset_voice_manager @ 0x448ec0 (thiscall, ret)

struct VoiceSet {
    char unknown_00[0x10];
    int active;                // +0x10
    char unknown_14[0x18 - 0x14];
};

class VoiceManager {
public:
    void reset_voice_manager();

    VoiceSet sets[16];         // +0x000
    int active_voice;          // +0x180
};

void VoiceManager::reset_voice_manager()
{
    active_voice = 0;
    VoiceSet* set = sets;
    int count = 16;
    do {
        set->active = 0;
        ++set;
        --count;
    } while (count != 0);
}
