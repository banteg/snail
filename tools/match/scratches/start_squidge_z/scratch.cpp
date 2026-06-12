// start_squidge_z @ 0x4449a0 (thiscall, ret 4)

class SquidgeState {
public:
    void start_squidge_z(float value);

    float y_output;   // +0x00
    float y_velocity; // +0x04
    float y_phase;    // +0x08
    float z_output;   // +0x0c
    float z_velocity; // +0x10
    float z_phase;    // +0x14
};

void SquidgeState::start_squidge_z(float value)
{
    z_phase = value;
    z_velocity = value * -0.00300000003f;
}
