// Golb (player shot) path-follow structures, partial.
// Offsets per analysis/decompile/*/00421770-*.c and 00415e30-*.c
#ifndef GOLB_H
#define GOLB_H

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    float vector_magnitude(); // @ 0x44ccf0, thiscall, returns st0
    void rotate_by_matrix(const float* matrix); // thiscall, matrix on stack
};

// stride 0x18 sample bank entry; only the position triple is typed so far
struct GolbPathSample {
    float unknown_00;
    float x; // +0x04
    float y; // +0x08
    float z; // +0x0c
    float unknown_10;
    float unknown_14;
};

class GolbPathBank {
public:
    void initialize_enemy_manager(); // @ 0x415e20
    GolbPathSample* search_path_for_golb(const Vector3* position); // @ 0x415e30

    int count;                  // +0x00
    GolbPathSample samples[1];  // +0x04
};

// Attachment path template fields touched by Golb path-follow helpers.
struct GolbPathTemplate {
    char unknown_00[0x38];
    int kind;          // +0x38
    char unknown_3c[0x44 - 0x3c];
    int sample_count;  // +0x44
    char unknown_48[0x50 - 0x48];
    float width_or_scale; // +0x50
    int width_cells;      // +0x54
    void* primary_samples;   // +0x58
    void* secondary_samples; // +0x5c
};

struct GolbPathSourceCell {
    char unknown_00[0x10];
    Vector3 anchor_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    GolbPathTemplate* path_template; // +0x38
};

class GolbPathFollowState {
public:
    int initialize_path_follow_golb(
        GolbPathSourceCell* source_cell,
        const Vector3* position,
        int search_slot); // @ 0x421770

    unsigned char active;     // +0x00
    char unknown_01[3];
    GolbPathTemplate* template_record; // +0x04
    GolbPathSourceCell* source_cell;   // +0x08
    int sample_index;          // +0x0c
    float progress;            // +0x10
    float vertical_offset;     // +0x14
    Vector3 output_position;   // +0x18
    int search_slot;          // +0x24
};

#endif
