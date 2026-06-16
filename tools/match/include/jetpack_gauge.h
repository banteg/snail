// Jetpack gauge controller view, partial. Cross-checked by initialize, arm,
// hover-end, particle uninit, and the attachment-follow state read.
#ifndef JETPACK_GAUGE_H
#define JETPACK_GAUGE_H

class Sprite;

struct JetParticleSlot {
    Sprite* sprite; // +0x00
    float wobble_x; // +0x04
    float wobble_y; // +0x08
    float wobble_alpha; // +0x0c
};

typedef char JetParticleSlot_must_be_0x10[
    (sizeof(JetParticleSlot) == 0x10) ? 1 : -1];

class JetpackGaugeController {
public:
    int initialize_jetpack_gauge(int player_slot); // @ 0x43a930
    int arm_jetpack_gauge(); // @ 0x43a980
    void end_jetpack_hover(); // @ 0x43a370
    void uninit_jet_particles(); // @ 0x43a580
    void update_jet_particles(); // @ 0x43a690
    void update_jetpack_gauge(); // called by update_subgoldy, scratch pending

    float progress; // +0x00
    float progress_step; // +0x04
    int unknown_08; // +0x08
    int state; // +0x0c
    void* player; // +0x10
    float wobble_x; // +0x14
    float wobble_y; // +0x18
    float wobble_alpha; // +0x1c
    JetParticleSlot particle_slots[15][2]; // +0x20
    void* game; // +0x200
    char unknown_204[0x20c - 0x204];
    float warning_intensity_latch; // +0x20c
    float warning_intensity; // +0x210
};

typedef char JetpackGaugeController_must_be_0x214[
    (sizeof(JetpackGaugeController) == 0x214) ? 1 : -1];

#endif
