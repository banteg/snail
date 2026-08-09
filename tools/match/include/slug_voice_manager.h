// Authored cRSlugVoiceManager embedded at cRSubGame +0x35bb7c.
#ifndef SLUG_VOICE_MANAGER_H
#define SLUG_VOICE_MANAGER_H

class cRSlugVoiceManager {
public:
    void Init(); // @ 0x43f5c0
    void AI(); // @ 0x43f5e0

    unsigned char active; // +0x00
    char pad_01[3];
    float progress;       // +0x04
    float step;           // +0x08
};

typedef cRSlugVoiceManager SlugVoiceManager;

typedef char cRSlugVoiceManager_must_be_0x0c[
    (sizeof(cRSlugVoiceManager) == 0x0c) ? 1 : -1];
typedef char SlugVoiceManager_must_be_0x0c[
    (sizeof(SlugVoiceManager) == 0x0c) ? 1 : -1];

#endif
