// Authored cRClickStart, exact 0xac-byte click-to-start runtime owner.
#ifndef CLICK_START_H
#define CLICK_START_H

#include "border_manager.h"
#include "bod_types.h"
#include "frontend_widget.h"

class Player;

enum ClickStartState {
    CLICK_START_STATE_INACTIVE = 0,
    CLICK_START_STATE_UNKNOWN_1 = 1,
    CLICK_START_STATE_WAITING_FOR_START = 2,
    CLICK_START_STATE_START_PENDING = 3,
    CLICK_START_STATE_TEARDOWN = 4,
};

class ClickStart : public RenderableBod {
public:
    ClickStart* initialize_click_start_controller_runtime(); // @ 0x408670, constructor
    void initialize_click_start(Player* player); // @ 0x442170, cRClickStart::Init
    void update_click_start();                   // @ 0x442290, cRClickStart::AI

    char unknown_78[0x80 - 0x78];
    ClickStartState state;      // +0x80
    FrontendWidget* prompt;     // +0x84
    float teardown_progress;    // +0x88
    float teardown_progress_step; // +0x8c
    char unknown_90[0x98 - 0x90];
    Player* owner_player;       // +0x98, borrowed owning cRSubGoldy
    char unknown_9c[0xa8 - 0x9c];
    unsigned char hide_prompt;  // +0xa8
};

typedef char ClickStart_must_be_0xac[(sizeof(ClickStart) == 0xac) ? 1 : -1];

#endif
