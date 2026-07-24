#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "bod_types.h"
#include "render_scene.h"

// iOS names this camera owner cRCamera. Windows embeds one in each GamePlayer
// and lends it to a Viewport; the viewport does not own it.
class RenderCamera : public RenderableBod {
public:
    TransformMatrix view_matrix; // +0x80, sprite depth/facing transform
    float fov_degrees; // +0xc0, passed through to render_camera
    union {
        unsigned int render_mask; // +0xc4, authored camera scene mask
        float overlay_rotation_angle; // embedded Overlay camera reuses this lane
    };
};

typedef char RenderCamera_must_cover_0xc8[
    (sizeof(RenderCamera) == 0xc8) ? 1 : -1];

// Android and iOS retain the original cRViewport class name for this owner.
// Windows constructs five consecutive records at GameRoot +0x5b4.
class Viewport {
public:
    Viewport* initialize_render_camera_slot(); // @ 0x44e920, cRViewport::cRViewport
    int attach_render_camera_source(RenderCamera* camera); // @ 0x44e900, SetCamera

    int unknown_00;          // +0x00, left to the owning runtime constructor
    int sort_key;            // +0x04, used by render_game_frame ordering
    unsigned int flags;      // +0x08, bit 0 marks the viewport active
    float viewport_x;        // +0x0c
    float viewport_y;        // +0x10
    float viewport_width;    // +0x14
    float viewport_height;   // +0x18
    float unknown_1c;        // +0x1c, initialized to 0.8725f
    RenderCamera* camera;    // +0x20, borrowed embedded GameRoot camera
    unsigned char draw_world; // +0x24, passed through render_game_frame
    char pad_25[0x28 - 0x25];
};

typedef char Viewport_must_be_0x28[(sizeof(Viewport) == 0x28) ? 1 : -1];

TransformMatrix* render_camera(
    float viewport_x,
    float viewport_y,
    float viewport_width,
    float viewport_height,
    float fov_degrees,
    TransformMatrix* camera_matrix,
    TransformMatrix* view_matrix,
    char draw_world,
    char post_sprite_pass); // @ 0x411fa0

#endif
