#ifndef BN_GARBAGE_HAZARD_TYPES_H
#define BN_GARBAGE_HAZARD_TYPES_H

/*
 * Narrow Binary Ninja type-import slice for the garbage hazard and sprite
 * runtime surface recovered through the matching scratches.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Player Player;
typedef struct SubgameRuntime SubgameRuntime;
typedef struct TextureRef TextureRef;
typedef struct TrackRowCell TrackRowCell;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

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

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
    tColour color;
} BodBase;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    void* render_animation_manager;
    uint8_t unknown_7c[0x4];
} RenderableBod;

typedef struct BodList {
    int32_t unknown_00;
    BodNode* first;
    BodNode* free_top;
} BodList;

typedef enum SpriteFlag {
    SPRITE_FLAG_ACTIVE = 0x0001,
    SPRITE_FLAG_ORIENT_TO_MOTION = 0x0002,
    SPRITE_FLAG_SKIP_INITIAL_PROGRESS = 0x0008,
    SPRITE_FLAG_RENDER_ENABLED = 0x0040,
    SPRITE_FLAG_PRESERVE_AT_PROGRESS_END = 0x0100,
    SPRITE_FLAG_DELAYED_RENDER = 0x0200,
    SPRITE_FLAG_THROTTLE_FACING_REFRESH = 0x0400,
    SPRITE_FLAG_GAMEPLAY_OWNED = 0x0800,
    SPRITE_FLAG_FORCE_OPAQUE = 0x1000,
    SPRITE_FLAG_ANIMATED = 0x2000,
    SPRITE_FLAG_ANIMATION_PING_PONG = 0x4000,
} SpriteFlag;

typedef struct Sprite Sprite;
struct Sprite {
    void* object_ref;
    SpriteFlag flags;
    int32_t owner;
    Sprite* next;
    Sprite* prev;
    int32_t render_bucket_index;
    float render_depth_key;
    TextureRef* texture_ref;
    TextureRef* texture_ref_a;
    TextureRef* texture_ref_b;
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

typedef struct SubGarbage SubGarbage;
typedef enum SubGarbageState {
    SUB_GARBAGE_STATE_INACTIVE = 0,
    SUB_GARBAGE_STATE_ACTIVE = 1,
    SUB_GARBAGE_STATE_BURST_PENDING = 2,
    SUB_GARBAGE_STATE_BURST = 3,
} SubGarbageState;

typedef enum SubGarbageCollisionSide {
    SUB_GARBAGE_COLLISION_SIDE_RIGHT = 1,
    SUB_GARBAGE_COLLISION_SIDE_LEFT = 2,
} SubGarbageCollisionSide;

enum {
    SUB_GARBAGE_SLOT_CAPACITY = 50,
};

struct SubGarbage {
    RenderableBod body;
    SubGarbage* next_active;
    SubGarbageState state;
    SubGarbageCollisionSide collision_side;
    SubgameRuntime* owner_game;
    Vec3 velocity;
    float radius;
    float attachment_facing_angle;
    int32_t unknown_a4;
    float burst_rate_step;
    float smoke_timer;
    float smoke_timer_step;
    Sprite* sprite;
    TrackRowCell* source_cell;
    uint8_t hidden;
    uint8_t unknown_bd[0x3];
    Player* owner_player;
};

typedef SubGarbage GarbageHazardSlot;

typedef struct SubGarbagePool {
    SubGarbage* active_head;
    SubGarbage slots[SUB_GARBAGE_SLOT_CAPACITY];
} SubGarbagePool;

typedef SubGarbagePool GarbageHazardPool;

/*
 * Analysis-only root-biased view retained by AddGarbage after multiplying the
 * slot index. The prefix aliases SubgameRuntime; garbage is one pool-owned
 * record, not separately allocated storage.
 */
typedef struct SubGarbageSlotCursor {
    uint8_t subgame_prefix[0x359144];
    SubGarbage garbage;
} SubGarbageSlotCursor;

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
TextureRef* __thiscall get_sprite_texture(SpriteManager* manager, int32_t texture_id);

SubGarbage* __thiscall initialize_garbage_hazard(SubGarbage* sub_garbage);
void __thiscall update_garbage_hazard(SubGarbage* sub_garbage);
SubGarbage* __thiscall destroy_garbage_hazard(SubGarbage* sub_garbage);
void __thiscall spawn_garbage_smoke_particle(
    SubGarbage* sub_garbage,
    Vec3* position,
    Vec3* velocity,
    Player* owner_player);
void __thiscall spawn_track_garbage_hazard(
    SubgameRuntime* game,
    TrackRowCell* cell,
    Player* player);

#endif
