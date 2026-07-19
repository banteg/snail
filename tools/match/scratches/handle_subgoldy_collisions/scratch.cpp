// handle_subgoldy_collisions @ 0x444cf0 (thiscall, ret) — cRSubGoldy::Collision()
// Eight pool sweeps against the player's cached camera target: salt,
// sub-lazer, garbage (intrusive list), slugs, track rings/parcels, health
// pickups, the speedup and jetpack singles, and the ring-effect ladder.
// Shared idiom: delta z pre-gate < threshold, then normalize_vector distance.

#include <stddef.h>

#include "damage_guage.h"
#include "garbage_hazard_slot.h"
#include "sub_hover.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "salt_hazard_types.h"
#include "slug_hazard_types.h"
#include "sound_effect_manager.h"
#include "subgame_runtime.h"
#include "sub_lazer_types.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_parcel_runtime.h"
#include "track_speedup.h"
#include "voice_manager.h"

typedef Vector3 Vec3;

float __fastcall normalize_vector(Vec3* vector);
int next_math_random_value();
void noop_runtime_ai();
int sprintf(char* buffer, const char* format, ...);

extern char g_parcel_format[];

void Player::handle_subgoldy_collisions()
{
    enum {
        SALT_POOL_FROM_SUBGAME =
            offsetof(SubgameRuntime, salt_hazards) + offsetof(SaltManager, slots),
        SALT_STATE_FROM_SUBGAME = SALT_POOL_FROM_SUBGAME + offsetof(Salt, state),
        SALT_POSITION_FROM_SUBGAME =
            SALT_POOL_FROM_SUBGAME
            + offsetof(Salt, transform)
            + offsetof(TransformMatrix, position),
        SALT_COLLISION_ARMED_FROM_SUBGAME =
            SALT_POOL_FROM_SUBGAME
            + offsetof(Salt, collision_armed),
        SUB_LAZER_POOL_FROM_SUBGAME =
            offsetof(SubgameRuntime, sub_lazers)
            + offsetof(SubLazerManager, slots),
        SUB_LAZER_STATE_FROM_SUBGAME =
            SUB_LAZER_POOL_FROM_SUBGAME + offsetof(SubLazer, state),
        SUB_LAZER_POSITION_FROM_SUBGAME =
            SUB_LAZER_POOL_FROM_SUBGAME
            + offsetof(SubLazer, transform)
            + offsetof(TransformMatrix, position)
    };

    Vec3 probe_b;      // v67
    Vec3 probe_c;      // v68
    Vec3 delta;        // v69
    Vec3 probe_salt;   // vector (also rings/effects source)
    Vec3 burst_offset;
    Vec3 burst_position; // v76
    Vec3 probe_rings;  // v77
    Vec3 probe_fx;     // v78

    if (!attachment_exit_pending && !boost_one_tick && !control_override_active) {
        if ((movement_flags & 0x80) == 0) {
            for (int i = 0;
                 i < (int)sizeof(game->salt_hazards.slots);
                i += (int)sizeof(Salt)) {
                char* slot = (char*)game + i;
                if (*(int*)(slot + SALT_STATE_FROM_SUBGAME) == 1
                    && *(unsigned char*)(slot + SALT_COLLISION_ARMED_FROM_SUBGAME) == 1) {
                    delta.x = *(float*)(slot + SALT_POSITION_FROM_SUBGAME
                                       + offsetof(Vector3, x))
                            - cached_camera_target_world.x;
                    delta.y = *(float*)(slot + SALT_POSITION_FROM_SUBGAME
                                       + offsetof(Vector3, y))
                            - cached_camera_target_world.y;
                    delta.z = *(float*)(slot + SALT_POSITION_FROM_SUBGAME
                                       + offsetof(Vector3, z))
                            - cached_camera_target_world.z;
                    probe_salt = delta;
                    if (delta.z < 1.0f && normalize_vector(&probe_salt) < 0.98000002f) {
                        if (damage_retrigger_timer == 0.0f)
                            damage_retrigger_timer = damage_retrigger_step;
                        *(unsigned char*)((char*)game + i
                            + SALT_COLLISION_ARMED_FROM_SUBGAME) = 0;
                        damage_gauge.apply_damage_gauge_delta(0.15000001f, 0);
                    }
                }
            }
        }
        for (int j = 0;
             j < (int)sizeof(game->sub_lazers.slots);
             j += (int)sizeof(SubLazer)) {
            char* slot = (char*)game + j;
            if (*(int*)(slot + SUB_LAZER_STATE_FROM_SUBGAME)
                == SUB_LAZER_STATE_ACTIVE) {
                delta.x = *(float*)(slot + SUB_LAZER_POSITION_FROM_SUBGAME
                                   + offsetof(Vector3, x))
                        - cached_camera_target_world.x;
                delta.y = *(float*)(slot + SUB_LAZER_POSITION_FROM_SUBGAME
                                   + offsetof(Vector3, y))
                        - cached_camera_target_world.y;
                delta.z = *(float*)(slot + SUB_LAZER_POSITION_FROM_SUBGAME
                                   + offsetof(Vector3, z))
                        - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 1.0f && normalize_vector(&probe_b) < 0.49000001f) {
                    *(int*)((char*)game + j + SUB_LAZER_STATE_FROM_SUBGAME) =
                        SUB_LAZER_STATE_RECYCLE_PENDING;
                    damage_gauge.apply_damage_gauge_delta(0.02f, 0);
                }
            }
        }
        for (SubGarbage* garbage = game->garbage_hazards.active_head;
             garbage;
             garbage = garbage->next_active) {
            if (garbage->state == SUB_GARBAGE_STATE_ACTIVE) {
                delta.x = garbage->transform.position.x - cached_camera_target_world.x;
                delta.y = garbage->transform.position.y - cached_camera_target_world.y;
                delta.z = garbage->transform.position.z - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 1.0f && normalize_vector(&probe_b) < 0.98000002f) {
                    if ((movement_flags & 0x80) == 0) {
                        velocity.x = velocity.x - probe_b.x * velocity.z * 0.18000001f;
                        velocity.z = velocity.z - probe_b.z * velocity.z * 0.1f;
                    }
                    garbage->state = SUB_GARBAGE_STATE_BURST_PENDING;
                    if (probe_b.x >= 0.0f)
                        garbage->collision_side = SUB_GARBAGE_COLLISION_SIDE_RIGHT;
                    else
                        garbage->collision_side = SUB_GARBAGE_COLLISION_SIDE_LEFT;
                    add_subgoldy_score(SUBGOLDY_SCORE_GARBAGE, 0);
                    damage_gauge.apply_damage_gauge_delta(0.039999999f, 0);
                    g_sound_effect_manager.play_sound_effect(
                        39 - (int)((float)next_math_random_value()
                            * -0.000061035156f));
                }
            }
        }
        for (int m = 0;
             m < (int)sizeof(game->slug_hazards.slots);
             m += (int)sizeof(Slug)) {
            Slug* slug = (Slug*)((char*)game->slug_hazards.slots + m);
            int state = slug->state;
            if (state == SUB_SLUG_STATE_ACTIVE
                || state == SUB_SLUG_STATE_LATERAL_ACTIVE) {
                delta.x = slug->transform.position.x - cached_camera_target_world.x;
                delta.y = slug->transform.position.y - cached_camera_target_world.y;
                delta.z = slug->transform.position.z - cached_camera_target_world.z;
                probe_b = delta;
                if (delta.z < 2.0f) {
                    float distance = normalize_vector(&probe_b);
                    if (distance < 1.5675001f) {
                        if ((movement_flags & 0x80) == 0) {
                            if (!control_override_active) {
                                SubgameRuntime* hit_game = game;
                                control_override_active = 1;
                                follow_state.active = 0;
                                float rate = hit_game->subgame_rate;
                                velocity =
                                    Vector3(0.0f, 0.2f, -0.2f) * rate;
                                begin_post_follow_carryover();
                                presentation.cutscene.state =
                                    CUT_SCENE_STATE_DEATH_PENDING;
                                slug->player_encounter_latched = 1;
                                slug->play_slug_voice(
                                    34 - (int)((float)next_math_random_value()
                                        * -0.000061035156f));
                                float half = distance * 0.5f;
                                presentation.wobble.lift_phase_step = 0.0f;
                                burst_offset = probe_b * half;
                                probe_salt.x = burst_offset.x + cached_camera_target_world.x;
                                burst_position.x = probe_salt.x;
                                int slot_id = player_slot;
                                probe_salt.y = burst_offset.y + cached_camera_target_world.y;
                                burst_position.y = probe_salt.y;
                                probe_salt.z = burst_offset.z + cached_camera_target_world.z;
                                burst_position.z = probe_salt.z;
                                firework.firework_shoot(
                                    &burst_position, slot_id, 92, 80);
                            } else {
                                float rate = game->subgame_rate;
                                float scaled_rate = rate * rate * 0.0040000002f;
                                velocity.z = scaled_rate * -8.0f;
                                damage_gauge.apply_damage_gauge_delta(1.0f, 0);
                            }
                        } else {
                            slug->kill_slug_hazard();
                        }
                    }
                }
            }
        }
        for (int n = 0;
             n < (int)sizeof(game->parcel_manager.slots);
             n += (int)sizeof(Parcel)) {
            Parcel* parcel =
                (Parcel*)((char*)game->parcel_manager.slots + n);
            if (parcel->state == PARCEL_STATE_TRACK_ACTIVE) {
                probe_salt.x = parcel->position.x - cached_camera_target_world.x;
                probe_salt.y = parcel->position.y - cached_camera_target_world.y;
                probe_salt.z = parcel->position.z - cached_camera_target_world.z;
                probe_rings = probe_salt;
                if (probe_salt.z < 1.0f && normalize_vector(&probe_rings) < 1.24f) {
                    add_subgoldy_score(SUBGOLDY_SCORE_PARCEL_COLLECT, 0);
                    g_voice_manager.play_voice_manager(
                        VOICE_SET_PACKAGE, VOICE_PLAY_AFTER_GLOBAL_COOLDOWN, -1);
                    g_sound_effect_manager.play_sound_effect(27);
                    parcel->state = PARCEL_STATE_COLLECT_PENDING;
                    SubgameRuntime* parcel_game = game;
                    int collected = parcels_collected + 1;
                    parcels_collected = collected;
                    if (!parcel_game->level_mode)
                        sprintf(
                            parcel_game->lives_text_widget->text_buffer,
                            g_parcel_format,
                            collected,
                            parcel_game->level_definition.parcel_count);
                }
            }
        }
    }
    for (int ii = 0;
         ii < (int)sizeof(game->health_pickups);
         ii += (int)sizeof(SubHealth)) {
        SubHealth* pickup = (SubHealth*)((char*)game->health_pickups + ii);
        if (pickup->state == TRACK_PICKUP_STATE_ACTIVE) {
            probe_b.x = pickup->position.x - cached_camera_target_world.x;
            probe_b.y = pickup->position.y - cached_camera_target_world.y;
            probe_c.x = probe_b.x;
            probe_c.y = probe_b.y;
            probe_b.z = pickup->position.z - cached_camera_target_world.z;
            probe_c.z = probe_b.z;
            if (transform.position.y >= 0.49000001f && probe_b.z < 1.0f) {
                float pickup_y;
                if (probe_b.y < 0.0f)
                    pickup_y = -probe_b.y;
                else
                    pickup_y = probe_b.y;
                if (pickup_y < 0.40000001f
                    && normalize_vector(&probe_c) < 0.98000002f) {
                    g_sound_effect_manager.play_sound_effect(14);
                    pickup->state = TRACK_PICKUP_STATE_TEARDOWN_PENDING;
                    health_collect_particles(pickup);
                    damage_gauge.apply_damage_gauge_delta(-0.5f, 0);
                }
            }
        }
    }
    SubSpeedUp* speedup = &game->speedup_pickup;
    if (speedup->state == TRACK_PICKUP_STATE_ACTIVE) {
        probe_b.x = speedup->transform.position.x - cached_camera_target_world.x;
        probe_b.y = speedup->transform.position.y - cached_camera_target_world.y;
        probe_c.x = probe_b.x;
        probe_c.y = probe_b.y;
        probe_b.z = speedup->transform.position.z - cached_camera_target_world.z;
        probe_c.z = probe_b.z;
        if (transform.position.y >= 0.49000001f && probe_b.z < 1.0f) {
            float pickup_y;
            if (probe_b.y < 0.0f)
                pickup_y = -probe_b.y;
            else
                pickup_y = probe_b.y;
            if (pickup_y < 0.40000001f
                && normalize_vector(&probe_c) < 0.98000002f) {
                speedup->state = TRACK_PICKUP_STATE_TEARDOWN_PENDING;
                noop_runtime_ai();
                velocity.z = game->subgame_rate * 0.5f;
            }
        }
    }
    JetPack* jetpack = &game->jetpack_pickup;
    if (jetpack->state == TRACK_PICKUP_STATE_ACTIVE) {
        probe_b.x = jetpack->position.x - cached_camera_target_world.x;
        probe_b.y = jetpack->position.y - cached_camera_target_world.y;
        probe_c.x = probe_b.x;
        probe_c.y = probe_b.y;
        probe_b.z = jetpack->position.z - cached_camera_target_world.z;
        probe_c.z = probe_b.z;
        if (transform.position.y >= 0.49000001f && probe_b.z < 1.0f && normalize_vector(&probe_c) < 3.0f) {
            jetpack->state = TRACK_PICKUP_STATE_TEARDOWN_PENDING;
            sub_hover.arm_jetpack_gauge();
        }
    }
    for (int jj = 0;
         jj < (int)sizeof(game->ring_effects.slots);
         jj += (int)sizeof(SubRing)) {
        SubRing* effect = (SubRing*)((char*)game->ring_effects.slots + jj);
        if (effect->state == SUB_RING_STATE_ACTIVE) {
            probe_salt.x = effect->transform.position.x - cached_camera_target_world.x;
            probe_salt.y = effect->transform.position.y - cached_camera_target_world.y;
            probe_salt.z = effect->transform.position.z - cached_camera_target_world.z;
            probe_fx = probe_salt;
            if (probe_salt.z < 1.0f) {
                if (normalize_vector(&probe_fx) < 0.98000002f) {
                    effect->state = SUB_RING_STATE_COLLECT_PENDING;
                    if (!completion_handoff_active) {
                        SubgameRuntime* effect_game = game;
                        SubRingKind kind = effect->kind;
                        if (kind == SUB_RING_KIND_SLOW_DEFAULT
                            || kind == SUB_RING_KIND_SLOW_AUTHORED) {
                            velocity.z = -0.1f;
                            g_sound_effect_manager.play_sound_effect(43);
                        } else {
                            velocity.z = effect_game->subgame_rate * 0.5f;
                        }
                    }
                    SubgameRuntime* ladder_game = game;
                    SubRingKind effect_kind = effect->kind;
                    if (effect_kind == SUB_RING_KIND_NORMAL_DEFAULT
                        || effect_kind == SUB_RING_KIND_NORMAL_AUTHORED) {
                        int current_lives = lives;
                        if (current_lives < 10) {
                            if ((ladder_game->runtime_flags
                                    & SUBGAME_RUNTIME_FLAG_RING_LIFE_REWARD)
                                    != 0
                                && ladder_game->level_mode != 3)
                                lives = current_lives + 1;
                            g_voice_manager.play_voice_manager(
                                VOICE_SET_POWER_UP,
                                VOICE_PLAY_AFTER_GLOBAL_COOLDOWN,
                                -1);
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
                        add_subgoldy_score(SUBGOLDY_SCORE_RING, 0);
                        continue;
                    }
                    if (effect_kind == SUB_RING_KIND_POWER_UP_AUTHORED) {
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
                        add_subgoldy_score(SUBGOLDY_SCORE_RING, 0);
                        continue;
                    }
                    if (effect_kind == SUB_RING_KIND_UNKNOWN_1) {
                        add_subgoldy_score(SUBGOLDY_SCORE_RING, 0);
                        g_sound_effect_manager.play_sound_effect(1);
                    } else if (effect_kind == SUB_RING_KIND_EXPLODE_RAMP
                        || effect_kind == SUB_RING_KIND_EXPLODE_AUTHORED) {
                        add_subgoldy_score(SUBGOLDY_SCORE_RING, 0);
                        g_sound_effect_manager.play_sound_effect(42);
                        nuke_effect_progress = nuke_effect_progress_step;
                        nuke.initialize_nuke();
                    }
                }
            }
        }
    }
}
