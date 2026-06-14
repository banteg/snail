// initialize_blink_random @ 0x4408c0 (thiscall, ret)

int next_math_random_value();

class BlinkRandomTable {
public:
    int initialize_blink_random();

    char unknown_000000[0x3bb700];
    int index; // +0x3bb700
    float samples[24]; // +0x3bb704
};

int BlinkRandomTable::initialize_blink_random()
{
    index = 0;
    float* sample = samples;
    int remaining = 24;
    int result;

    do {
        result = next_math_random_value();
        --remaining;
        *sample = 1.0f / (((float)result * 0.000030517578f + 1.0f) * 60.0f);
        ++sample;
    } while (remaining);

    return result;
}
