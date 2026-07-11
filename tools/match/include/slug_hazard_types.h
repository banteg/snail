// Shared slug hazard runtime view, recovered from hit/kill/voice/explosion paths.
// The owner is the embedded subgame runtime; helpers may still use sparse casts
// when a focused source-shape proof requires them.
#ifndef SLUG_HAZARD_TYPES_H
#define SLUG_HAZARD_TYPES_H

#include "bod_types.h"
#include "sub_loc_fwd.h"

class Player;
class Sprite;
class SubgameRuntime;

class SlugHazardRuntime : public RenderableBod {
public:
    SlugHazardRuntime* initialize_slug_hazard_runtime(); // @ 0x408530
    void update_slug_voice_ai();                         // @ 0x43f520
    void play_slug_voice(int sample_index);              // @ 0x43f560
    void hit_slug_hazard(int damage);                     // @ 0x43f620
    int explode_slug_hazard();                            // @ 0x43f680
    void kill_slug_hazard();                              // @ 0x43f8b0
    void update_slug_hazard_ai();                         // @ 0x43f930

    char unknown_78[0x80 - 0x78];
    int state;                         // +0x80
    int death_toss_direction;          // +0x84
    SubgameRuntime* owner_game;        // +0x88
    Vector3 velocity;                  // +0x8c
    char unknown_98[0xac - 0x98];
    Sprite* sprite;                    // +0xac
    TrackRowCell* source_cell;         // +0xb0
    unsigned char passed_player;       // +0xb4
    char unknown_b5[0xb8 - 0xb5];
    float lateral_phase;               // +0xb8
    float lateral_phase_step;          // +0xbc
    Player* player;                    // +0xc0
    int engagement_voice_gate;         // +0xc4
    int hit_points;                    // +0xc8
    unsigned char hit_flash_pending;   // +0xcc
    char unknown_cd[0xd0 - 0xcd];
    float hit_flash_progress;          // +0xd0
    float hit_flash_progress_step;     // +0xd4
    unsigned char voice_active;        // +0xd8
    unsigned char player_encounter_latched; // +0xd9, proximity voice / first-hit latch
    char unknown_da[0xdc - 0xda];
    float voice_progress;              // +0xdc
    float voice_progress_step;         // +0xe0
    float blink_progress;              // +0xe4
    float blink_step;                  // +0xe8
};

typedef char SlugHazardRuntime_must_be_0xec[
    (sizeof(SlugHazardRuntime) == 0xec) ? 1 : -1];

class SlugHazardPool {
public:
    SlugHazardRuntime slots[8];
};

typedef char SlugHazardPool_must_be_0x760[
    (sizeof(SlugHazardPool) == 0x760) ? 1 : -1];

#endif
