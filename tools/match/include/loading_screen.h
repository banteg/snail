#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

struct LoadingScreen {
    int initialize_loading_screen(); // @ 0x418b50
    int destroy_loading_screen();    // @ 0x418e50
    int update_loading_screen();     // @ 0x418e80

    int active;              // +0x00
    int previous_percent;    // +0x04
    int last_loading_budget; // +0x08
};

typedef char LoadingScreen_must_be_0x0c[
    (sizeof(LoadingScreen) == 0x0c) ? 1 : -1];

extern LoadingScreen g_loading_screen; // data_503290

#endif
