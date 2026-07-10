// create_golb @ 0x415280 (thiscall, ret 0xc)
// cRSubGolb::Create(cRSubGoldy*, int, int): link a projectile slot, seed its
// spawn position and velocity from Goldy's movement flag family, then install
// the sprite, vapour, or path-search presentation path used by update_golb_ai.

#include "golb.h"
#include "sprite.h"
#include "vapour_trail.h"
#include "vector3.h"

typedef unsigned int DWORD;

typedef Vector3 Vec3;

class GolbShotPrimaryBodyView {
public:
    virtual int create_dispatch();
};

extern char* g_game_base; // data_4df904

void __fastcall set_matrix_identity(void* transform);
int report_errorf(char* format, ...);
int next_math_random_value();

int GolbShot::create_golb(Player* player_, int spawn_selector, int emitter_index)
{
    char* self = (char*)this;
    DWORD* words = (DWORD*)self;

    self[0x1bc] = 0;
    self[0x1bd] = 0;

    if ((words[1] & 0x200) != 0) {
        report_errorf("List ADD");
    } else {
        char* anchor = g_game_base + 0x5ac;
        int head = *(int*)anchor;
        if (head) {
            *(DWORD*)(head + 8) = (DWORD)self;
            *(DWORD*)(*(DWORD*)(*(DWORD*)anchor + 8) + 12) = *(DWORD*)anchor;
            int next = *(DWORD*)(*(DWORD*)anchor + 8);
            *(DWORD*)anchor = next;
            *(DWORD*)(next + 8) = 0;
        } else {
            *(DWORD*)anchor = (DWORD)self;
            words[2] = 0;
            *(DWORD*)(*(DWORD*)anchor + 12) = 0;
        }
        words[1] |= 0x200;
    }

    words[158] = (DWORD)player_;
    DWORD kind_flags = player_->movement_flags;
    if ((kind_flags & 7) != 0) {
        words[112] = 0;
    } else if ((kind_flags & 0x18) != 0) {
        words[112] = 1;
    } else if ((kind_flags & 0x60) != 0) {
        words[112] = 2;
    }

    set_matrix_identity(self + 0x27c);
    words[145] = 1;

    Vec3* position = (Vec3*)(self + 0x1f4);
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

    if (words[112] == 1) {
        velocity.x += velocity.x;
        velocity.y += velocity.y;
        velocity.z += velocity.z;
    }
    if (words[112] == 2) {
        velocity.x *= 0.80000001f;
        velocity.y *= 0.80000001f;
        velocity.z *= 0.80000001f;
    }

    Vec3* direction = (Vec3*)(self + 0x258);
    Vec3* movement = &velocity;
    direction->x = movement->x;
    direction->y = movement->y;
    direction->z = movement->z;

    if (words[112]) {
        int adjusted_kind = words[112] - 1;
        if (adjusted_kind) {
            if (adjusted_kind == 1) {
                words[154] = 0;
                ((float*)self)[155] = *(float*)(words[156] + 0x38) * 0.027777776f;
                words[106] = (DWORD)self;
                words[109] = 0;
                words[110] = 1045854032;
                words[102] = 0;

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

                words[157] = emitter_index;
                GolbPathSample* found = ((GolbPathBank*)(words[156] + 0x1270fd4))
                                          ->search_path_for_golb(position);
                if (found) {
                    DWORD* found_words = (DWORD*)found;
                    words[102] = found_words[5];
                    if (!found_words[0])
                        *(DWORD*)(found_words[5] + 4) |= 0x1000;
                    Vec3* homing_target = (Vec3*)(self + 0x19c);
                    Vec3* found_position = (Vec3*)(found_words + 1);
                    *homing_target = *found_position;
                    words[107] = 0;
                    words[108] = 1023969417;
                }
            }
        } else {
            words[154] = 0;
            words[69] = (DWORD)self;
            ((float*)self)[155] = *(float*)(words[156] + 0x38) * 0.041666668f;

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

            ((VapourTrail*)(self + 0x80))->reset_vapour(spawn_selector);
            ((Color4f*)(self + 0xa8))->store_color4f(1.0f, 1.0f, 1.0f, 0.99000001f);
            words[157] = emitter_index;
            ((VapourTrail*)(self + 0x80))->add_vapour_point((TransformMatrix*)(self + 0x1c4));
            ((VapourTrail*)node)->update_vapour();
        }
    } else {
        words[154] = 0;
        ((float*)self)[155] = *(float*)(words[156] + 0x38) * 0.041666668f;
        Sprite* sprite = g_sprite_manager.allocate_sprite(
            owner_player->player_slot,
            130,
            -1,
            -1);
        words[146] = (DWORD)sprite;
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
        sprite->facing_angle_step = *(float*)(words[156] + 0x38) * 0.58177644f;
        words[157] = emitter_index;
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

    ((float*)self)[153] = velocity.vector_magnitude();
    Vec3* previous_output = (Vec3*)(self + 0x234);
    *previous_output = *position;

    return ((GolbShotPrimaryBodyView*)self)->create_dispatch();
}
