// initialize_input @ 0x40aa50 (thiscall, ret)

class InputState {
public:
    int initialize_input();

    int field_00;
    int pressed;        // +0x04
    int released;       // +0x08
    int previous;       // +0x0c
    int inverse_current; // +0x10
    int field_14;
    int field_18;
    int field_1c;
    int field_20;
    int field_24;
    int authored_x;     // +0x28
    int authored_y;     // +0x2c
    int field_30;
    int current;        // +0x34
};

int InputState::initialize_input()
{
    inverse_current = -1;
    current = 0;
    pressed = 0;
    released = 0;
    previous = 0;
    field_14 = 0;
    field_18 = 0;
    authored_x = 0x43a00000;
    authored_y = 0x43700000;
    field_30 = 0;
    return 0;
}
