#ifndef TWINKLE_MANAGER_H
#define TWINKLE_MANAGER_H

#include "twinkle.h"

class cRTwinkleManager {
public:
    void update_twinkle_manager(); // @ 0x404030, Android cRTwinkleManager::AI()

    cRTwinkle twinkles[5]; // +0x00, five stride-0x30 records
    int active_state;    // +0xf0
    int twinkle_count;   // +0xf4
};

typedef cRTwinkleManager TwinkleManager;
typedef char TwinkleManager_must_be_0xf8[
    (sizeof(cRTwinkleManager) == 0xf8) ? 1 : -1];

#endif
