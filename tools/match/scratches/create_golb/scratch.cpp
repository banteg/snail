// create_golb @ 0x415280 (thiscall, ret 0xc)
// cRSubGolb::Create(cRSubGoldy*, int, int): link a projectile slot, seed its
// spawn position and velocity from Goldy's shoot-flag family, then install
// the sprite, vapour, or path-search presentation path used by update_golb_ai.

#include "bod_ai_dispatch.h"
#include "game_root.h"
#include "golb.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "vapour.h"
#include "vector3.h"

typedef unsigned int DWORD;

typedef Vector3 Vec3;

int report_errorf(char* format, ...);
int next_math_random_value();

void cRSubGolb::create_golb(cRSubGoldy* player_, int spawn_selector, int shot_slot_index)
{
    skip_one_tick = 0;
    slug_bounce_armed = 0;

    BodNode* body = this;
    g_game->active_bod_list.add_bod(body);

    owner_player = player_;
    DWORD kind_flags = player_->shoot_flags;
    if ((kind_flags & 7) != 0) {
        kind = 0;
    } else if ((kind_flags & 0x18) != 0) {
        kind = 1;
    } else if ((kind_flags & 0x60) != 0) {
        kind = 2;
    }

    source_matrix.Identity();

    cRSubGoldy* spawn_player = owner_player;
    Vec3* position = &flight_transform.position;
    state = 1;
    *position = spawn_player->transform.position;
    Vec3 half_forward = spawn_player->transform.basis_forward * 0.5f;
    *position += half_forward;

    cRSubGoldy* player = owner_player;
    DWORD shoot_flags = player->shoot_flags;
    if ((shoot_flags & 5) == 0) {
        if ((shoot_flags & 2) != 0) {
            if (spawn_selector == 2) {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_BLASTER_LEFT_FIRE];
                *position = *source;
                position->x += 0.5f;
            } else if (spawn_selector == 1) {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_BLASTER_RIGHT_FIRE];
                *position = *source;
                position->x -= 0.5f;
            }
            Vec3 staged_velocity;
            staged_velocity.x = 0.0f;
            staged_velocity.y = 0.0f;
            staged_velocity.z = player->velocity.z + 1.0f;
            velocity = staged_velocity;
            goto after_default_launch_family;
        }

        if ((shoot_flags & 0x18) == 0) {
            if ((shoot_flags & 0x60) == 0) {
                if ((shoot_flags & 0x29) != 0) {
                    Vec3 staged_velocity;
                    staged_velocity.x = 0.0f;
                    staged_velocity.y = 0.0f;
                    staged_velocity.z = player->velocity.z + 1.0f;
                    velocity = staged_velocity;
                    goto after_default_launch_family;
                }

                if ((shoot_flags & 0x52) != 0) {
                    Vec3 staged_velocity;
                    staged_velocity.x = 0.0f;
                    staged_velocity.y = 0.0f;
                    staged_velocity.z = player->velocity.z + 1.0f;
                    velocity = staged_velocity;
                    if (spawn_selector == 2)
                        position->x += 0.5f;
                    else
                        position->x -= 0.5f;
                }
                goto after_default_launch_family;
            }

            {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_ROCKET_BASE];
                *position = *source;
                Vec3 staged_velocity;
                staged_velocity.x = 0.0f;
                staged_velocity.y = 0.0f;
                staged_velocity.z = player->velocity.z + 0.60000002f;
                velocity = staged_velocity;
            }
            goto after_default_launch_family;
        }

        {
            if (spawn_selector == 2) {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_LASER_LEFT];
                *position = *source;
                if (player->transform.basis_forward.z > 0.0f)
                    spawn_selector =
                        (int)&player->presentation.snail_hotspots_world[
                            SNAIL_HOTSPOT_LASER_LEFT].z;
                else
                    spawn_selector = 0;
            } else {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_LASER_RIGHT];
                *position = *source;
                if (player->transform.basis_forward.z > 0.0f)
                    spawn_selector =
                        (int)&player->presentation.snail_hotspots_world[
                            SNAIL_HOTSPOT_LASER_LEFT].z;
                else
                    spawn_selector = 0;
            }
            skip_one_tick = 1;
            Vec3 staged_velocity;
            staged_velocity.x = 0.0f;
            staged_velocity.y = 0.0f;
            staged_velocity.z = player->velocity.z + 1.0f;
            velocity = staged_velocity;
        }
        goto after_default_launch_family;

after_default_launch_family:
        ;
    } else {
        Vec3* source;
        if (spawn_selector == 3) {
            source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_BLASTER_LEFT_FIRE];
            goto copy_shoot_flag_source;
        }
        if (spawn_selector == 2) {
            source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_BLASTER_RIGHT_FIRE];
            goto copy_shoot_flag_source;
        }
        if (spawn_selector == 1) {
            source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_BLASTER_TOP_FIRE];
            goto copy_shoot_flag_source;
        }
        goto after_shoot_flag_source;

copy_shoot_flag_source:
        *position = *source;

after_shoot_flag_source:

        if ((player->shoot_flags & 4) != 0) {
            if (spawn_selector == 3) {
                velocity.x = 0.1f;
                velocity.y = 0.0f;
                velocity.z = player->velocity.z + 1.0f;
                position->x += 0.5f;
            } else if (spawn_selector == 2) {
                velocity.x = -0.1f;
                velocity.y = 0.0f;
                velocity.z = player->velocity.z + 1.0f;
                position->x -= 0.5f;
            } else {
                velocity.x = 0.0f;
                velocity.y = 0.0f;
                velocity.z = player->velocity.z + 1.0f;
            }
        } else {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = player->velocity.z + 1.0f;
        }
    }

    if (kind == 1) {
        velocity.x += velocity.x;
        velocity.y += velocity.y;
        velocity.z += velocity.z;
    }
    if (kind == 2) {
        velocity.x *= 0.80000001f;
        velocity.y *= 0.80000001f;
        velocity.z *= 0.80000001f;
    }

    direction = velocity;

    switch (kind) {
        case 2: {
            lifetime = 0.0f;
            lifetime_step = game->subgame_rate * 0.027777776f;
            rocket_owner_shot = this;
            spin = 0.0f;
            spin_step = 0.20943952f;
            homing_target_object = 0;

            g_game->active_bod_list.add_bod(&tertiary_body);

            this->shot_slot_index = shot_slot_index;
            ContactTargetEntry* found =
                game->enemy_manager.search_path_for_golb(position);
            if (found) {
                ContactTargetObject* object = found->object;
                homing_target_object = object;
                if (!found->kind)
                    object->list_flags |= BOD_FLAG_SUPPRESS_CONTACT;
                Vec3* homing_target = &this->homing_target;
                *homing_target = found->position;
                homing_blend = 0.0f;
                homing_blend_step = 0.033333335f;
            }
            break;
        }
        case 1: {
            lifetime = 0.0f;
            lifetime_step = game->subgame_rate * 0.041666668f;
            vapour_owner_shot = this;

            BodNode* node = &vapour;
            BodNode* anchor = &g_game->subgame.golb_vapour_list_head;
            if ((vapour.list_flags & BOD_FLAG_LINKED) != 0) {
                report_errorf("List ADDafter");
            } else {
                vapour.list_prev = anchor;
                vapour.list_next = anchor->list_next;
                anchor->list_next = node;
                if (vapour.list_next)
                    vapour.list_next->list_prev = node;
                vapour.list_flags |= BOD_FLAG_LINKED;
            }

            vapour.ReSet((float*)spawn_selector);
            vapour.color.store_color4f(1.0f, 1.0f, 1.0f, 0.99000001f);
            this->shot_slot_index = shot_slot_index;
            vapour.Add(flight_transform);
            ((BodAiDispatch*)&vapour)->update_bod_ai();
            break;
        }
        case 0: {
            lifetime = 0.0f;
            lifetime_step = game->subgame_rate * 0.041666668f;
            render_sprite = g_sprite_manager.New(
                owner_player->player_slot,
                130,
                -1,
                -1);
            render_sprite->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
            render_sprite->progress = 0.0f;
            render_sprite->progress_step = 0.0f;
            render_sprite->gravity_step = 0.0f;

            tColour color;
            render_sprite->color =
                *color.Set(1.0f, 1.0f, 1.0f, 1.0f);
            render_sprite->size_start = 0.49000001f;
            render_sprite->size_end = 0.49000001f;
            Vec3* sprite_position = (Vec3*)&render_sprite->position;
            *sprite_position = *position;
            render_sprite->facing_angle =
                ((float)next_math_random_value() - 16384.0f)
                * 0.0000610351562f * 3.1415927f;
            render_sprite->facing_angle_step =
                game->subgame_rate * 0.58177644f;
            this->shot_slot_index = shot_slot_index;
            break;
        }
    }

    if (owner_player->follow_state.active == 1
        && owner_player->follow_state.vertical_offset < 0.5f) {
        path_follow.active = 1;
        path_follow.template_record = owner_player->follow_state.template_record;
        path_follow.source_cell = owner_player->follow_state.source_cell;
        path_follow.sample_index = owner_player->follow_state.sample_index;
        path_follow.progress = owner_player->follow_state.progress;
        path_follow.vertical_offset = 0.0f;
        path_follow.output_position = owner_player->follow_state.output_position;
        path_follow.shot = this;
        path_entry_z_latch = owner_player->follow_state.output_position.z;
    } else {
        path_follow.active = 0;
        path_entry_z_latch = -1.0f;
    }

    path_factor = velocity.Magnitude();
    Vec3* previous_output = &previous_flight_transform.position;
    *previous_output = *position;

    ((BodAiDispatch*)this)->update_bod_ai();
}
