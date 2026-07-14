// Authored contact-damage controller. The shipped class and texture assets
// intentionally spell the owner cRDamageGuage.
#ifndef DAMAGE_GUAGE_H
#define DAMAGE_GUAGE_H

enum DamageGuageState {
    DAMAGE_GUAGE_STATE_MONITORING = 0,
    DAMAGE_GUAGE_STATE_WARNING_TRANSITION = 1,
    DAMAGE_GUAGE_STATE_DRAINING = 2,
};

class DamageGuage {
public:
    void initialize_damage_gauge(); // @ 0x440fa0, cRDamageGuage::Init
    void update_damage_gauge(); // @ 0x440fd0, cRDamageGuage::AI
    void apply_damage_gauge_delta(float delta, char force); // @ 0x4413f0, cRDamageGuage::Take

    DamageGuageState state; // +0x00
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

typedef char DamageGuage_must_be_0x2c[
    (sizeof(DamageGuage) == 0x2c) ? 1 : -1];

#endif
