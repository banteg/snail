// update_twinkle_manager @ 0x404030 (thiscall, ret)

#include "twinkle_manager.h"

void cRTwinkleManager::AI()
{
    int result = active_state;
    --result;
    if (result == 0) {
        int index = 0;
        if (twinkle_count > 0) {
            cRTwinkle* twinkle = twinkles;
            do {
                twinkle->AI();
                ++index;
                ++twinkle;
            } while (index < twinkle_count);
        }
    }
}
