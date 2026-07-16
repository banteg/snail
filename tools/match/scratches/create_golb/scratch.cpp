// create_golb @ 0x415280 (thiscall, ret 0xc)
// cRSubGolb::Create(cRSubGoldy*, int, int): link a projectile slot, seed its
// spawn position and velocity from Goldy's movement flag family, then install
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

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);
int next_math_random_value();

void GolbShot::create_golb(Player* player_, int spawn_selector, int emitter_index)
{
    skip_one_tick = 0;
    slug_bounce_armed = 0;

    BodNode* body = &primary_body;
    if ((body->list_flags & BOD_FLAG_LINKED) != 0) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* old_first = *first_ref;
        if (old_first) {
            old_first->list_prev = body;
            BodNode* current = *first_ref;
            BodNode* inserted = current->list_prev;
            inserted->list_next = current;
            current = *first_ref;
            *first_ref = current->list_prev;
            (*first_ref)->list_prev = 0;
        } else {
            *first_ref = body;
            body->list_prev = 0;
            (*first_ref)->list_next = 0;
        }
        body->list_flags |= BOD_FLAG_LINKED;
    }

    owner_player = player_;
    DWORD kind_flags = player_->movement_flags;
    if ((kind_flags & 7) != 0) {
        kind = 0;
    } else if ((kind_flags & 0x18) != 0) {
        kind = 1;
    } else if ((kind_flags & 0x60) != 0) {
        kind = 2;
    }

    source_matrix.set_matrix_identity();
    state = 1;

    Vec3* position = &flight_transform.position;
    Player* player = owner_player;
    Vec3* player_position = &player->transform.position;
    position->x = player_position->x;
    position->y = player_position->y;
    position->z = player_position->z;
    position->x = player->transform.basis_forward.x * 0.5f + position->x;
    position->y = player->transform.basis_forward.y * 0.5f + position->y;
    position->z = player->transform.basis_forward.z * 0.5f + position->z;

    DWORD movement_flags = player->movement_flags;
    if ((movement_flags & 5) == 0) {
        if ((movement_flags & 2) != 0) {
            if (spawn_selector == 2) {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_BLASTER_LEFT_FIRE];
                position->x = source->x;
                position->y = source->y;
                position->z = source->z;
                position->x += 0.5f;
            } else if (spawn_selector == 1) {
                Vec3* source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_BLASTER_RIGHT_FIRE];
                position->x = source->x;
                position->y = source->y;
                position->z = source->z;
                position->x -= 0.5f;
            }
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = player->velocity.z + 1.0f;
        } else if ((movement_flags & 0x18) != 0) {
            Vec3* source;
            if (spawn_selector == 2)
                source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_LASER_LEFT];
            else
                source = &player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_LASER_RIGHT];
            position->x = source->x;
            position->y = source->y;
            position->z = source->z;
            if (player->transform.basis_forward.z > 0.0f)
                spawn_selector = (int)&player->presentation.snail_hotspots_world[
                    SNAIL_HOTSPOT_LASER_LEFT].z;
            else
                spawn_selector = 0;
            skip_one_tick = 1;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = player->velocity.z + 1.0f;
        } else if ((movement_flags & 0x60) != 0) {
            Vec3* source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_ROCKET_BASE];
            position->x = source->x;
            position->y = source->y;
            position->z = source->z;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = player->velocity.z + 0.60000002f;
        } else if ((movement_flags & 0x29) != 0) {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = player->velocity.z + 1.0f;
        } else if ((movement_flags & 0x52) != 0) {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = player->velocity.z + 1.0f;
            if (spawn_selector == 2)
                position->x += 0.5f;
            else
                position->x -= 0.5f;
        }
    } else {
        Vec3* source;
        if (spawn_selector == 3) {
            source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_BLASTER_LEFT_FIRE];
            goto copy_movement_flag_source;
        }
        if (spawn_selector == 2) {
            source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_BLASTER_RIGHT_FIRE];
            goto copy_movement_flag_source;
        }
        if (spawn_selector == 1) {
            source = &player->presentation.snail_hotspots_world[
                SNAIL_HOTSPOT_BLASTER_TOP_FIRE];
            goto copy_movement_flag_source;
        }
        goto after_movement_flag_source;

copy_movement_flag_source:
        position->x = source->x;
        position->y = source->y;
        position->z = source->z;

after_movement_flag_source:

        if ((player->movement_flags & 4) != 0) {
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

    Vec3* direction = &this->direction;
    Vec3* movement = &velocity;
    direction->x = movement->x;
    direction->y = movement->y;
    direction->z = movement->z;

    if (kind) {
        int adjusted_kind = kind - 1;
        if (adjusted_kind) {
            if (adjusted_kind == 1) {
                lifetime = 0.0f;
                lifetime_step = game->subgame_rate * 0.027777776f;
                rocket_owner_shot = this;
                spin = 0.0f;
                spin_step = 0.20943952f;
                homing_target_object = 0;

                char* node = (char*)&tertiary_body;
                DWORD* node_words = (DWORD*)node;
                if ((node_words[1] & BOD_FLAG_LINKED) != 0) {
                    report_errorf("List ADD");
                } else {
                    char* anchor = (char*)&g_game->active_bod_list.first;
                    int head = *(int*)anchor;
                    if (head) {
                        *(DWORD*)(head + 8) = (DWORD)node;
                        *(DWORD*)(*(DWORD*)(*(DWORD*)anchor + 8) + 12) = *(DWORD*)anchor;
                        int next = *(DWORD*)(*(DWORD*)anchor + 8);
                        *(DWORD*)anchor = next;
                        *(DWORD*)(next + 8) = 0;
                    } else {
                        *(DWORD*)anchor = (DWORD)node;
                        node_words[2] = 0;
                        *(DWORD*)(*(DWORD*)anchor + 12) = 0;
                    }
                    node_words[1] |= BOD_FLAG_LINKED;
                }

                this->emitter_index = emitter_index;
                ContactTargetEntry* found =
                    game->enemy_manager.search_path_for_golb(position);
                if (found) {
                    homing_target_object = found->object;
                    if (!found->kind)
                        found->object->list_flags |= BOD_FLAG_SUPPRESS_CONTACT;
                    Vec3* homing_target = &this->homing_target;
                    *homing_target = found->position;
                    homing_blend = 0.0f;
                    homing_blend_step = 0.033333335f;
                }
            }
        } else {
            lifetime = 0.0f;
            vapour_owner_shot = this;
            lifetime_step = game->subgame_rate * 0.041666668f;

            BodNode* node = &secondary_body;
            BodNode* anchor = &g_game->subgame.golb_vapour_list_head;
            if ((secondary_body.list_flags & BOD_FLAG_LINKED) != 0) {
                report_errorf("List ADDafter");
            } else {
                secondary_body.list_prev = anchor;
                secondary_body.list_next = anchor->list_next;
                anchor->list_next = node;
                if (secondary_body.list_next)
                    secondary_body.list_next->list_prev = node;
                secondary_body.list_flags |= BOD_FLAG_LINKED;
            }

            vapour.reset_vapour((float*)spawn_selector);
            secondary_body.color.store_color4f(1.0f, 1.0f, 1.0f, 0.99000001f);
            this->emitter_index = emitter_index;
            vapour.add_vapour_point(&flight_transform);
            vapour.update_vapour();
        }
    } else {
        lifetime = 0.0f;
        lifetime_step = game->subgame_rate * 0.041666668f;
        Sprite* sprite = g_sprite_manager.allocate_sprite(
            owner_player->player_slot,
            130,
            -1,
            -1);
        render_sprite = sprite;
        sprite->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
        sprite->progress = 0.0f;
        sprite->progress_step = 0.0f;
        sprite->gravity_step = 0.0f;

        tColour color;
        sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        sprite->size_start = 0.49000001f;
        sprite->size_end = 0.49000001f;
        Vec3* sprite_position = (Vec3*)&sprite->position;
        *sprite_position = *position;
        sprite->facing_angle = ((float)next_math_random_value() - 16384.0f) * 0.0001917476f;
        sprite->facing_angle_step = game->subgame_rate * 0.58177644f;
        this->emitter_index = emitter_index;
    }

    if (owner_player->follow_state.active == 1 && owner_player->follow_state.vertical_offset < 0.5f) {
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

    path_factor = velocity.vector_magnitude();
    Vec3* previous_output = &previous_flight_transform.position;
    *previous_output = *position;

    ((BodAiDispatch*)&primary_body)->update_bod_ai();
}
