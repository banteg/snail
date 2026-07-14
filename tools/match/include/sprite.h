// Sprite runtime structures, partial.
// iOS RSprite.o names these owners cRSprite and cRSpriteManager.
// Layout is cross-checked by initialize_sprite, update_sprite, texture helpers,
// allocate_sprite, kill_sprite, kill_game_sprites, draw_sprite_quad,
// update_sprite_facing_angle, and exact allocation callers.
#ifndef SPRITE_H
#define SPRITE_H

#include "render_scene.h"
#include "vector3.h"

struct TgaImageView;

enum {
    SPRITE_POOL_CAPACITY = 3000,
    SPRITE_ACTIVE_LIST_COUNT = 5,
    SPRITE_TEXTURE_CAPACITY = 1000,
    SPRITE_DEPTH_BUCKET_COUNT = 256,
};

// Authored four-float colour owner. Android retains this class and its
// Set/Alpha/Grey/White/Black family with the same RGBA field order.
struct tColour {
    tColour* noop_this_constructor();
    tColour* set_color_rgba(float r, float g, float b, float a); // @ 0x44db60; Set
    void store_color4f(float r, float g, float b, float a); // @ 0x44dbb0; constructor role
    void set_color_rgb(float r, float g, float b); // @ 0x44dbd0; Set
    void set_color_alpha(float alpha); // @ 0x44db80; Alpha
    void set_color_grayscale(float intensity); // @ 0x44db90; Grey
    void set_color_white(); // @ 0x44dc50; White
    void set_color_black(); // @ 0x44dc60; Black

    float r; // +0x00
    float g; // +0x04
    float b; // +0x08
    float a; // +0x0c
};

typedef char tColour_must_be_0x10[(sizeof(tColour) == 0x10) ? 1 : -1];

// Windows counterpart of the symbol-preserving iOS `GTempColour` owner.
extern tColour g_temp_colour; // data_503308

// Authored packed-colour owner. Android's symbol-preserving build names this
// class `tColourSmall` and independently proves the same Windows BGRA byte
// order through operator=(tColour const&) and G0SetColour.
struct tColourSmall {
    tColourSmall* noop_this_constructor();
    tColourSmall* pack_color_rgba_u8(tColour* color); // @ 0x44dbf0; tColourSmall::operator=

    unsigned char b; // +0x00
    unsigned char g; // +0x01
    unsigned char r; // +0x02
    unsigned char a; // +0x03
};

typedef char tColourSmall_must_be_0x04[
    (sizeof(tColourSmall) == 0x04) ? 1 : -1];

enum TextureRefFlags {
    TEXTURE_REF_RETAIN_SOURCE_BYTES = 0x20,
    TEXTURE_REF_REGISTERED = 0x400,
    TEXTURE_REF_DISABLE_PATH_REUSE = 0x800,
    TEXTURE_REF_WRAP_ADDRESSING = 0x1000,
    TEXTURE_REF_ANIMATED = 0x2000,
    TEXTURE_REF_ANIMATION_PING_PONG = 0x4000,
    TEXTURE_REF_SKIP_RUNTIME_LOAD = 0x8000,
    TEXTURE_REF_HAS_ALPHA = 0x10000,
};

enum SpriteFlag {
    SPRITE_FLAG_ACTIVE = 0x0001, // live active-list member
    SPRITE_FLAG_ORIENT_TO_MOTION = 0x0002, // renderer updates facing from motion
    SPRITE_FLAG_SKIP_INITIAL_PROGRESS = 0x0008, // consumed by first update
    SPRITE_FLAG_RENDER_ENABLED = 0x0040, // renderer visibility gate
    SPRITE_FLAG_PRESERVE_AT_PROGRESS_END = 0x0100, // do not kill at progress bound
    SPRITE_FLAG_DELAYED_RENDER = 0x0200, // lifetime delay still active
    SPRITE_FLAG_THROTTLE_FACING_REFRESH = 0x0400, // use refresh cadence pair
    SPRITE_FLAG_GAMEPLAY_OWNED = 0x0800, // paused and bulk-killed with gameplay
    SPRITE_FLAG_FORCE_OPAQUE = 0x1000, // draw alpha as 1.0
    SPRITE_FLAG_ANIMATED = 0x2000, // advance texture frames
    SPRITE_FLAG_ANIMATION_PING_PONG = 0x4000, // reverse frame step at bounds
};

struct TextureRef {
    unsigned int flags; // +0x00
    int loaded_width; // +0x04, filled by load_registered_texture_ref
    int loaded_height; // +0x08, filled by load_registered_texture_ref
    char name[0x8c - 0x0c]; // +0x0c, inline path/name used by kill_sprite error path
    int slot_index;         // +0x8c, texture-list slot id
    int frame_count;        // +0x90
    float frame_progress_step; // +0x94
    void* texture_ref;      // +0x98, caller payload or retained source bytes
    char unknown_9c[0xa0 - 0x9c];
    int mip_levels;         // +0xa0, initialized to 1 by get_or_create_texture_ref
};

typedef char TextureRef_must_be_0xa4[
    (sizeof(TextureRef) == 0xa4) ? 1 : -1];

class TextureRefList {
public:
    int initialize_texture_list(int capacity); // @ 0x44e800
    TextureRef* get_or_create_texture_ref(char* texture_path, int arg3, int flags); // @ 0x44e810

    int count;             // +0x00
    int capacity;          // +0x04
    TextureRef entries[1]; // +0x08, variable-capacity backing store
};

class Sprite {
public:
    void initialize_sprite(); // @ 0x44de90
    void update_sprite();     // @ 0x44df30
    void kill_sprite();       // @ 0x44e200
    void update_sprite_facing_angle(const TransformMatrix* matrix); // @ 0x44e410
    TextureRef* set_sprite_texture_ref(int texture_id, int frame); // @ 0x44e550

    void* object_ref; // +0x00, initialized to sentinel -1
    unsigned int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    int render_bucket_index; // +0x14, cached by render_game_frame depth sort
    float render_depth_key; // +0x18, cached by render_game_frame depth sort
    TextureRef* texture_ref; // +0x1c
    TextureRef* texture_ref_a; // +0x20
    TextureRef* texture_ref_b; // +0x24
    int draw_mode; // +0x28
    tColour color; // +0x2c
    Vector3 previous_position; // +0x3c
    Vector3 position; // +0x48
    Vector3 velocity; // +0x54
    float size_start; // +0x60, interpolated size at progress 0
    float size_end; // +0x64, interpolated size at progress 1
    float progress; // +0x68
    float progress_step; // +0x6c
    float lifetime; // +0x70
    float lifetime_step; // +0x74
    float gravity_step; // +0x78
    float facing_angle; // +0x7c
    float facing_angle_step; // +0x80
    int reserved_84; // +0x84, initialized to zero; no covered reader yet
    float corner_scale; // +0x88
    float facing_refresh_progress; // +0x8c
    float facing_refresh_step; // +0x90
    float depth_offset; // +0x94
    float depth_bias; // +0x98, added to projected sprite depth before bucketing
    int texture_id; // +0x9c
    int frame_count; // +0xa0
    int frame; // +0xa4
    int frame_step; // +0xa8
    float frame_progress; // +0xac
    float frame_progress_step; // +0xb0
};

typedef char Sprite_must_be_0xb4[
    (sizeof(Sprite) == 0xb4) ? 1 : -1];

int configure_sprite_render_state(Sprite* sprite); // @ 0x413670

// Per-frame depth-sort workspace owned by the sprite renderer. The node pool
// mirrors the manager's fixed sprite capacity; the bucket table covers every
// clamped 8-bit depth index.
struct SpriteDepthNode {
    SpriteDepthNode* next; // +0x00
    Vector3 position;      // +0x04, projected camera-space position
    float depth_key;       // +0x10
    Sprite* sprite;        // +0x14, borrowed live sprite
};

typedef char SpriteDepthNode_must_be_0x18[
    (sizeof(SpriteDepthNode) == 0x18) ? 1 : -1];

class SpriteManager {
public:
    void initialize_sprite_manager(); // @ 0x44e160
    TextureRef* register_sprite_texture(char* texture_path, int texture_id, int flags); // @ 0x44e0f0
    Sprite* allocate_sprite(int owner, int texture_id, int texture_a, int texture_b); // @ 0x44e2a0
    void kill_game_sprites(); // @ 0x44e3d0
    char set_sprite_manager_paused(char paused_); // @ 0x44e540
    TextureRef* get_sprite_texture(int texture_id); // @ 0x44e570
    TgaImageView* get_sprite_tga(int texture_id); // @ 0x44e580, iOS/Android GetTga

    unsigned char paused; // +0x00000
    char unknown_00001[0x04 - 0x01];
    Sprite sprites[SPRITE_POOL_CAPACITY]; // +0x00004
    Sprite* active_heads[SPRITE_ACTIVE_LIST_COUNT]; // +0x83d64
    Sprite* free_head; // +0x83d78
};

typedef char SpriteManager_must_be_0x83d7c[
    (sizeof(SpriteManager) == 0x83d7c) ? 1 : -1];

extern TextureRef* g_sprite_texture_table[SPRITE_TEXTURE_CAPACITY]; // data_78ff90
extern TextureRefList g_texture_refs;        // data_4b7790
extern SpriteManager g_sprite_manager;       // data_790f30
extern Sprite* g_sprite_active_heads[SPRITE_ACTIVE_LIST_COUNT]; // data_814c94
extern Sprite* g_sprite_free_head;           // data_814ca8
extern Sprite g_sprite_sentinel;             // data_814cb0
extern SpriteDepthNode g_sprite_depth_nodes[SPRITE_POOL_CAPACITY]; // data_4e5510
extern SpriteDepthNode* g_sprite_depth_buckets[SPRITE_DEPTH_BUCKET_COUNT]; // data_4f7050

#endif
