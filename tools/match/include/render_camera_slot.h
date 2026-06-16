#ifndef RENDER_CAMERA_SLOT_H
#define RENDER_CAMERA_SLOT_H

class RenderCameraSlot {
public:
    RenderCameraSlot* initialize_render_camera_slot(); // @ 0x44e920
    int attach_render_camera_source(void* source);     // @ 0x44e900

    int unknown_00;          // +0x00, left to the owning runtime constructor
    int sort_key;            // +0x04, used by render_game_frame ordering
    unsigned int flags;      // +0x08, bit 0 marks the slot active
    float viewport_x;        // +0x0c
    float viewport_y;        // +0x10
    float viewport_width;    // +0x14
    float viewport_height;   // +0x18
    float unknown_1c;        // +0x1c, initialized to 0.8725f
    void* source;            // +0x20, render_camera source object
    unsigned char draw_world; // +0x24, passed through render_game_frame
    char pad_25[0x28 - 0x25];
};

typedef char RenderCameraSlot_must_be_0x28[
    (sizeof(RenderCameraSlot) == 0x28) ? 1 : -1];

#endif
