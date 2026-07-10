#ifndef RENDER_CAMERA_SLOT_H
#define RENDER_CAMERA_SLOT_H

#include "transform_matrix.h"

// iOS names this render-camera owner cRCamera. Windows embeds camera instances
// in GameRoot and lends them to RenderCameraSlot; the slot does not own them.
class RenderCamera {
public:
    char unknown_00[0x38];
    TransformMatrix camera_matrix; // +0x38, world camera transform
    char unknown_78[0x80 - 0x78];
    TransformMatrix view_matrix; // +0x80, sprite depth/facing transform
    int camera_mode; // +0xc0, passed through to render_camera
    unsigned int render_mask; // +0xc4, high byte selects compatible slots
};

typedef char RenderCamera_must_cover_0xc8[
    (sizeof(RenderCamera) == 0xc8) ? 1 : -1];

class RenderCameraSlot {
public:
    RenderCameraSlot* initialize_render_camera_slot(); // @ 0x44e920
    int attach_render_camera_source(RenderCamera* source); // @ 0x44e900

    int unknown_00;          // +0x00, left to the owning runtime constructor
    int sort_key;            // +0x04, used by render_game_frame ordering
    unsigned int flags;      // +0x08, bit 0 marks the slot active
    float viewport_x;        // +0x0c
    float viewport_y;        // +0x10
    float viewport_width;    // +0x14
    float viewport_height;   // +0x18
    float unknown_1c;        // +0x1c, initialized to 0.8725f
    RenderCamera* source;    // +0x20, borrowed embedded GameRoot camera
    unsigned char draw_world; // +0x24, passed through render_game_frame
    char pad_25[0x28 - 0x25];
};

typedef char RenderCameraSlot_must_be_0x28[
    (sizeof(RenderCameraSlot) == 0x28) ? 1 : -1];

#endif
