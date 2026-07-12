// Authored cRClickStart, exact 0xac-byte click-to-start runtime owner.
#ifndef CLICK_START_H
#define CLICK_START_H

#include "border_manager.h"
#include "bod_types.h"
#include "frontend_widget.h"

class Player;

class ClickStart : public RenderableBod {
public:
    ClickStart* initialize_click_start_controller_runtime(); // @ 0x408670, constructor
    void initialize_click_start(Player* player); // @ 0x442170, cRClickStart::Init
    void update_click_start();                   // @ 0x442290, cRClickStart::AI

    char unknown_78[0x80 - 0x78];
    int state;                  // +0x80
    FrontendWidget* prompt;     // +0x84
    float teardown_progress;    // +0x88
    float teardown_progress_step; // +0x8c
    char unknown_90[0x98 - 0x90];
    Player* player;             // +0x98, borrowed containing cRSubGoldy
    char unknown_9c[0xa8 - 0x9c];
    unsigned char hide_prompt;  // +0xa8
};

typedef char ClickStart_must_be_0xac[(sizeof(ClickStart) == 0xac) ? 1 : -1];

#endif
