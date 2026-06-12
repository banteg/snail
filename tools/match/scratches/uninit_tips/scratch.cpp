// uninit_tips @ 0x448d10 (thiscall, ret)

class TipSlot {
public:
    void kill_tip_widgets();

    int active;                // +0x00
    char unknown_04[0x20 - 0x04];
};

class TipManager {
public:
    void uninit_tips();

    char unknown_00[0x38];
    TipSlot slots[3];          // +0x38
};

void TipManager::uninit_tips()
{
    TipSlot* slot = slots;
    int count = 3;
    do {
        if (slot->active == 1) {
            slot->kill_tip_widgets();
        }
        ++slot;
        --count;
    } while (count != 0);
}
