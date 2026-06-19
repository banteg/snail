// reset_spring_float @ 0x41aa30 (thiscall)

class SpringFloat {
public:
    void reset_spring_float();

    float output;          // +0x00
    float velocity;        // +0x04
    float phase;           // +0x08
    float target_output;   // +0x0c
    float target_velocity; // +0x10
};

void SpringFloat::reset_spring_float()
{
    output = 0.0f;
    target_velocity = 0.0f;
    target_output = 0.0f;
    velocity = 0.0f;
    phase = 0.0f;
}
