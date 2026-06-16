// Sprite runtime structures, partial.
// Layout is cross-checked by initialize_sprite, update_sprite, texture helpers,
// allocate_sprite, kill_sprite, kill_game_sprites, draw_sprite_quad,
// update_sprite_facing_angle, and exact allocation callers.
#ifndef SPRITE_H
#define SPRITE_H

#include "vector3.h"

struct Color4f {
    Color4f* noop_this_constructor();
    Color4f* set_color_rgba(float r, float g, float b, float a); // @ 0x44db60
    Color4f* store_color4f(float r, float g, float b, float a);   // @ 0x44dbb0
    int store_color4f(int r_bits, int g_bits, int b_bits, int a_bits); // raw-bit callsite view
    int set_color_alpha(int alpha_bits);                         // @ 0x44db80, raw-bit alpha
    void set_color_grayscale(float intensity);                    // @ 0x44db90
    void set_color_white();                                      // @ 0x44dc50
    void set_color_black();                                      // @ 0x44dc60

    float r; // +0x00
    float g; // +0x04
    float b; // +0x08
    float a; // +0x0c
};

struct TextureRef {
    unsigned int flags; // +0x00
    char unknown_04[0x0c - 0x04];
    char name[0x8c - 0x0c]; // +0x0c, inline path/name used by kill_sprite error path
    int slot_index;         // +0x8c, texture-list slot id
    int frame_count;        // +0x90
    float frame_progress_step; // +0x94
    void* texture_ref;      // +0x98
    char unknown_9c[0xa0 - 0x9c];
    int unknown_a0;         // +0xa0, initialized to 1 by get_or_create_texture_ref
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
    int unknown_14; // +0x14
    int unknown_18; // +0x18
    TextureRef* texture_ref; // +0x1c
    TextureRef* texture_ref_a; // +0x20
    TextureRef* texture_ref_b; // +0x24
    int draw_mode; // +0x28
    Color4f color; // +0x2c
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
    int unknown_84; // +0x84
    float corner_scale; // +0x88
    float facing_refresh_progress; // +0x8c
    float facing_refresh_step; // +0x90
    float depth_offset; // +0x94
    int unknown_98; // +0x98
    int texture_id; // +0x9c
    int frame_count; // +0xa0
    int frame; // +0xa4
    int frame_step; // +0xa8
    float frame_progress; // +0xac
    float frame_progress_step; // +0xb0
};

class SpriteManager {
public:
    void initialize_sprite_manager(); // @ 0x44e160
    Sprite* allocate_sprite(int owner, int texture_id, int texture_a, int texture_b); // @ 0x44e2a0
    void kill_game_sprites(); // @ 0x44e3d0
    char set_sprite_manager_paused(char paused_); // @ 0x44e540

    unsigned char paused; // +0x00000
    char unknown_00001[0x04 - 0x01];
    Sprite sprites[3000]; // +0x00004
    Sprite* active_heads[5]; // +0x83d64
    Sprite* free_head; // +0x83d78
};

extern TextureRef* g_sprite_texture_table[]; // data_78ff90
extern TextureRefList g_texture_refs;        // data_4b7790
extern SpriteManager g_sprite_manager;       // data_790f30
extern Sprite* g_sprite_active_heads[5];     // data_814c94
extern Sprite* g_sprite_free_head;           // data_814ca8
extern Sprite g_sprite_sentinel;             // data_814cb0

#endif
