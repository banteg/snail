// reset_tooltip @ 0x403be0 (thiscall, ret)

extern char* g_game_base; // data_4df904

class BorderRecord;

class BorderManager {
public:
    int kill_border(BorderRecord* border);
};

class TooltipState {
public:
    int reset_tooltip();

    int field_00;
    int state; // +0x04
    char unknown_008[0x18 - 0x008];
    BorderRecord* tooltip_widget; // +0x18
};

int TooltipState::reset_tooltip()
{
    int result = state;
    result -= 2;
    if (result != 0) {
        --result;
        if (result != 0)
            return result;

        result = ((BorderManager*)(g_game_base + 0xb4c))->kill_border(tooltip_widget);
        tooltip_widget = 0;
    }

    state = 1;
    return result;
}
