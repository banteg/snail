// update_twinkle_manager @ 0x404030 (thiscall, ret)

class Twinkle {
public:
    int update_twinkle();
};

class TwinkleManager {
public:
    int update_twinkle_manager();

    char twinkles[0xf0]; // +0x00, five stride-0x30 records
    int active_state; // +0xf0
    int twinkle_count; // +0xf4
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
