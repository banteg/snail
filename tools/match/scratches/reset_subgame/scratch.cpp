// reset_subgame @ 0x437b10 (thiscall, ret)

#include "subgame_runtime.h"
#include "game_time.h"

typedef unsigned int DWORD;

extern "C" void* memcpy(void* dest, const void* src, unsigned int count);
#pragma intrinsic(memcpy)

void SubgameRuntime::reset_subgame()
{
    int health_count = sizeof(health_pickups) / sizeof(health_pickups[0]);
    SubHealth* health = health_pickups;
    do {
        health->state = 0;
        health->owner_game = this;
        ++health;
        --health_count;
    } while (health_count);

    speedup_pickup.state = 0;
    speedup_pickup.owner_game = this;
    jetpack_pickup.state = 0;
    jetpack_pickup.owner_game = this;

    SubGarbage* garbage = garbage_hazards.slots;
    int garbage_count =
        sizeof(garbage_hazards.slots) / sizeof(garbage_hazards.slots[0]);
    do {
        garbage->state = 0;
        garbage->game = this;
        garbage->next_active = 0;
        ++garbage;
        --garbage_count;
    } while (garbage_count);

    Slug* slug = slug_hazards.slots;
    int slug_count =
        sizeof(slug_hazards.slots) / sizeof(slug_hazards.slots[0]);
    do {
        slug->state = 0;
        slug->owner_game = this;
        ++slug;
        --slug_count;
    } while (slug_count);

    SubRing* ring = ring_effects.slots;
    int ring_count =
        sizeof(ring_effects.slots) / sizeof(ring_effects.slots[0]);
    do {
        ring->state = 0;
        ring->rate_source = this;
        ++ring;
        --ring_count;
    } while (ring_count);

    if (replay_launch_active == 1
        && level_mode == current_high_score_record.replay_mode_id) {
        DWORD saved_score = current_high_score_record.score;
        DWORD saved_tail_a = current_high_score_record.score_tail;
        player.total_score = saved_score;
        DWORD saved_tail_b = current_high_score_record.source_tail;
        player.score_tail = saved_tail_a;
        memcpy(&player.stopwatch, &current_high_score_record.timer, sizeof(Time));
        player.startup_track_index = saved_tail_b;
    } else {
        if (subgame_rebuild_selector == 2) {
            player.total_score = 0;
            player.clear_subgoldy_score_buckets();
        }
        player.stopwatch.Zero();
        player.score_tail = 0;
        player.startup_track_index = 0;
    }

    player.last_ring_spawn_z = 0.0f;
    scan_reset = 1;
    camera_snap_requested = 1;
    replay_launch_active = 0;
    garbage_hazards.active_head = 0;
}
