// start_squidge_y @ 0x444980 (thiscall, ret 4)

class SquidgeState {
public:
    void start_squidge_y(float value);

    float y_output;   // +0x00
    float y_velocity; // +0x04
    float y_phase;    // +0x08
};

void SquidgeState::start_squidge_y(float value)
{
    y_phase = 0.0f;
    y_velocity = value * 0.5f;
}
