// handle_subgoldy_collisions @ 0x444cf0 (thiscall, ret) — cRSubGoldy::Collision()
// Eight pool sweeps against the player's cached camera target: salt,
// sub-lazer, garbage (intrusive list), slugs, track rings/parcels, health
// pickups, the speedup and jetpack singles, and the ring-effect ladder.
// Shared idiom: delta z pre-gate < threshold, then normalize_vector distance.

#include "damage_gauge.h"
#include "jetpack_gauge.h"

struct Vec3 {
    float x;
    float y;
    float z;
};

class TrackHealthPickup;

float __fastcall normalize_vector(Vec3* vector);
void play_sound_effect(int effect_id);
int next_math_random_value();
void kill_slug_hazard(int slug);
void play_slug_voice(int slug, int voice);
void play_voice_manager(int manager, int voice, unsigned char flag, int arg);
void firework_shoot(float* position, int player_slot, int a3, int a4);
void noop_runtime_ai();
int initialize_nuke(float* nuke);
int sprintf(char* buffer, const char* format, ...);

extern int unk_751498[];
extern char g_parcel_format[];

struct Game {
    char unknown_00[0x38];
    float subgame_rate; // +0x38
    char unknown_3c[0x40 - 0x3c];
    int level_mode; // +0x40
    int level_mode_arg; // +0x44
    float base_subgame_rate; // +0x48
    unsigned int runtime_flags; // +0x4c
    char unknown_50[0x1b01e0 - 0x50];
    int parcel_total; // +0x1b01e0
    char unknown_1b01e4[0x355e18 - 0x1b01e4];
    float speedup_position[3]; // +0x355e18
    char unknown_355e24[0x355e30 - 0x355e24];
    int speedup_state; // +0x355e30
    char unknown_355e34[0x355e74 - 0x355e34];
    float jetpack_position[3]; // +0x355e74
    char unknown_355e80[0x355e9c - 0x355e80];
    int jetpack_state; // +0x355e9c
    char unknown_355ea0[0x356000 - 0x355ea0];
    char health_slots[928]; // +0x356000 stride 116: pos +0x10, state +0x38
    char slug_slots[1888]; // +0x3563a0 stride 236: object +0x00, pos +0x68, state +0x80, hit byte +0xd9
    char lazer_slots[3520]; // +0x356b00 stride 176: pos +0x68, state +0x80
    char salt_slots[6080]; // +0x3578c0 stride 152: pos +0x68, state +0x80, live byte +0x94
    char unknown_359080[0x359140 - (0x3578c0 + 6080)];
    int garbage_list_head; // +0x359140
    char unknown_359144[0x35b78c - 0x359144];
    char ring_effect_slots[1008]; // +0x35b78c stride 504: pos +0x68, state +0x80, kind +0x88
    char unknown_35bb7c[0x35bb94 - (0x35b78c + 1008)];
    int hud_text_owner; // +0x35bb94
    char unknown_35bb98[0x125e480 - 0x35bb98];
    char track_ring_slots[7000]; // +0x125e480 stride 140: pos +0x10, state +0x38
};

struct Player {
    void handle_subgoldy_collisions();
    void begin_post_follow_carryover();
    void add_subgoldy_score(int event_id, int value);
    char health_collect_particles(TrackHealthPickup* pickup);

    char unknown_00[0x6c];
    float live_position_y; // +0x6c
    char unknown_70[0x150 - 0x70];
    char nuke_object[0x1d4 - 0x150]; // +0x150
    float damage_retrigger_timer; // +0x1d4
    float damage_retrigger_step;  // +0x1d8
    char unknown_1dc[0x2d8 - 0x1dc];
    // (the nuke fields live lower in the struct: progress 0x374, step 0x378,
    // and initialize_nuke receives player+0x150 as its this; settle that
    // interior object when the nuke port lands)
    unsigned char control_override_active; // +0x2d8
    char unknown_2d9[0x308 - 0x2d9];
    int movement_flag_selector; // +0x308
    char unknown_30c[0x338 - 0x30c];
    unsigned char movement_flags; // +0x338
    char unknown_339[0x374 - 0x339];
    float nuke_effect_progress;      // +0x374
    float nuke_effect_progress_step; // +0x378
    char unknown_37c[0x380 - 0x37c];
    int player_slot; // +0x380
    unsigned char follow_active; // +0x384
    char unknown_385[0x3c4 - 0x385];
    DamageGaugeController damage_gauge; // +0x3c4
    char unknown_3f0[0x404 - 0x3f0];
    int lives; // +0x404
    Game* game; // +0x408
    char unknown_40c[0x410 - 0x40c];
    Vec3 velocity; // +0x410
    unsigned char boost_one_tick;          // +0x41c
    unsigned char attachment_exit_pending; // +0x41d
    char unknown_41e[0x440 - 0x41e];
    unsigned char completion_handoff_active; // +0x440
    char unknown_441[0x2750 - 0x441];
    JetpackGaugeController jetpack_gauge; // +0x2750
    Vec3 cached_camera_target_world; // +0x2964
    char unknown_2970[0x3f4c - 0x2970];
    float wobble_lift_phase_step; // +0x3f4c
    char unknown_3f50[0x42e8 - 0x3f50];
    int cutscene_ai_state; // +0x42e8
    char unknown_42ec[0x4338 - 0x42ec];
    int parcels_collected; // +0x4338
};

void Player::handle_subgoldy_collisions()
{
    Vec3 delta;        // v69
    Vec3 probe_salt;   // vector (also rings/effects source)
    Vec3 probe_b;      // v67
    Vec3 probe_c;      // v68
    Vec3 probe_rings;  // v77
    Vec3 probe_fx;     // v78
    float burst_position[3];

    if (!attachment_exit_pending && !boost_one_tick && !control_override_active) {
        if ((movement_flags & 0x80) == 0) {
            for (int i = 0; i < 6080; i += 152) {
                char* slot = (char*)game + i;
                if (*(int*)(slot + 0x357940) == 1 && *(unsigned char*)(slot + 0x357954) == 1) {
                    delta.x = *(float*)(slot + 0x357928) - cached_camera_target_world.x;
                    delta.y = *(float*)(slot + 0x35792c) - cached_camera_target_world.y;
                    delta.z = *(float*)(slot + 0x357930) - cached_camera_target_world.z;
                    probe_salt = delta;
                    if (delta.z < 1.0f && normalize_vector(&probe_salt) < 0.98000002f) {
                        if (damage_retrigger_timer == 0.0f)
                            damage_retrigger_timer = damage_retrigger_step;
                        *(unsigned char*)((char*)game + i + 0x357954) = 0;
                        damage_gauge.apply_damage_gauge_delta(0.15000001f, 0);
                    }
                }
            }
        }
        for (int j = 0; j < 3520; j += 176) {
            char* slot = (char*)game + j;
            if (*(int*)(slot + 0x356b80) == 1) {
                delta.x = *(float*)(slot + 0x356b68) - cached_camera_target_world.x;
                delta.y = *(float*)(slot + 0x356b6c) - cached_camera_target_world.y;
                delta.z = *(float*)(slot + 0x356b70) - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 1.0f && normalize_vector(&probe_b) < 0.49000001f) {
                    *(int*)((char*)game + j + 0x356b80) = 2;
                    damage_gauge.apply_damage_gauge_delta(0.02f, 0);
                }
            }
        }
        for (int k = game->garbage_list_head; k; k = *(int*)(k + 0x80)) {
            if (*(int*)(k + 0x84) == 1) {
                delta.x = *(float*)(k + 0x68) - cached_camera_target_world.x;
                delta.y = *(float*)(k + 0x6c) - cached_camera_target_world.y;
                delta.z = *(float*)(k + 0x70) - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 1.0f && normalize_vector(&probe_b) < 0.98000002f) {
                    if ((movement_flags & 0x80) == 0) {
                        velocity.x = velocity.x - probe_b.x * velocity.z * 0.18000001f;
                        velocity.z = velocity.z - probe_b.z * velocity.z * 0.1f;
                    }
                    *(int*)(k + 0x84) = 2;
                    if (probe_b.x >= 0.0f)
                        *(int*)(k + 0x88) = 1;
                    else
                        *(int*)(k + 0x88) = 2;
                    add_subgoldy_score(0, 0);
                    damage_gauge.apply_damage_gauge_delta(0.039999999f, 0);
                    play_sound_effect(39 - (int)(__int64)((double)next_math_random_value() * -0.000061035156));
                }
            }
        }
        for (int m = 0; m < 1888; m += 236) {
            Game* slug_game = game;
            int state = *(int*)((char*)slug_game + m + 0x356420);
            char* slot = (char*)slug_game + m;
            if (state == 1 || state == 4) {
                delta.x = *(float*)(slot + 0x356408) - cached_camera_target_world.x;
                delta.y = *(float*)(slot + 0x35640c) - cached_camera_target_world.y;
                delta.z = *(float*)(slot + 0x356410) - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 2.0f) {
                    float distance = normalize_vector(&probe_b);
                    if (distance < 1.5675001f) {
                        if ((movement_flags & 0x80) == 0) {
                            if (control_override_active) {
                                float rate = game->subgame_rate;
                                float scaled_rate = rate * rate * 0.0040000002f;
                                velocity.z = scaled_rate * -8.0f;
                                damage_gauge.apply_damage_gauge_delta(1.0f, 0);
                            } else {
                                Game* hit_game = game;
                                control_override_active = 1;
                                follow_active = 0;
                                float rate = hit_game->subgame_rate;
                                velocity.x = 0.0f;
                                float lift = rate * 0.2f;
                                velocity.y = lift;
                                float knockback = rate * -0.2f;
                                velocity.z = knockback;
                                begin_post_follow_carryover();
                                Game* voice_game = game;
                                cutscene_ai_state = 10;
                                *((char*)voice_game + m + 0x356479) = 1;
                                play_slug_voice(
                                    (int)((char*)game + m + 0x3563a0),
                                    34 - (int)(__int64)((double)next_math_random_value() * -0.000061035156));
                                float half = distance * 0.5f;
                                wobble_lift_phase_step = 0.0f;
                                float burst_x = half * probe_b.x;
                                float burst_y = probe_b.y * half;
                                probe_salt.x = burst_x + cached_camera_target_world.x;
                                burst_position[0] = probe_salt.x;
                                int slot_id = player_slot;
                                probe_salt.y = burst_y + cached_camera_target_world.y;
                                burst_position[1] = probe_salt.y;
                                probe_salt.z = half * probe_b.z + cached_camera_target_world.z;
                                burst_position[2] = probe_salt.z;
                                firework_shoot(burst_position, slot_id, 92, 80);
                            }
                        } else {
                            kill_slug_hazard((int)((char*)game + m + 0x3563a0));
                        }
                    }
                }
            }
        }
        for (int n = 0; n < 7000; n += 140) {
            char* slot = (char*)game + n;
            if (*(int*)(slot + 0x125e4b8) == 1) {
                probe_salt.x = *(float*)(slot + 0x125e490) - cached_camera_target_world.x;
                probe_salt.y = *(float*)(slot + 0x125e494) - cached_camera_target_world.y;
                probe_salt.z = *(float*)(slot + 0x125e498) - cached_camera_target_world.z;
                probe_rings = probe_salt;
                if (probe_salt.z < 1.0f && normalize_vector(&probe_rings) < 1.24f) {
                    add_subgoldy_score(3, 0);
                    play_voice_manager((int)unk_751498, 10, 1, -1);
                    play_sound_effect(27);
                    *(int*)((char*)game + n + 0x125e4b8) = 4;
                    Game* parcel_game = game;
                    int collected = parcels_collected + 1;
                    parcels_collected = collected;
                    if (!parcel_game->level_mode)
                        sprintf(
                            (char*)(parcel_game->hud_text_owner + 716),
                            g_parcel_format,
                            collected,
                            parcel_game->parcel_total);
                }
            }
        }
    }
    for (int ii = 0; ii < 928; ii += 116) {
        char* slot = (char*)game + ii;
        if (*(int*)(slot + 0x356038) == 1) {
            probe_b.x = *(float*)(slot + 0x356010) - cached_camera_target_world.x;
            probe_b.y = *(float*)(slot + 0x356014) - cached_camera_target_world.y;
            probe_c.x = probe_b.x;
            probe_c.y = probe_b.y;
            probe_b.z = *(float*)(slot + 0x356018) - cached_camera_target_world.z;
            probe_c.z = probe_b.z;
            if (live_position_y >= 0.49000001f && probe_b.z < 1.0f) {
                float dy = probe_b.y;
                if (dy < 0.0f)
                    dy = -dy;
                if (dy < 0.40000001f && normalize_vector(&probe_c) < 0.98000002f) {
                    play_sound_effect(14);
                    *(int*)((char*)game + ii + 0x356038) = 2;
                    health_collect_particles((TrackHealthPickup*)((char*)game + ii + 0x356000));
                    damage_gauge.apply_damage_gauge_delta(-0.5f, 0);
                }
            }
        }
    }
    Game* speedup_game = game;
    if (speedup_game->speedup_state == 1) {
        probe_b.x = speedup_game->speedup_position[0] - cached_camera_target_world.x;
        probe_b.y = speedup_game->speedup_position[1] - cached_camera_target_world.y;
        probe_c.x = probe_b.x;
        probe_c.y = probe_b.y;
        probe_b.z = speedup_game->speedup_position[2] - cached_camera_target_world.z;
        probe_c.z = probe_b.z;
        if (live_position_y >= 0.49000001f && probe_b.z < 1.0f) {
            float dy = probe_b.y;
            if (dy < 0.0f)
                dy = -dy;
            if (dy < 0.40000001f && normalize_vector(&probe_c) < 0.98000002f) {
                game->speedup_state = 2;
                noop_runtime_ai();
                velocity.z = game->subgame_rate * 0.5f;
            }
        }
    }
    Game* jetpack_game = game;
    if (jetpack_game->jetpack_state == 1) {
        probe_b.x = jetpack_game->jetpack_position[0] - cached_camera_target_world.x;
        probe_b.y = jetpack_game->jetpack_position[1] - cached_camera_target_world.y;
        probe_c.x = probe_b.x;
        probe_c.y = probe_b.y;
        probe_b.z = jetpack_game->jetpack_position[2] - cached_camera_target_world.z;
        probe_c.z = probe_b.z;
        if (live_position_y >= 0.49000001f && probe_b.z < 1.0f && normalize_vector(&probe_c) < 3.0f) {
            game->jetpack_state = 2;
            jetpack_gauge.arm_jetpack_gauge();
        }
    }
    for (int jj = 0; jj < 1008; jj += 504) {
        char* slot = (char*)game + jj;
        if (*(int*)(slot + 0x35b80c) == 1) {
            probe_salt.x = *(float*)(slot + 0x35b7f4) - cached_camera_target_world.x;
            probe_salt.y = *(float*)(slot + 0x35b7f8) - cached_camera_target_world.y;
            probe_salt.z = *(float*)(slot + 0x35b7fc) - cached_camera_target_world.z;
            probe_fx = probe_salt;
            if (probe_salt.z < 1.0f) {
                if (normalize_vector(&probe_fx) < 0.98000002f) {
                    *(int*)((char*)game + jj + 0x35b80c) = 2;
                    if (!completion_handoff_active) {
                        Game* effect_game = game;
                        int kind = *(int*)((char*)effect_game + jj + 0x35b814);
                        if (kind == 3 || kind == 7) {
                            velocity.z = -0.1f;
                            play_sound_effect(43);
                        } else {
                            velocity.z = effect_game->subgame_rate * 0.5f;
                        }
                    }
                    Game* ladder_game = game;
                    int effect_kind = *(int*)((char*)ladder_game + jj + 0x35b814);
                    switch (effect_kind) {
                    case 4:
                    case 5: {
                        int current_lives = lives;
                        if (current_lives < 10) {
                            if ((ladder_game->runtime_flags & 0x10) != 0 && ladder_game->level_mode != 3)
                                lives = current_lives + 1;
                            play_voice_manager((int)unk_751498, 5, 1, -1);
                        }
                        int selector = movement_flag_selector;
                        if (selector >= 8) {
                            if (selector == 8)
                                movement_flag_selector = 7;
                        } else {
                            movement_flag_selector = selector + 1;
                        }
                        int effect_index = movement_flag_selector - 1;
                        if (effect_index > 6)
                            effect_index = 6;
                        play_sound_effect(effect_index + 1);
                        add_subgoldy_score(2, 0);
                        continue;
                    }
                    case 8: {
                        int selector = movement_flag_selector;
                        if (selector >= 8) {
                            if (selector == 8)
                                movement_flag_selector = 7;
                        } else {
                            movement_flag_selector = selector + 1;
                        }
                        int effect_index = movement_flag_selector - 1;
                        if (effect_index > 6)
                            effect_index = 6;
                        play_sound_effect(effect_index + 1);
                        add_subgoldy_score(2, 0);
                        continue;
                    }
                    case 1:
                        add_subgoldy_score(2, 0);
                        play_sound_effect(1);
                        break;
                    case 2:
                    case 6:
                        add_subgoldy_score(2, 0);
                        play_sound_effect(42);
                        nuke_effect_progress = nuke_effect_progress_step;
                        initialize_nuke((float*)nuke_object);
                        break;
                    }
                }
            }
        }
    }
}
