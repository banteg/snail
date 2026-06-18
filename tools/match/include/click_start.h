// Click-to-start runtime owner, partial.
#ifndef CLICK_START_H
#define CLICK_START_H

#include "bod_types.h"
#include "frontend_widget.h"

class BorderManager {
public:
    FrontendWidget* allocate_border(); // @ 0x4032a0
    void kill_border(FrontendWidget* border);
};

class ClickStartPlayer {
public:
    char unknown_000[0x304];
    int startup_track_index; // +0x304, click-start view; update_subgoldy uses the same slot as a replay/ghost anchor
};

class ClickStartController : public RenderableBod {
public:
    ClickStartController* initialize_click_start_controller_runtime(); // @ 0x408670
    void initialize_click_start(ClickStartPlayer* player); // @ 0x442170
    void update_click_start();                             // @ 0x442290

    char unknown_78[0x80 - 0x78];
    int state;                  // +0x80
    FrontendWidget* prompt;     // +0x84
    float teardown_progress;    // +0x88
    float teardown_progress_step; // +0x8c
    char unknown_90[0x98 - 0x90];
    ClickStartPlayer* player;   // +0x98
    char unknown_9c[0xa8 - 0x9c];
    unsigned char hide_prompt;  // +0xa8
};

#endif
