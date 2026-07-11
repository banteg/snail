// Authored cRSubHover, exact 0x214-byte hover countdown and jet-VFX owner.
#ifndef SUB_HOVER_H
#define SUB_HOVER_H

class Sprite;
class Player;
class SubgameRuntime;
struct Vector3;

struct JetParticleSlot {
    Sprite* sprite; // +0x00
    float wobble_x; // +0x04
    float wobble_y; // +0x08
    float wobble_alpha; // +0x0c
};

typedef char JetParticleSlot_must_be_0x10[
    (sizeof(JetParticleSlot) == 0x10) ? 1 : -1];

class SubHover {
public:
    void initialize_jetpack_gauge(int player_slot); // @ 0x43a930, cRSubHover::Init
    void arm_jetpack_gauge(); // @ 0x43a980, cRSubHover::On
    void end_jetpack_hover(); // @ 0x43a370, cRSubHover::End
    void uninit_jet_particles(); // @ 0x43a580, cRSubHover::JetUnInit
    void initialize_jet_particles(); // @ 0x43a5b0, cRSubHover::JetInit
    void update_jet_particles(); // @ 0x43a690, cRSubHover::Jets
    void update_jetpack_gauge(); // @ 0x43a390, cRSubHover::AI
    // Stable Windows target name for the folded no-op also called as
    // cRSubHover::Hover(Vector3&, float).
    void spawn_track_speedup(Vector3* position, float progress); // alias @ 0x43d880

    float progress; // +0x00
    float progress_step; // +0x04
    int unknown_08; // +0x08
    int state; // +0x0c
    Player* player; // +0x10, borrowed containing player
    float wobble_x; // +0x14
    float wobble_y; // +0x18
    float wobble_alpha; // +0x1c
    JetParticleSlot particle_slots[15][2]; // +0x20
    SubgameRuntime* game; // +0x200, borrowed owning subgame
    char unknown_204[0x20c - 0x204];
    float warning_intensity_latch; // +0x20c
    float warning_intensity; // +0x210
};

typedef char SubHover_must_be_0x214[(sizeof(SubHover) == 0x214) ? 1 : -1];

#endif
