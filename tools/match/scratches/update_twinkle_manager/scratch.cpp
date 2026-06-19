// update_twinkle_manager @ 0x404030 (thiscall, ret)

#include "twinkle_manager.h"

class Twinkle {
public:
    int update_twinkle();
};

int TwinkleManager::update_twinkle_manager()
{
    int result = active_state;
    --result;
    if (result == 0) {
        result = twinkle_count;
        int index = 0;
        if (result > 0) {
            Twinkle* twinkle = (Twinkle*)twinkles;
            do {
                twinkle->update_twinkle();
                result = twinkle_count;
                ++index;
                twinkle = (Twinkle*)((char*)twinkle + 0x30);
            } while (index < result);
        }
    }
    return result;
}
