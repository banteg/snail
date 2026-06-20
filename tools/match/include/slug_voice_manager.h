// Standalone subgame slug voice gate at Game +0x35bb7c.
#ifndef SLUG_VOICE_MANAGER_H
#define SLUG_VOICE_MANAGER_H

class SlugVoiceManager {
public:
    void initialize_slug_voice_manager(); // @ 0x43f5c0
    void update_slug_voice_manager();     // @ 0x43f5e0

    unsigned char active; // +0x00
    char pad_01[3];
    float progress;       // +0x04
    float step;           // +0x08
};

typedef char SlugVoiceManager_must_be_0x0c[
    (sizeof(SlugVoiceManager) == 0x0c) ? 1 : -1];

#endif
