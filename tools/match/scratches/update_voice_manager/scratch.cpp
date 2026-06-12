// update_voice_manager @ 0x4492a0 (thiscall, ret)

class VoiceSet {
public:
    int update_voice_set();

    char unknown_00[0x18];
};

class VoiceManager {
public:
    void update_voice_manager();

    VoiceSet sets[16];         // +0x000
    float global_progress;      // +0x180
};

void VoiceManager::update_voice_manager()
{
    VoiceSet* set = sets;
    int count = 16;
    do {
        set->update_voice_set();
        ++set;
        --count;
    } while (count != 0);
    global_progress = global_progress + 0.016666668f;
}
