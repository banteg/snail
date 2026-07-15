// Shared backdrop renderer state, partial.
#ifndef BACKDROP_H
#define BACKDROP_H

#include "bod_types.h"
#include "landscape_script.h"

struct BackdropDistortCell {
    float phase; // +0x00
    float phase_step; // +0x04
    float x_offset; // +0x08
    float y_offset; // +0x0c
    float current_x_offset; // +0x10
    float current_y_offset; // +0x14
};
typedef char BackdropDistortCell_must_be_0x18[
    (sizeof(BackdropDistortCell) == 0x18) ? 1 : -1];

struct BackdropWorldBlend {
    tColour color; // +0x00, constructed as a tColour at startup
    float blend; // +0x10
    float blend_step; // +0x14
    int previous_world; // +0x18
    int current_world; // +0x1c
};
typedef char BackdropWorldBlend_must_be_0x20[
    (sizeof(BackdropWorldBlend) == 0x20) ? 1 : -1];

class Backdrop : public BodBase {
public:
    void set_backdrop_zoom(float zoom); // @ 0x410c30, iOS cRBackdrop::SetZoom(float)
    void set_backdrop_distort(float distort); // @ 0x410c40, iOS/Android cRBackdrop::SetDistort(float)
    void change_backdrop(LandscapeScriptRecord* record, char flip); // @ 0x410d50
    void change_backdrop_real(); // @ 0x410dc0
    void initialize_backdrop(int last_mode); // @ 0x410e20
    void set_backdrop_world(int world); // @ 0x410f40, Android cRBackdrop::SetWorld(int)
    int draw_split_backdrop(); // @ 0x410f90
#ifdef BACKDROP_RENDER_BACKDROP_RETURNS_VOID
#define BACKDROP_RENDER_BACKDROP_RESULT void
#else
#define BACKDROP_RENDER_BACKDROP_RESULT int
#endif
    BACKDROP_RENDER_BACKDROP_RESULT render_backdrop(); // @ 0x411040
#undef BACKDROP_RENDER_BACKDROP_RESULT
    int update_backdrop(); // @ 0x4112f0

    unsigned char active_split_backdrop_pair; // +0x38
    unsigned char pending_split_backdrop_pair; // +0x39
    char unknown_03a[0x3c - 0x3a];
    int active_primary_texture_id; // +0x3c
    int pending_primary_texture_id; // +0x40
    int active_secondary_texture_id; // +0x44
    int pending_secondary_texture_id; // +0x48
    unsigned char backdrop_change_queued; // +0x4c
    char unknown_04d[0x50 - 0x4d];
    float pending_distort; // +0x50
    unsigned char pending_flip; // +0x54
    unsigned char active_flip; // +0x55
    char unknown_056[0x58 - 0x56];
    union {
        BackdropDistortCell distort_cells[64]; // +0x58, flat traversal view
        BackdropDistortCell distort_grid[8][8]; // +0x58, [row][column]
    };
    // Persistent 0/1 draw gate. update_backdrop decrements only a local copy
    // to test the authored `== 1` state; this field is not a countdown.
    int backdrop_render_enabled; // +0x658
    int unknown_65c; // +0x65c
    // cRClickStart::AI state 2 is the sole Windows reference and raises this
    // byte to one. The exact Backdrop owner is proven; no reader yet proves a
    // stronger semantic name.
    unsigned char unknown_660; // +0x660
    char unknown_661[0x664 - 0x661];
    float unknown_664; // +0x664
    float unknown_668; // +0x668
    float unknown_66c; // +0x66c
    float unknown_670; // +0x670
    float unknown_674; // +0x674
    float unknown_678; // +0x678
    BackdropWorldBlend primary_world_blend; // +0x67c
    BackdropWorldBlend secondary_world_blend; // +0x69c
    float unknown_6bc; // +0x6bc
    float unknown_6c0; // +0x6c0
    int unknown_6c4; // +0x6c4
    float zoom; // +0x6c8, normalized track progress on Windows
};

typedef char Backdrop_must_cover_0x6cc[(sizeof(Backdrop) == 0x6cc) ? 1 : -1];

#endif
