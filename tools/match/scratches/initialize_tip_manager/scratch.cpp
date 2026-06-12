// initialize_tip_manager @ 0x448cf0 (thiscall, ret)

struct TipSlot {
    int active;                // +0x00
    char unknown_04[0x20 - 0x04];
};

class TipManager {
public:
    void initialize_tip_manager();

    char unknown_00[0x38];
    TipSlot slots[3];          // +0x38
};

void TipManager::initialize_tip_manager()
{
    TipSlot* slot = slots;
    int count = 3;
    do {
        slot->active = 0;
        ++slot;
        --count;
    } while (count != 0);
}
