// Contact-damage gauge controller view, cross-checked by initialize, update,
// and apply-delta paths. The +0x24/+0x28 pair doubles as the hit-flash
// animation driver and the voice/skin retrigger gate in apply_damage_gauge_delta.
#ifndef DAMAGE_GAUGE_H
#define DAMAGE_GAUGE_H

class DamageGaugeController {
public:
    void initialize_damage_gauge(); // @ 0x440fa0
    void update_damage_gauge(); // @ 0x440fd0
    void apply_damage_gauge_delta(float delta, char force); // @ 0x4413f0

    int state; // +0x00
    float pulse_progress; // +0x04
    float pulse_step; // +0x08
    unsigned char unresolved_byte_0c; // +0x0c
    char unknown_0d[0x10 - 0x0d];
    float warning_transition_progress; // +0x10
    float warning_transition_step; // +0x14
    int skin_hold_ticks; // +0x18
    float fill; // +0x1c
    float display_fill; // +0x20
    float hit_flash_progress; // +0x24
    float hit_flash_step; // +0x28
};

typedef char DamageGaugeController_must_be_0x2c[
    (sizeof(DamageGaugeController) == 0x2c) ? 1 : -1];

#endif
