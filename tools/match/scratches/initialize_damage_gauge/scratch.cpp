// initialize_damage_gauge @ 0x440fa0 (thiscall, ret)

class DamageGaugeController {
public:
    void initialize_damage_gauge();

    int state;                         // +0x00
    float pulse_progress;              // +0x04
    float pulse_step;                  // +0x08
    unsigned char unresolved_byte_0c;  // +0x0c
    char unknown_0d[0x10 - 0x0d];
    float warning_transition_progress; // +0x10
    char unknown_14[0x18 - 0x14];
    int skin_hold_ticks;               // +0x18
    float fill;                        // +0x1c
    float display_fill;                // +0x20
    float hit_flash_progress;          // +0x24
    float hit_flash_step;              // +0x28
};

void DamageGaugeController::initialize_damage_gauge()
{
    pulse_step = 0.020833334f;
    fill = 0.0f;
    display_fill = 0.0f;
    skin_hold_ticks = 0;
    state = 0;
    warning_transition_progress = 0.0f;
    unresolved_byte_0c = 0;
    pulse_progress = 0.0f;
    hit_flash_progress = 0.0f;
    hit_flash_step = 0.0333333351f;
}
