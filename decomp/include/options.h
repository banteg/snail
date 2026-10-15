// Authored cROptions front-end owner embedded in GameRoot.
#ifndef OPTIONS_H
#define OPTIONS_H

#include "frontend_widget.h"

class cROptions {
public:
    void Init();   // @ 0x41ace0
    void UnInit(); // @ 0x41aee0
    void AI();     // @ 0x41af60
    void apply_audio_config_volumes(); // @ 0x41b070, cROptions::Apply-compatible

    int previous_frontend_state; // +0x00
    unsigned char active; // +0x04
    char unknown_05[0x10 - 0x05];
    cRBorder* back_widget; // +0x10
    cRBorder* fullscreen_widget; // +0x14
    cRBorder* sound_volume_widget; // +0x18
    cRBorder* music_volume_widget; // +0x1c
    float previous_sample_volume; // +0x20
};

typedef cROptions Options;
typedef char Options_must_be_0x24[
    (sizeof(cROptions) == 0x24) ? 1 : -1];

#endif
