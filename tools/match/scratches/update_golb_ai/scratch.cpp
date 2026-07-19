// update_golb_ai @ 0x414820 (thiscall, ret) — one live Golb shot per tick.
// Straight or path-follow flight, homing blend (kind 2), per-kind trail
// effects, garbage/slug contact sweeps, wall-14 impact, lifetime cleanup.

#include <stddef.h>

#include "golb.h"
#include "player.h"
#include "score_buckets.h"
#include "subgame_runtime.h"
#include "transform_matrix.h"
#include "vapour.h"
#include "vector3.h"

typedef Vector3 Vec3;
float __fastcall normalize_vector(Vec3* vector);

void GolbShot::update_golb_ai()
{
    enum {
        SLUG_POOL_FROM_SUBGAME =
            offsetof(SubgameRuntime, slug_hazards) + offsetof(SlugPool, slots),
        SLUG_POOL_EXTENT = sizeof(((SlugPool*)0)->slots),
        SLUG_SLOT_STRIDE = sizeof(Slug),
        SLUG_STATE_FROM_SUBGAME =
            SLUG_POOL_FROM_SUBGAME + offsetof(Slug, state),
        SLUG_POSITION_FROM_SUBGAME =
            SLUG_POOL_FROM_SUBGAME
            + offsetof(Slug, transform)
            + offsetof(TransformMatrix, position)
    };

    float speed;
    float deflect_speed;
    float lived;
    Vec3* new_output;
    Vec3* new_direction;
    Vec3 probe;
    Vec3 delta;
    Vec3 target_delta;
    Vec3 blended_velocity;
    Vec3 pull_delta;
    Vec3 kept_velocity;
    Vec3 reflected_velocity;
    Vec3 smoke_position;
    Vec3 trail_a;
    Vec3 trail_b;
    Vec3 wall_impact;

    if (game->subgame_pause_gate)
        return;
    if (skip_one_tick == 1) {
        skip_one_tick = 0;
        return;
    }
    switch (state) {
    case 1:
        break;
    default:
        return;
    }

    if (path_follow.active == 1) {
        switch (path_follow.calc_path_length_z(path_factor, &flight_transform.position, &velocity)) {
        case 1:
        case 3:
            {
                Vec3* raw_position = &flight_transform.position;
                Vec3* output_position = &source_matrix.position;
                *output_position = *raw_position;
            }
            break;
        case 0:
        case 2:
            source_matrix.position = path_follow.output_position;
            break;
        default:
            break;
        }
    } else {
        Vec3* movement = &velocity;
        Vec3* current_position = &flight_transform.position;
        current_position->x = movement->x + current_position->x;
        current_position->y = movement->y + current_position->y;
        current_position->z = movement->z + current_position->z;
        if (kind == 0) {
            if (flight_transform.position.y > 0.49000001f || flight_transform.position.y < 0.0f) {
                velocity.y = velocity.y - game->subgame_rate * 0.017000001f;
            } else {
                velocity.y = 0.0f;
            }
        } else if (kind == 2 && homing_target_object) {
            float blend = homing_blend_step + homing_blend;
            homing_blend = blend;
            if (blend > 1.0f)
                homing_blend = 1.0f;
            speed = normalize_vector(&velocity);
            target_delta.x = homing_target.x - current_position->x;
            target_delta.y = homing_target.y - current_position->y;
            target_delta.z = homing_target.z - current_position->z;
            delta = target_delta;
            if (normalize_vector(&delta) < 0.40000001f) {
                spawn_golb_impact_sprite(&flight_transform.position);
                goto retire;
            }
            float pull = homing_blend;
            pull_delta.x = delta.x * pull;
            pull_delta.y = delta.y * pull;
            pull_delta.z = delta.z * pull;
            float keep = 1.0f - homing_blend * 1.5f;
            kept_velocity.x = keep * velocity.x;
            kept_velocity.y = keep * movement->y;
            kept_velocity.z = keep * movement->z;
            blended_velocity.x = kept_velocity.x + pull_delta.x;
            blended_velocity.y = kept_velocity.y + pull_delta.y;
            blended_velocity.z = kept_velocity.z + pull_delta.z;
            velocity = blended_velocity;
            normalize_vector(&velocity);
            velocity.x = speed * velocity.x;
            movement->y = speed * movement->y;
            movement->z = speed * movement->z;
            if (speed < 0.1f)
                goto retire;
        }
        source_matrix.position = flight_transform.position;
        if (path_entry_z_latch < source_matrix.position.z && flight_transform.position.y < 1.0f && flight_transform.position.y > 0.0f) {
            SubLoc* cell = game->get_track_grid_cell_at_world_position(&source_matrix.position);
            if (cell->tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE) {
                path_entry_z_latch = source_matrix.position.z;
                path_follow.initialize_path_follow_golb(
                    cell, &flight_transform.position, this);
            }
            if (velocity.z > 1.0f
                && (cell - 8)->tile_id == SUBLOC_TILE_PATH_ENTRY_UPPERCASE) {
                path_entry_z_latch = source_matrix.position.z + 1.0f;
                path_follow.initialize_path_follow_golb(
                    cell - 8, &flight_transform.position, this);
            }
        }
    }

    switch (kind) {
    case 2: {
        float spun = spin_step + spin;
        spin = spun;
        tertiary_body.transform = source_matrix;
        if (spun > 6.2831855f)
            spin = spun - 6.2831855f;
        spawn_golb_smoke(&source_matrix.position);
        smoke_position = source_matrix.position - direction * 0.5f;
        spawn_golb_smoke(&smoke_position);
        break;
    }
    case 1:
        vapour.add_vapour_point(&source_matrix);
        break;
    case 0: {
        Vec3* body_position = &render_sprite->position;
        *body_position = source_matrix.position;
        spawn_golb_trail_sprite(&source_matrix.position);
        trail_a = source_matrix.position - direction * 0.30000001f;
        spawn_golb_trail_sprite(&trail_a);
        trail_b = source_matrix.position - direction * 0.60000002f;
        spawn_golb_trail_sprite(&trail_b);
        break;
    }
    }

    new_output = &source_matrix.position;
    new_direction = &direction;
    *new_direction = *new_output - previous_flight_transform.position;
    if (kind == 2) {
        tertiary_body.transform.set_matrix_z_direction(direction);
        tertiary_body.transform.rotate_matrix_local_z(spin);
    }
    lived = lifetime_step + lifetime;
    lifetime = lived;
    previous_flight_transform.position = source_matrix.position;
    if (lived <= 1.0f) {
        Player* bounds_player = player;
        if (flight_transform.position.z >= bounds_player->interaction_max_z
            && bounds_player->transform.position.z + 46.0f >= flight_transform.position.z) {
            SubGarbage* garbage = game->garbage_hazards.active_head;
            while (garbage) {
                if (garbage->state == SUB_GARBAGE_STATE_ACTIVE) {
                    probe.x = garbage->transform.position.x - new_output->x;
                    probe.y = garbage->transform.position.y - new_output->y;
                    probe.z = garbage->transform.position.z - new_output->z;
                    float dz = probe.z;
                    if (dz < 0.0f)
                        dz = -dz;
                    if (dz < 3.0f
                        && normalize_vector(&probe) < garbage->radius + 0.49000001f) {
                        garbage->state = SUB_GARBAGE_STATE_BURST_PENDING;
                        garbage->collision_side = probe.x >= 0.0f
                            ? SUB_GARBAGE_COLLISION_SIDE_RIGHT
                            : SUB_GARBAGE_COLLISION_SIDE_LEFT;
                        player->add_subgoldy_score(SUBGOLDY_SCORE_GARBAGE, 0);
                        if (kind != 1)
                            goto garbage_hit;
                    }
                }
                garbage = garbage->next_active;
            }

            {
                int slug_index = 0;
                for (int m = 0; m < SLUG_POOL_EXTENT; m += SLUG_SLOT_STRIDE) {
                    char* slot = (char*)game + m;
                    int slug_state = *(int*)(slot + SLUG_STATE_FROM_SUBGAME);
                    if (slug_state == SUB_SLUG_STATE_ACTIVE
                        || slug_state == SUB_SLUG_STATE_LATERAL_ACTIVE) {
                        probe.x = *(float*)(slot + SLUG_POSITION_FROM_SUBGAME
                                           + offsetof(Vector3, x))
                                - new_output->x;
                        probe.y = *(float*)(slot + SLUG_POSITION_FROM_SUBGAME
                                           + offsetof(Vector3, y))
                                - new_output->y;
                        probe.z = *(float*)(slot + SLUG_POSITION_FROM_SUBGAME
                                           + offsetof(Vector3, z))
                                - new_output->z;
                        float dz = probe.z;
                        if (dz < 0.0f)
                            dz = -dz;
                        if (dz < 2.5f && normalize_vector(&probe) < 2.5f) {
                            path_follow.active = 0;
                            deflect_speed = normalize_vector(&velocity);
                            probe.y = 0.0f;
                            normalize_vector(&probe);
                            reflected_velocity.x = -(deflect_speed * probe.x);
                            reflected_velocity.y = 0.0f;
                            reflected_velocity.z = -(deflect_speed * probe.z);
                            velocity.x = reflected_velocity.x;
                            velocity.y = reflected_velocity.y;
                            velocity.z = reflected_velocity.z;
                            if (kind == 1) {
                                kill_golb();
                                spawn_golb_impact_sprite(new_output);
                                ((Slug*)((char*)game
                                    + SLUG_SLOT_STRIDE * slug_index
                                    + SLUG_POOL_FROM_SUBGAME))->hit_slug_hazard(2);
                                return;
                            }
                            if (kind == 2) {
                                kill_golb();
                                spawn_golb_impact_sprite(new_output);
                                ((Slug*)((char*)game
                                    + SLUG_SLOT_STRIDE * slug_index
                                    + SLUG_POOL_FROM_SUBGAME))->hit_slug_hazard(4);
                                return;
                            }
                            if (kind == 0) {
                                if (slug_bounce_armed) {
                                    kill_golb();
                                    spawn_golb_impact_sprite(new_output);
                                } else {
                                    slug_bounce_armed = 1;
                                }
                                return;
                            }
                        }
                    }
                    ++slug_index;
                }
                goto wall_probe;
            }

garbage_hit:
            kill_golb();
            spawn_golb_impact_sprite(new_output);
            if (kind == 2) {
                for (SubGarbage* splash = game->garbage_hazards.active_head;
                    splash;
                    splash = splash->next_active) {
                    if (splash->state == SUB_GARBAGE_STATE_ACTIVE) {
                        probe.x = splash->transform.position.x - new_output->x;
                        probe.y = splash->transform.position.y - new_output->y;
                        probe.z = splash->transform.position.z - new_output->z;
                        if (normalize_vector(&probe) < 3.0f) {
                            splash->state = SUB_GARBAGE_STATE_BURST_PENDING;
                            if (probe.x >= 0.0f)
                                splash->collision_side = SUB_GARBAGE_COLLISION_SIDE_RIGHT;
                            else
                                splash->collision_side = SUB_GARBAGE_COLLISION_SIDE_LEFT;
                            player->add_subgoldy_score(SUBGOLDY_SCORE_GARBAGE, 0);
                        }
                    }
                }
            }
            return;

wall_probe:
            if (game->get_track_grid_cell_at_world_position(new_output)->tile_id
                != SUBLOC_TILE_WALL2)
                return;
            wall_impact.x = new_output->x;
            wall_impact.y = new_output->y;
            wall_impact.z = new_output->z - 1.0f;
            spawn_golb_impact_sprite(&wall_impact);
        }
    }
retire:
    kill_golb();
}
