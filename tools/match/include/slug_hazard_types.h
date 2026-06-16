// Shared slug hazard runtime view, recovered from hit/kill/voice/explosion paths.
// Game stays scratch-local because each caller only needs a sparse game view.
#ifndef SLUG_HAZARD_TYPES_H
#define SLUG_HAZARD_TYPES_H

#include "bod_types.h"

class Game;

class SlugHazardRuntime : public RenderableBod {
public:
    SlugHazardRuntime* initialize_slug_hazard_runtime(); // @ 0x408530
    void update_slug_voice_ai();                         // @ 0x43f520
    void play_slug_voice(int sample_index);              // @ 0x43f560
    void hit_slug_hazard(int damage);                     // @ 0x43f620
    int explode_slug_hazard();                            // @ 0x43f680
    void kill_slug_hazard();                              // @ 0x43f8b0

    char unknown_78[0x80 - 0x78];
    int state;                        // +0x80
    int death_toss_direction;         // +0x84
    Game* owner_game;                 // +0x88
    char unknown_8c[0xc8 - 0x8c];
    int hit_points;                   // +0xc8
    unsigned char hit_flash_pending;  // +0xcc
    char unknown_cd[0xd8 - 0xcd];
    unsigned char voice_active;       // +0xd8
    unsigned char player_hit_latched; // +0xd9, set by first player-hit cutscene path
    char unknown_da[0xdc - 0xda];
    float voice_progress;             // +0xdc
    float voice_progress_step;        // +0xe0
    char unknown_e4[0xec - 0xe4];
};

typedef char SlugHazardRuntime_must_be_0xec[
    (sizeof(SlugHazardRuntime) == 0xec) ? 1 : -1];

#endif
