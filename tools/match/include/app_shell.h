// Narrow root application shell view for SubGoldy frontend handoff paths.
#ifndef APP_SHELL_H
#define APP_SHELL_H

#include "frontend_fade.h"

struct AppShellHudRow {
    int values[16];
};

class AppShell {
public:
    char unknown_000[0x24];
    FrontendFade fade; // +0x24
    char unknown_038[0x15c - 0x38];
    AppShellHudRow hud_source; // +0x15c
    char unknown_19c[0x1b8 - 0x19c];
    int frontend_state; // +0x1b8
    int frontend_substate; // +0x1bc
    char unknown_1c0[0x2cc - 0x1c0];
    AppShellHudRow hud_target; // +0x2cc
    unsigned char skip_flag; // +0x30c
    unsigned char high_score_entry_pending; // +0x30d
};

extern AppShell* g_app; // data_4df904

#endif
