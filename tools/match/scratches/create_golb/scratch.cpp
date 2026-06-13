// create_golb @ 0x415280 (thiscall, ret 0xc)
// cRSubGolb::Create(cRSubGoldy*, int, int): link a projectile slot, seed its
// spawn position and velocity from Goldy's movement flag family, then install
// the sprite, vapour, or path-search presentation path used by update_golb_ai.

typedef unsigned int DWORD;

struct Vec3 {
    float x;
    float y;
    float z;

    float vector_magnitude();
};

struct Color4f {
    Color4f* set_color_rgba(float r, float g, float b, float a);
    float store_color4f(float r, float g, float b, float a);

    float r;
    float g;
    float b;
    float a;
};

struct SpriteManager {
    void* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

struct GolbPathSampleBank {
    void* search_path_for_golb(Vec3* position);
};

struct VapourTrail {
    virtual int update_vapour();
    int reset_vapour(int mode);
};

class GolbShot {
public:
    virtual int create_dispatch();
    int create_golb(char* player, int spawn_selector, int emitter_index);
};

extern char* g_game_base; // data_4df904
extern SpriteManager g_sprite_manager; // data_790f30

void __fastcall set_matrix_identity(void* transform);
int report_errorf(char* format, ...);
int next_math_random_value();
void add_vapour_point(void* vapour, void* matrix);

int GolbShot::create_golb(char* player, int spawn_selector, int emitter_index)
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

    words[158] = (DWORD)player;
    DWORD kind_flags = *(DWORD*)(player + 0x338);
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
    Vec3* velocity = (Vec3*)(self + 0x24c);
    Vec3* player_position = (Vec3*)(player + 0x68);
    position->x = player_position->x;
    position->y = player_position->y;
    position->z = player_position->z;
    position->x = *(float*)(player + 0x58) * 0.5f + position->x;
    position->y = *(float*)(player + 0x5c) * 0.5f + position->y;
    position->z = *(float*)(player + 0x60) * 0.5f + position->z;

    DWORD movement_flags = *(DWORD*)(player + 0x338);
    if ((movement_flags & 5) != 0) {
        Vec3* source;
        switch (spawn_selector) {
        case 3:
            source = (Vec3*)(player + 0x4134);
            break;
        case 2:
            source = (Vec3*)(player + 0x414c);
            break;
        case 1:
            source = (Vec3*)(player + 0x4164);
            break;
        default:
            source = 0;
            break;
        }
        if (source) {
            position->x = source->x;
            position->y = source->y;
            position->z = source->z;
        }

        if ((*(unsigned char*)(player + 0x338) & 4) != 0) {
            if (spawn_selector == 3) {
                velocity->x = 0.1f;
                velocity->y = 0.0f;
                velocity->z = *(float*)(player + 0x418) + 1.0f;
                position->x += 0.5f;
            } else if (spawn_selector == 2) {
                velocity->x = -0.1f;
                velocity->y = 0.0f;
                velocity->z = *(float*)(player + 0x418) + 1.0f;
                position->x -= 0.5f;
            } else {
                velocity->x = 0.0f;
                velocity->y = 0.0f;
                velocity->z = *(float*)(player + 0x418) + 1.0f;
            }
        } else {
            velocity->x = 0.0f;
            velocity->y = 0.0f;
            velocity->z = *(float*)(player + 0x418) + 1.0f;
        }
    } else if ((movement_flags & 2) != 0) {
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
        velocity->x = 0.0f;
        velocity->y = 0.0f;
        velocity->z = *(float*)(player + 0x418) + 1.0f;
    } else if ((movement_flags & 0x18) != 0) {
        Vec3* source;
        if (spawn_selector == 2)
            source = (Vec3*)(player + 0x417c);
        else
            source = (Vec3*)(player + 0x4188);
        position->x = source->x;
        position->y = source->y;
        position->z = source->z;
        self[0x1bc] = 1;
        velocity->x = 0.0f;
        velocity->y = 0.0f;
        velocity->z = *(float*)(player + 0x418) + 1.0f;
    } else if ((movement_flags & 0x60) != 0) {
        Vec3* source = (Vec3*)(player + 0x41ac);
        position->x = source->x;
        position->y = source->y;
        position->z = source->z;
        velocity->x = 0.0f;
        velocity->y = 0.0f;
        velocity->z = *(float*)(player + 0x418) + 0.60000002f;
    } else if ((movement_flags & 0x29) != 0) {
        velocity->x = 0.0f;
        velocity->y = 0.0f;
        velocity->z = *(float*)(player + 0x418) + 1.0f;
    } else if ((movement_flags & 0x52) != 0) {
        velocity->x = 0.0f;
        velocity->y = 0.0f;
        velocity->z = *(float*)(player + 0x418) + 1.0f;
        if (spawn_selector == 2)
            position->x += 0.5f;
        else
            position->x -= 0.5f;
    }

    if (words[112] == 1) {
        velocity->x += velocity->x;
        velocity->y += velocity->y;
        velocity->z += velocity->z;
    }
    if (words[112] == 2) {
        velocity->x *= 0.80000001f;
        velocity->y *= 0.80000001f;
        velocity->z *= 0.80000001f;
    }

    Vec3* direction = (Vec3*)(self + 0x258);
    direction->x = velocity->x;
    direction->y = velocity->y;
    direction->z = velocity->z;

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
                if ((words[71] & 0x200) != 0) {
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
                        words[72] = 0;
                        *(DWORD*)(*(DWORD*)anchor + 12) = 0;
                    }
                    words[71] |= 0x200;
                }

                words[157] = emitter_index;
                void* found = ((GolbPathSampleBank*)(words[156] + 0x1270fd4))
                                  ->search_path_for_golb(position);
                if (found) {
                    DWORD* found_words = (DWORD*)found;
                    words[102] = found_words[5];
                    if (!found_words[0])
                        *(DWORD*)(found_words[5] + 4) |= 0x1000;
                    words[103] = found_words[1];
                    words[104] = found_words[2];
                    words[105] = found_words[3];
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
            add_vapour_point(self + 0x80, self + 0x1c4);
            ((VapourTrail*)node)->update_vapour();
        }
    } else {
        words[154] = 0;
        ((float*)self)[155] = *(float*)(words[156] + 0x38) * 0.041666668f;
        DWORD* sprite = (DWORD*)g_sprite_manager.allocate_sprite(
            *(DWORD*)(player + 0x380),
            130,
            -1,
            -1);
        words[146] = (DWORD)sprite;
        sprite[1] |= 0x800;
        *(DWORD*)((char*)sprite + 0x68) = 0;
        *(DWORD*)((char*)sprite + 0x6c) = 0;
        *(DWORD*)((char*)sprite + 0x78) = 0;

        Color4f color;
        Color4f* color_words = color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        DWORD* sprite_color = (DWORD*)((char*)sprite + 0x2c);
        sprite_color[0] = ((DWORD*)color_words)[0];
        sprite_color[1] = ((DWORD*)color_words)[1];
        sprite_color[2] = ((DWORD*)color_words)[2];
        sprite_color[3] = ((DWORD*)color_words)[3];
        *(DWORD*)((char*)sprite + 0x60) = 1056629064;
        *(DWORD*)((char*)sprite + 0x64) = 1056629064;
        Vec3* sprite_position = (Vec3*)((char*)sprite + 0x48);
        *sprite_position = *position;
        *(float*)((char*)sprite + 0x7c) =
            ((float)next_math_random_value() - 16384.0f) * 0.0001917476f;
        *(float*)((char*)sprite + 0x80) = *(float*)(words[156] + 0x38) * 0.58177644f;
        words[157] = emitter_index;
    }

    if (*(unsigned char*)(player + 0x384) == 1 && *(float*)(player + 0x398) < 0.5f) {
        self[0x2bc] = 1;
        words[176] = *(DWORD*)(player + 0x388);
        words[177] = *(DWORD*)(player + 0x38c);
        words[178] = *(DWORD*)(player + 0x390);
        words[179] = *(DWORD*)(player + 0x394);
        words[180] = 0;
        words[181] = *(DWORD*)(player + 0x3b0);
        words[182] = *(DWORD*)(player + 0x3b4);
        words[183] = *(DWORD*)(player + 0x3b8);
        words[184] = (DWORD)self;
        words[185] = *(DWORD*)(player + 0x3b8);
    } else {
        self[0x2bc] = 0;
        words[185] = 0xbf800000;
    }

    ((float*)self)[153] = velocity->vector_magnitude();
    Vec3* previous_output = (Vec3*)(self + 0x234);
    *previous_output = *position;

    return create_dispatch();
}
