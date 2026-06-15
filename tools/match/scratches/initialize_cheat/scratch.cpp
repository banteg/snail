// initialize_cheat @ 0x404740 (thiscall, ret)

class CheatState {
public:
    int initialize_cheat();

    int field_00;
    int field_04;
    int field_08;
    int field_0c;
};

int CheatState::initialize_cheat()
{
    field_08 = 0;
    field_0c = 0;
    field_00 = 0;
    return 0;
}
