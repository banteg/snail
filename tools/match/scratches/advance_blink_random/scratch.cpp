// advance_blink_random @ 0x4408a0 (thiscall, ret)

class BlinkRandomTable {
public:
    double advance_blink_random();

    char unknown_000000[0x3bb700];
    int index; // +0x3bb700
    float samples[24]; // +0x3bb704
};

double BlinkRandomTable::advance_blink_random()
{
    int next_index = (index + 1) % 24;
    index = next_index;
    return samples[next_index];
}
