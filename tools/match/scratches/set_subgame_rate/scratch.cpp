// set_subgame_rate @ 0x4404c0 (thiscall, ret 0x4)

class Subgame
{
public:
    void set_subgame_rate(float rate);

    char pad_00[0x30];
    float rate; // 0x30
    char pad_34[0x38 - 0x34];
    float target_rate; // 0x38
};

void Subgame::set_subgame_rate(float rate_value)
{
    rate = rate_value;
    target_rate = rate_value;
}
