// Options menu controller, partial. The widget slots are cross-checked by
// initialize, update, destroy, and the root frontend dispatcher.
#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "frontend_widget.h"

class OptionsMenu {
public:
    void initialize_options_menu(); // @ 0x41ace0
    char* destroy_options_menu(); // @ 0x41aee0
    void update_options_menu(); // @ 0x41af60
    int apply_audio_config_volumes(); // @ 0x41b070

    int previous_frontend_state; // +0x00
    unsigned char active; // +0x04
    char unknown_05[0x10 - 0x05];
    FrontendWidget* back_widget; // +0x10
    FrontendWidget* fullscreen_widget; // +0x14
    FrontendWidget* sound_volume_widget; // +0x18
    FrontendWidget* music_volume_widget; // +0x1c
    float previous_sample_volume; // +0x20
};

#endif
