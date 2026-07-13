// create_golb @ 0x415280 (thiscall, ret 0xc)
// cRSubGolb::Create(cRSubGoldy*, int, int): link a projectile slot, seed its
// spawn position and velocity from Goldy's movement flag family, then install
// the sprite, vapour, or path-search presentation path used by update_golb_ai.

#include "bod_ai_dispatch.h"
#include "golb.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "vapour.h"
#include "vector3.h"

typedef unsigned int DWORD;

typedef Vector3 Vec3;

extern char* g_game_base; // data_4df904

void __fastcall set_matrix_identity(void* transform);
int report_errorf(char* format, ...);
int next_math_random_value();

void GolbShot::create_golb(Player* player_, int spawn_selector, int emitter_index)
{
    char* self = (char*)this;
    DWORD* words = (DWORD*)self;

    self[0x1bc] = 0;
    self[0x1bd] = 0;

    BodNode* body = &primary_body;
    if ((body->list_flags & 0x200) != 0) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = (BodNode**)(g_game_base + 0x5ac);
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
        body->list_flags |= 0x200;
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

    set_matrix_identity(&source_matrix);
    state = 1;

    Vec3* position = &this->position;
    char* player = (char*)owner_player;
    Vec3* player_position = (Vec3*)(player + 0x68);
    position->x = player_position->x;
    position->y = player_position->y;
    position->z = player_position->z;
    position->x = *(float*)(player + 0x58) * 0.5f + position->x;
    position->y = *(float*)(player + 0x5c) * 0.5f + position->y;
    position->z = *(float*)(player + 0x60) * 0.5f + position->z;

    DWORD movement_flags = *(DWORD*)(player + 0x338);
    if ((movement_flags & 5) == 0) {
        if ((movement_flags & 2) != 0) {
            if (spawn_selector == 2) {
                Vec3* source = (Vec3*)(player + 0x4134);
                position->x = source->x;
                position->y = source->y;
                position->z = source->z;
                position->x += 0.5f;
            } else if (spawn_selector == 1) {
                Vec3* source = (Vec3*)(player + 0x414c);
                position->x = source->x;
                position->y = source->y;
                position->z = source->z;
                position->x -= 0.5f;
            }
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = *(float*)(player + 0x418) + 1.0f;
        } else if ((movement_flags & 0x18) != 0) {
            Vec3* source;
            if (spawn_selector == 2)
                source = (Vec3*)(player + 0x417c);
            else
                source = (Vec3*)(player + 0x4188);
            position->x = source->x;
            position->y = source->y;
            position->z = source->z;
            if (*(float*)(player + 0x60) > 0.0f)
                spawn_selector = (int)(player + 0x4184);
            else
                spawn_selector = 0;
            self[0x1bc] = 1;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = *(float*)(player + 0x418) + 1.0f;
        } else if ((movement_flags & 0x60) != 0) {
            Vec3* source = (Vec3*)(player + 0x41ac);
            position->x = source->x;
            position->y = source->y;
            position->z = source->z;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = *(float*)(player + 0x418) + 0.60000002f;
        } else if ((movement_flags & 0x29) != 0) {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = *(float*)(player + 0x418) + 1.0f;
        } else if ((movement_flags & 0x52) != 0) {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = *(float*)(player + 0x418) + 1.0f;
            if (spawn_selector == 2)
                position->x += 0.5f;
            else
                position->x -= 0.5f;
        }
    } else {
        Vec3* source;
        if (spawn_selector == 3) {
            source = (Vec3*)(player + 0x4134);
            goto copy_movement_flag_source;
        }
        if (spawn_selector == 2) {
            source = (Vec3*)(player + 0x414c);
            goto copy_movement_flag_source;
        }
        if (spawn_selector == 1) {
            source = (Vec3*)(player + 0x4164);
            goto copy_movement_flag_source;
        }
        goto after_movement_flag_source;

copy_movement_flag_source:
        position->x = source->x;
        position->y = source->y;
        position->z = source->z;

after_movement_flag_source:

        if ((*(unsigned char*)(player + 0x338) & 4) != 0) {
            if (spawn_selector == 3) {
                velocity.x = 0.1f;
                velocity.y = 0.0f;
                velocity.z = *(float*)(player + 0x418) + 1.0f;
                position->x += 0.5f;
            } else if (spawn_selector == 2) {
                velocity.x = -0.1f;
                velocity.y = 0.0f;
                velocity.z = *(float*)(player + 0x418) + 1.0f;
                position->x -= 0.5f;
            } else {
                velocity.x = 0.0f;
                velocity.y = 0.0f;
                velocity.z = *(float*)(player + 0x418) + 1.0f;
            }
        } else {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            velocity.z = *(float*)(player + 0x418) + 1.0f;
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
                lifetime_step = *(float*)((char*)game + 0x38) * 0.027777776f;
                words[106] = (DWORD)self;
                spin = 0.0f;
                spin_step = 0.20943952f;
                homing_target_object = 0;

                char* node = self + 0x118;
                DWORD* node_words = (DWORD*)node;
                if ((node_words[1] & 0x200) != 0) {
                    report_errorf("List ADD");
                } else {
                    char* anchor = g_game_base + 0x5ac;
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
                    node_words[1] |= 0x200;
                }

                this->emitter_index = emitter_index;
                ContactTargetEntry* found =
                    game->enemy_manager.search_path_for_golb(position);
                if (found) {
                    homing_target_object = found->object;
                    if (!found->kind)
                        found->object->list_flags |= 0x1000;
                    Vec3* homing_target = (Vec3*)(self + 0x19c);
                    *homing_target = found->position;
                    homing_blend = 0.0f;
                    homing_blend_step = 0.033333335f;
                }
            }
        } else {
            lifetime = 0.0f;
            words[69] = (DWORD)self;
            lifetime_step = *(float*)((char*)game + 0x38) * 0.041666668f;

            char* node = self + 0x80;
            char* anchor = g_game_base + 0x3ca33c;
            if ((words[33] & 0x200) != 0) {
                report_errorf("List ADDafter");
            } else {
                words[34] = (DWORD)anchor;
                words[35] = *(DWORD*)(anchor + 12);
                *(DWORD*)(anchor + 12) = (DWORD)node;
                if (words[35])
                    *(DWORD*)(words[35] + 8) = (DWORD)node;
                words[33] |= 0x200;
            }

            ((Vapour*)(self + 0x80))->reset_vapour((float*)spawn_selector);
            ((Color4f*)(self + 0xa8))->store_color4f(1.0f, 1.0f, 1.0f, 0.99000001f);
            this->emitter_index = emitter_index;
            ((Vapour*)(self + 0x80))->add_vapour_point((TransformMatrix*)(self + 0x1c4));
            ((Vapour*)node)->update_vapour();
        }
    } else {
        lifetime = 0.0f;
        lifetime_step = *(float*)((char*)game + 0x38) * 0.041666668f;
        Sprite* sprite = g_sprite_manager.allocate_sprite(
            owner_player->player_slot,
            130,
            -1,
            -1);
        render_body_owner = sprite;
        sprite->flags |= 0x800;
        sprite->progress = 0.0f;
        sprite->progress_step = 0.0f;
        sprite->gravity_step = 0.0f;

        Color4f color;
        sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        sprite->size_start = 0.49000001f;
        sprite->size_end = 0.49000001f;
        Vec3* sprite_position = (Vec3*)&sprite->position;
        *sprite_position = *position;
        sprite->facing_angle = ((float)next_math_random_value() - 16384.0f) * 0.0001917476f;
        sprite->facing_angle_step = *(float*)((char*)game + 0x38) * 0.58177644f;
        this->emitter_index = emitter_index;
    }

    if (owner_player->follow_active == 1 && owner_player->follow_vertical_offset < 0.5f) {
        path_follow.active = 1;
        path_follow.template_record = (GolbPathTemplate*)owner_player->follow_template;
        path_follow.source_cell = (GolbPathSourceCell*)owner_player->follow_source_cell;
        path_follow.sample_index = owner_player->follow_sample_index;
        path_follow.progress = owner_player->follow_progress;
        path_follow.vertical_offset = 0.0f;
        path_follow.output_position = owner_player->follow_output_position;
        path_follow.shot = this;
        path_entry_z_latch = owner_player->follow_output_position.z;
    } else {
        path_follow.active = 0;
        path_entry_z_latch = -1.0f;
    }

    path_factor = velocity.vector_magnitude();
    Vec3* previous_output = &this->previous_output;
    *previous_output = *position;

    ((BodAiDispatch*)self)->update_bod_ai();
}
