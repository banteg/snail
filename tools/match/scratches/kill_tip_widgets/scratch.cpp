// kill_tip_widgets @ 0x4489e0 (thiscall, ret)

extern char* g_game_base; // data_4df904

struct FrontendWidget;

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

class TipSlot {
public:
    void kill_tip_widgets();

    int active;                // +0x00
    char unknown_04[0x0c - 0x04];
    FrontendWidget* body;      // +0x0c
    FrontendWidget* ok_button; // +0x10
    FrontendWidget* disable_button; // +0x14
};

void TipSlot::kill_tip_widgets()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(body);
    if (ok_button != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(ok_button);
    }
    if (disable_button != 0) {
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(disable_button);
    }
    active = 0;
}
