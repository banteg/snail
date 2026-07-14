#ifndef BN_GARBAGE_HAZARD_TYPES_H
#define BN_GARBAGE_HAZARD_TYPES_H

/*
 * Narrow Binary Ninja type-import slice for the garbage hazard and sprite
 * runtime surface recovered through the matching scratches.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct TransformMatrix TransformMatrix;
typedef struct SubgameRuntime SubgameRuntime;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct BodNode BodNode;
struct BodNode {
    void* vtable;
    uint32_t list_flags;
    BodNode* list_prev;
    BodNode* list_next;
};

typedef struct BodList {
    int32_t unknown_00;
    BodNode* first;
    BodNode* free_top;
} BodList;

typedef struct Sprite Sprite;
struct Sprite {
    void* object_ref;
    uint32_t flags;
    int32_t owner;
    Sprite* next;
    Sprite* prev;
    int32_t render_bucket_index;
    float render_depth_key;
    struct TextureRef* texture_ref;
    struct TextureRef* texture_ref_a;
    struct TextureRef* texture_ref_b;
    int32_t draw_mode;
    tColour color;
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
    uint8_t _pad_01[0x3];
    Sprite sprites[3000];
    Sprite* active_heads[5];
    Sprite* free_head;
} SpriteManager;

typedef struct GarbageHazardSlot GarbageHazardSlot;
enum SubGarbageState {
    SUB_GARBAGE_STATE_INACTIVE = 0,
    SUB_GARBAGE_STATE_ACTIVE = 1,
    SUB_GARBAGE_STATE_BURST_PENDING = 2,
    SUB_GARBAGE_STATE_BURST = 3,
};

enum SubGarbageCollisionSide {
    SUB_GARBAGE_COLLISION_SIDE_RIGHT = 1,
    SUB_GARBAGE_COLLISION_SIDE_LEFT = 2,
};

enum {
    SUB_GARBAGE_SLOT_CAPACITY = 50,
};

struct GarbageHazardSlot {
    void* vtable;
    uint32_t list_flags;
    GarbageHazardSlot* list_prev;
    GarbageHazardSlot* list_next;
    Vec3 bod_position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 world_position;
    float world_position_w;
    void* render_animation_manager;
    uint8_t unknown_7c[0x4];
    GarbageHazardSlot* next_active;
    int32_t state;
    int32_t collision_side;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float radius;
    float attachment_facing_angle;
    int32_t unknown_a4;
    float burst_rate_step;
    float smoke_timer;
    float smoke_timer_step;
    Sprite* sprite;
    struct TrackRowCell* source_cell;
    uint8_t hidden;
    uint8_t unknown_bd[0x3];
    struct Player* owner_player;
};

typedef struct GarbageHazardPool {
    GarbageHazardSlot* active_head;
    GarbageHazardSlot slots[SUB_GARBAGE_SLOT_CAPACITY];
} GarbageHazardPool;

void __thiscall initialize_sprite_manager(SpriteManager* manager);
Sprite* __thiscall allocate_sprite(
    SpriteManager* manager,
    int32_t owner,
    int32_t texture_id,
    int32_t texture_a,
    int32_t texture_b);
void __thiscall initialize_sprite(Sprite* sprite);
void __thiscall update_sprite(Sprite* sprite);
void __thiscall kill_sprite(Sprite* sprite);
void __thiscall kill_game_sprites(SpriteManager* manager);
void __thiscall update_sprite_facing_angle(Sprite* sprite, const TransformMatrix* matrix);
uint8_t __thiscall set_sprite_manager_paused(SpriteManager* manager, uint8_t paused);
struct TextureRef* __thiscall get_sprite_texture(SpriteManager* manager, int32_t texture_id);

GarbageHazardSlot* __thiscall initialize_garbage_hazard(GarbageHazardSlot* slot);
void __thiscall update_garbage_hazard(GarbageHazardSlot* slot);
GarbageHazardSlot* __thiscall destroy_garbage_hazard(GarbageHazardSlot* slot);
void __thiscall spawn_garbage_smoke_particle(
    GarbageHazardSlot* slot,
    Vec3* position,
    Vec3* velocity,
    struct Player* owner_player);
void __thiscall spawn_track_garbage_hazard(
    SubgameRuntime* game,
    struct TrackRowCell* cell,
    struct Player* player);

#endif
