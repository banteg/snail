#ifndef BN_BACKDROP_TYPES_H
#define BN_BACKDROP_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct BackdropDistortCell {
    float phase;
    float phase_step;
    float x_offset;
    float y_offset;
    float current_x_offset;
    float current_y_offset;
} BackdropDistortCell;

typedef struct BackdropWorldBlend {
    tColour color;
    float blend;
    float blend_step;
    int32_t previous_world;
    int32_t current_world;
} BackdropWorldBlend;

typedef struct LandscapeScriptRecord {
    int32_t id;
    char name[0x84 - 0x04];
    int32_t backdrop_texture_id;
    uint8_t split_backdrop_texture_pair;
    char backdrop_texture_path[0x10c - 0x89];
    int32_t object_index;
    tColour fog_color;
    float distort;
} LandscapeScriptRecord;

typedef struct Backdrop {
    uint8_t bod_base[0x38];
    uint8_t active_split_backdrop_pair;
    uint8_t pending_split_backdrop_pair;
    uint8_t _pad_03a[0x3c - 0x3a];
    int32_t active_primary_texture_id;
    int32_t pending_primary_texture_id;
    int32_t active_secondary_texture_id;
    int32_t pending_secondary_texture_id;
    uint8_t backdrop_change_queued;
    uint8_t _pad_04d[0x50 - 0x4d];
    float pending_distort;
    uint8_t pending_flip;
    uint8_t active_flip;
    uint8_t _pad_056[0x58 - 0x56];
    BackdropDistortCell distort_grid[8][8];
    int32_t backdrop_render_enabled;
    int32_t unknown_65c;
    uint8_t unknown_660;
    uint8_t _pad_661[0x664 - 0x661];
    float unknown_664;
    float unknown_668;
    float unknown_66c;
    float unknown_670;
    float unknown_674;
    float unknown_678;
    BackdropWorldBlend primary_world_blend;
    BackdropWorldBlend secondary_world_blend;
    float unknown_6bc;
    float unknown_6c0;
    int32_t unknown_6c4;
    float zoom;
} Backdrop;

void __thiscall set_backdrop_progress_fraction(Backdrop* backdrop, float zoom);
void __thiscall set_backdrop_distort(Backdrop* backdrop, float distort);
void __thiscall change_backdrop(
    Backdrop* backdrop, LandscapeScriptRecord* record, uint8_t flip);
void __thiscall change_backdrop_real(Backdrop* backdrop);
void __thiscall initialize_backdrop(Backdrop* backdrop, int32_t last_mode);
void __thiscall set_backdrop_texture_target(Backdrop* backdrop, int32_t world);

#endif
