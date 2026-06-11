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

    float magnitude(); // vector_magnitude @ image, thiscall, returns st0
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
    GolbPathSample* search_path_for_golb(const Vector3* position); // @ 0x415e30

    int count;                  // +0x00
    GolbPathSample samples[1];  // +0x04
};

// path template fields touched by initialize_path_follow_golb; the real
// PathTemplate layout lives in analysis/headers, only two fields matter here
struct GolbPathTemplate {
    char unknown_00[0x18];
    float base_z;    // +0x18
    char unknown_1c[0x38 - 0x1c];
    int sample_count; // +0x38
};

class GolbPathFollowState {
public:
    int initialize_path_follow_golb(
        GolbPathTemplate* path, const Vector3* position, int search_slot); // @ 0x421770

    unsigned char active;     // +0x00
    char unknown_01[3];
    int sample_count;         // +0x04, copy of path->sample_count
    GolbPathTemplate* path;   // +0x08
    float progress;           // +0x0c
    float offset_z;           // +0x10, position.z - path->base_z
    float offset_y;           // +0x14, position.y - 0.49f
    char unknown_18[0x24 - 0x18];
    int search_slot;          // +0x24
};

#endif
