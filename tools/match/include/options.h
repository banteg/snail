// Authored cROptions front-end owner embedded in GameRoot.
#ifndef OPTIONS_H
#define OPTIONS_H

#include "frontend_widget.h"

class Options {
public:
    void initialize_options_menu(); // @ 0x41ace0, cROptions::Init
    char* destroy_options_menu(); // @ 0x41aee0, cROptions::UnInit
    void update_options_menu(); // @ 0x41af60, cROptions::AI
    void apply_audio_config_volumes(); // @ 0x41b070, cROptions::Apply-compatible

    int previous_frontend_state; // +0x00
    unsigned char active; // +0x04
    char unknown_05[0x10 - 0x05];
    FrontendWidget* back_widget; // +0x10
    FrontendWidget* fullscreen_widget; // +0x14
    FrontendWidget* sound_volume_widget; // +0x18
    FrontendWidget* music_volume_widget; // +0x1c
    float previous_sample_volume; // +0x20
};

typedef char Options_must_be_0x24[
    (sizeof(Options) == 0x24) ? 1 : -1];

#endif
