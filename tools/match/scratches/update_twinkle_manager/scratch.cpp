// update_twinkle_manager @ 0x404030 (thiscall, ret)

#include "twinkle_manager.h"

void TwinkleManager::update_twinkle_manager()
{
    int result = active_state;
    --result;
    if (result == 0) {
        int index = 0;
        if (twinkle_count > 0) {
            Twinkle* twinkle = twinkles;
            do {
                twinkle->update_twinkle();
                ++index;
                ++twinkle;
            } while (index < twinkle_count);
        }
    }
}
