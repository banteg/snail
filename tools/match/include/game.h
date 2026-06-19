// Game runtime view, partial. Keep this header for fields that are corroborated
// by multiple scratches before wider consolidation.
#ifndef GAME_H
#define GAME_H

#include "frontend_widget.h"
#include "garbage_hazard_slot.h"
#include "ring_special_effect_types.h"
#include "salt_hazard_types.h"
#include "slug_hazard_types.h"
#include "sub_lazer_types.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_speedup.h"
#include "vector3.h"

class Player;
struct TrackRowCell;

class Game {
public:
    void initialize_subgame(); // @ 0x4374b0
    void complete_subgame(unsigned char completed); // @ 0x438700
    void destroy_subgame(); // @ 0x438850
    unsigned int* spawn_track_health_pickup(TrackRowCell* cell, Player* player); // @ 0x43d6c0
    int spawn_track_jetpack_pickup(TrackRowCell* cell, Player* player); // @ 0x43d890
    void remove_subgame_bods(); // @ 0x440910
    void hide_gameplay_scores(); // @ 0x445f10
    void unhide_gameplay_scores(); // @ 0x445f40

    char unknown_000000[0x6d4];
    Vector3 star_spawn_direction; // +0x6d4
    char unknown_0006e0[0x6e4 - 0x6e0];
    Vector3 star_spawn_origin; // +0x6e4
    char unknown_0006f0[0x74621 - 0x6f0];
    unsigned char pause_gate; // +0x74621
    char unknown_074622[0x74650 - 0x74622];
    float subgame_rate; // +0x74650, root view of subgame +0x38
    char unknown_074654[0x74668 - 0x74654];
    int active_row_start; // +0x74668
    char unknown_07466c[0x74670 - 0x7466c];
    int active_row_end; // +0x74670
    char unknown_074674[0x355db0 - 0x74674];
    TrackSpeedupRuntime speedup_pickup; // +0x355db0
    TrackJetpackPickup jetpack_pickup; // +0x355e64
    TrackHealthPickup health_pickups[8]; // +0x356000
    SlugHazardRuntime slug_slots[8]; // +0x3563a0
    SubLazerSlot sub_lazer_pool[20]; // +0x356b00
    SaltHazardSlot salt_pool[40]; // +0x3578c0
    char unknown_359080[0x359140 - 0x359080];
    GarbageHazardPool garbage_hazards; // +0x359140
    RingOrSpecialEffectPool ring_effects; // +0x35b78c
    char unknown_35bb7c[0x35bbbc - 0x35bb7c];
};
typedef char Game_hud_widgets_must_reach_0x35bbbc[
    (sizeof(Game) == 0x35bbbc) ? 1 : -1];

#endif
