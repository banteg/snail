#ifndef STAR_MANAGER_TYPES_H
#define STAR_MANAGER_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the Windows star-field pass.
 * iOS symbols name the concrete class cRStarManager. The 0x38-byte prefix is
 * the same BodBase constructed at GameRoot+0x4f33c before the callback table
 * is installed; the remaining fields are proved by the seven lifecycle and
 * update functions at 0x434270..0x434800.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct TransformMatrix TransformMatrix;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef struct BodNode {
    void* vtable;
    uint32_t list_flags;
    struct BodNode* list_prev;
    struct BodNode* list_next;
} BodNode;

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    Color4f color;
} BodBase;

typedef struct TextureRef {
    uint32_t flags;
    int32_t loaded_width;
    int32_t loaded_height;
    char name[0x80];
    int32_t slot_index;
    int32_t frame_count;
    float frame_progress_step;
    void* texture_ref;
    uint8_t unknown_9c[0x4];
    int32_t mip_levels;
} TextureRef;
typedef struct Sprite Sprite;
struct Sprite {
    void* object_ref;
    uint32_t flags;
    int32_t owner;
    Sprite* next;
    Sprite* prev;
    int32_t render_bucket_index;
    float render_depth_key;
    TextureRef* texture_ref;
    TextureRef* texture_ref_a;
    TextureRef* texture_ref_b;
    int32_t draw_mode;
    Color4f color;
    Vec3 previous_position;
    Vec3 position;
    Vec3 velocity;
    float size_start;
    float size_end;
    float progress;
    float progress_step;
    float lifetime;
    float lifetime_step;
    float gravity_step;
    float facing_angle;
    float facing_angle_step;
    int32_t reserved_84;
    float corner_scale;
    float facing_refresh_progress;
    float facing_refresh_step;
    float depth_offset;
    float depth_bias;
    int32_t texture_id;
    int32_t frame_count;
    int32_t frame;
    int32_t frame_step;
    float frame_progress;
    float frame_progress_step;
};

typedef struct SpriteManager {
    uint8_t paused;
    uint8_t unknown_01[0x3];
    Sprite sprites[3000];
    Sprite* active_heads[5];
    Sprite* free_head;
} SpriteManager;

typedef struct StarManagerEntry {
    int32_t active;
    Vec3 position;
    Vec3 velocity;
    Sprite* sprite;
    float speed;
    float travel_distance;
    float alpha_scale;
} StarManagerEntry;

typedef struct StarManager {
    BodBase bod;
    int32_t state;
    StarManagerEntry* entries;
    int32_t count;
    float fade;
    float fade_step;
} StarManager;

#endif
