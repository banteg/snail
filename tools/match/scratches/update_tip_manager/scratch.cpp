// update_tip_manager @ 0x448d80 (fastcall, ret)

struct TipSlot {
    void update_tip();

    int active;                // +0x00
    char unknown_04[0x20 - 0x04];
};

class TipManager {
public:
    void update_tip_manager();

    char unknown_00[0x38];
    TipSlot slots[3];          // +0x38
};

void TipManager::update_tip_manager()
{
    TipSlot* slot = slots;
    int count = 3;
    do {
        if (slot->active == 1) {
            slot->update_tip();
        }
        ++slot;
        --count;
    } while (count != 0);
}
