// Frontend widget view, partial. Cross-checked by the border hide/unhide,
// highlight, stack-layout, shortcut, warning, score, tip, and row-event paths.
#ifndef FRONTEND_WIDGET_H
#define FRONTEND_WIDGET_H

#include "sprite.h"

class BorderRecord;

class TooltipState {
public:
    int reset_tooltip(); // @ 0x403be0

    int field_00; // +0x00
    int state; // +0x04
    char unknown_008[0x18 - 0x008];
    BorderRecord* tooltip_widget; // +0x18
    char unknown_01c[0x40 - 0x01c];
};

class FrontendWidget {
public:
    int hide_border_init(); // @ 0x4010e0
    int unhide_border_init(); // @ 0x401110
    int highlight_border(); // @ 0x402800
    int unhighlight_border(); // @ 0x4027e0
    FrontendWidget* stack_widget_below(FrontendWidget* previous_widget); // @ 0x4027b0
    FrontendWidget* layout_frontend_widget();
    int set_frontend_widget_shortcut_key(int shortcut_key_code); // @ 0x402790
    void border_add_text_number(int value); // @ 0x401030
    void initialize_frontend_widget(int flags, char* text, int widget_type,
        float x, float y, Color4f* color, int alignment, float anchor_x);
    void initialize_frontend_sprite_button(int flags, int sprite, float x, float y,
        Color4f* color, float z, int layer);

    char unknown_000[0x44];
    float hide_blend; // +0x44
    char unknown_048[0x4c - 0x048];
    float frame_x; // +0x4c
    float frame_y; // +0x50
    float frame_width; // +0x54
    float frame_height; // +0x58
    char unknown_05c[0x178 - 0x05c];
    int warning_field; // +0x178
    char unknown_17c[0x194 - 0x17c];
    int shortcut_key_code; // +0x194
    char unknown_198[0x1a0 - 0x198];
    unsigned int widget_flags; // +0x1a0
    char unknown_1a4[0x208 - 0x1a4];
    float warning_overlay_alpha; // +0x208
    float hover_blend_target; // +0x20c
    float hover_blend_current; // +0x210
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
    char unknown_220[0x238 - 0x220];
    float layout_x; // +0x238
    float layout_y; // +0x23c
    char unknown_240[0x248 - 0x240];
    float layout_width; // +0x248
    float layout_height; // +0x24c
    char unknown_250[0x25c - 0x250];
    int layout_mode; // +0x25c
    float layout_center_x; // +0x260
    char unknown_264[0x26c - 0x264];
    float stack_gap; // +0x26c
    char unknown_270[0x28c - 0x270];
    TooltipState tooltip; // +0x28c
    char text_buffer[2]; // +0x2cc
    char unknown_2ce[0x6f4 - 0x2ce];
    float layout_anchor_x; // +0x6f4
    float layout_anchor_y; // +0x6f8
};

#endif
