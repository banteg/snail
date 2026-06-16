// handle_subgoldy_collisions @ 0x444cf0 (thiscall, ret) — cRSubGoldy::Collision()
// Eight pool sweeps against the player's cached camera target: salt,
// sub-lazer, garbage (intrusive list), slugs, track rings/parcels, health
// pickups, the speedup and jetpack singles, and the ring-effect ladder.
// Shared idiom: delta z pre-gate < threshold, then normalize_vector distance.

#include "damage_gauge.h"
#include "garbage_hazard_slot.h"
#include "jetpack_gauge.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "salt_hazard_types.h"
#include "slug_hazard_types.h"
#include "sub_lazer_types.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_parcel_runtime.h"
#include "track_speedup.h"

typedef Vector3 Vec3;

float __fastcall normalize_vector(Vec3* vector);
int next_math_random_value();
void firework_shoot(float* position, int player_slot, int a3, int a4);
void noop_runtime_ai();
int sprintf(char* buffer, const char* format, ...);

struct VoiceManager {
    void play_voice_manager(int voice, unsigned char flag, int arg);
};
extern VoiceManager g_voice_manager; // unk_751498

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};
extern SoundEffectManager g_sound_effect_manager;

extern char g_parcel_format[];

class Game {
public:
    char unknown_00[0x38];
    float subgame_rate; // +0x38
    char unknown_3c[0x40 - 0x3c];
    int level_mode; // +0x40
    int level_mode_arg; // +0x44
    float base_subgame_rate; // +0x48
    unsigned int runtime_flags; // +0x4c
    char unknown_50[0x1b01e0 - 0x50];
    int parcel_total; // +0x1b01e0
    char unknown_1b01e4[0x355db0 - 0x1b01e4];
    TrackSpeedupRuntime speedup_pickup; // +0x355db0
    TrackJetpackPickup jetpack_pickup; // +0x355e64
    TrackHealthPickup health_pickups[8]; // +0x356000
    SlugHazardRuntime slug_slots[8]; // +0x3563a0, stride 0xec
    SubLazerSlot lazer_slots[20]; // +0x356b00, stride 0xb0
    SaltHazardSlot salt_slots[40]; // +0x3578c0, live byte is velocity.z low byte
    char unknown_359080[0x359140 - (0x3578c0 + 6080)];
    GarbageHazardPool garbage_hazards; // +0x359140
    RingOrSpecialEffectParent ring_effects[2]; // +0x35b78c
    char unknown_35bb7c[0x35bb94 - (0x35b78c + 1008)];
    int hud_text_owner; // +0x35bb94
    char unknown_35bb98[0x125e480 - 0x35bb98];
    TrackParcelPool track_parcels; // +0x125e480
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
                SaltHazardSlot* slot =
                    (SaltHazardSlot*)((char*)game + i + 0x3578c0);
                if (slot->state == 1 && *(unsigned char*)&slot->velocity.z == 1) {
                    delta.x = slot->position.x - cached_camera_target_world.x;
                    delta.y = slot->position.y - cached_camera_target_world.y;
                    delta.z = slot->position.z - cached_camera_target_world.z;
                    probe_salt = delta;
                    if (delta.z < 1.0f && normalize_vector(&probe_salt) < 0.98000002f) {
                        if (damage_retrigger_timer == 0.0f)
                            damage_retrigger_timer = damage_retrigger_step;
                        *(unsigned char*)&slot->velocity.z = 0;
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
        for (GarbageHazardSlot* garbage = game->garbage_hazards.active_head;
             garbage;
             garbage = garbage->next_active) {
            if (garbage->state == 1) {
                delta.x = garbage->world_position.x - cached_camera_target_world.x;
                delta.y = garbage->world_position.y - cached_camera_target_world.y;
                delta.z = garbage->world_position.z - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 1.0f && normalize_vector(&probe_b) < 0.98000002f) {
                    if ((movement_flags & 0x80) == 0) {
                        velocity.x = velocity.x - probe_b.x * velocity.z * 0.18000001f;
                        velocity.z = velocity.z - probe_b.z * velocity.z * 0.1f;
                    }
                    garbage->state = 2;
                    if (probe_b.x >= 0.0f)
                        garbage->collision_side = 1;
                    else
                        garbage->collision_side = 2;
                    add_subgoldy_score(0, 0);
                    damage_gauge.apply_damage_gauge_delta(0.039999999f, 0);
                    g_sound_effect_manager.play_sound_effect(39 - (int)(__int64)((double)next_math_random_value() * -0.000061035156));
                }
            }
        }
        for (int m = 0; m < 1888; m += 236) {
            SlugHazardRuntime* slug =
                (SlugHazardRuntime*)((char*)game + m + 0x3563a0);
            int state = slug->state;
            if (state == 1 || state == 4) {
                delta.x = slug->transform.position.x - cached_camera_target_world.x;
                delta.y = slug->transform.position.y - cached_camera_target_world.y;
                delta.z = slug->transform.position.z - cached_camera_target_world.z;
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
                                presentation.cutscene_ai_state = 10;
                                slug->player_hit_latched = 1;
                                slug->play_slug_voice(
                                    34 - (int)(__int64)((double)next_math_random_value() * -0.000061035156));
                                float half = distance * 0.5f;
                                presentation.wobble_lift_phase_step = 0.0f;
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
                            slug->kill_slug_hazard();
                        }
                    }
                }
            }
        }
        for (int n = 0; n < 7000; n += 140) {
            TrackParcelRuntime* parcel =
                (TrackParcelRuntime*)((char*)game + n + 0x125e480);
            if (parcel->state == 1) {
                probe_salt.x = parcel->world_position.x - cached_camera_target_world.x;
                probe_salt.y = parcel->world_position.y - cached_camera_target_world.y;
                probe_salt.z = parcel->world_position.z - cached_camera_target_world.z;
                probe_rings = probe_salt;
                if (probe_salt.z < 1.0f && normalize_vector(&probe_rings) < 1.24f) {
                    add_subgoldy_score(3, 0);
                    g_voice_manager.play_voice_manager(10, 1, -1);
                    g_sound_effect_manager.play_sound_effect(27);
                    parcel->state = 4;
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
        TrackHealthPickup* pickup =
            (TrackHealthPickup*)((char*)game + ii + 0x356000);
        if (pickup->state == 1) {
            probe_b.x = pickup->world_position.x - cached_camera_target_world.x;
            probe_b.y = pickup->world_position.y - cached_camera_target_world.y;
            probe_c.x = probe_b.x;
            probe_c.y = probe_b.y;
            probe_b.z = pickup->world_position.z - cached_camera_target_world.z;
            probe_c.z = probe_b.z;
            if (position.y >= 0.49000001f && probe_b.z < 1.0f) {
                float dy = probe_b.y;
                if (dy < 0.0f)
                    dy = -dy;
                if (dy < 0.40000001f && normalize_vector(&probe_c) < 0.98000002f) {
                    g_sound_effect_manager.play_sound_effect(14);
                    pickup->state = 2;
                    health_collect_particles(pickup);
                    damage_gauge.apply_damage_gauge_delta(-0.5f, 0);
                }
            }
        }
    }
    TrackSpeedupRuntime* speedup = &game->speedup_pickup;
    if (speedup->state == 1) {
        probe_b.x = speedup->world_position.x - cached_camera_target_world.x;
        probe_b.y = speedup->world_position.y - cached_camera_target_world.y;
        probe_c.x = probe_b.x;
        probe_c.y = probe_b.y;
        probe_b.z = speedup->world_position.z - cached_camera_target_world.z;
        probe_c.z = probe_b.z;
        if (position.y >= 0.49000001f && probe_b.z < 1.0f) {
            float dy = probe_b.y;
            if (dy < 0.0f)
                dy = -dy;
            if (dy < 0.40000001f && normalize_vector(&probe_c) < 0.98000002f) {
                speedup->state = 2;
                noop_runtime_ai();
                velocity.z = game->subgame_rate * 0.5f;
            }
        }
    }
    TrackJetpackPickup* jetpack = &game->jetpack_pickup;
    if (jetpack->state == 1) {
        probe_b.x = jetpack->world_position.x - cached_camera_target_world.x;
        probe_b.y = jetpack->world_position.y - cached_camera_target_world.y;
        probe_c.x = probe_b.x;
        probe_c.y = probe_b.y;
        probe_b.z = jetpack->world_position.z - cached_camera_target_world.z;
        probe_c.z = probe_b.z;
        if (position.y >= 0.49000001f && probe_b.z < 1.0f && normalize_vector(&probe_c) < 3.0f) {
            jetpack->state = 2;
            jetpack_gauge.arm_jetpack_gauge();
        }
    }
    for (int jj = 0; jj < 1008; jj += 504) {
        RingOrSpecialEffectParent* effect =
            (RingOrSpecialEffectParent*)((char*)game + jj + 0x35b78c);
        if (effect->state == 1) {
            probe_salt.x = effect->position.x - cached_camera_target_world.x;
            probe_salt.y = effect->position.y - cached_camera_target_world.y;
            probe_salt.z = effect->position.z - cached_camera_target_world.z;
            probe_fx = probe_salt;
            if (probe_salt.z < 1.0f) {
                if (normalize_vector(&probe_fx) < 0.98000002f) {
                    effect->state = 2;
                    if (!completion_handoff_active) {
                        Game* effect_game = game;
                        int kind = effect->kind;
                        if (kind == 3 || kind == 7) {
                            velocity.z = -0.1f;
                            g_sound_effect_manager.play_sound_effect(43);
                        } else {
                            velocity.z = effect_game->subgame_rate * 0.5f;
                        }
                    }
                    Game* ladder_game = game;
                    int effect_kind = effect->kind;
                    if (effect_kind == 4 || effect_kind == 5) {
                        int current_lives = lives;
                        if (current_lives < 10) {
                            if ((ladder_game->runtime_flags & 0x10) != 0 && ladder_game->level_mode != 3)
                                lives = current_lives + 1;
                            g_voice_manager.play_voice_manager(5, 1, -1);
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
                        g_sound_effect_manager.play_sound_effect(effect_index + 1);
                        add_subgoldy_score(2, 0);
                        continue;
                    }
                    if (effect_kind == 8) {
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
                        g_sound_effect_manager.play_sound_effect(effect_index + 1);
                        add_subgoldy_score(2, 0);
                        continue;
                    }
                    if (effect_kind == 1) {
                        add_subgoldy_score(2, 0);
                        g_sound_effect_manager.play_sound_effect(1);
                    } else if (effect_kind == 2 || effect_kind == 6) {
                        add_subgoldy_score(2, 0);
                        g_sound_effect_manager.play_sound_effect(42);
                        nuke_effect_progress = nuke_effect_progress_step;
                        nuke.initialize_nuke();
                    }
                }
            }
        }
    }
}
