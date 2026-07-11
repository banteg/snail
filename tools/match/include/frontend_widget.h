// Windows cRBorder/front-end widget view, partial. Cross-checked by hide/unhide,
// highlight, stack-layout, shortcut, warning, score, tip, and row-event paths.
#ifndef FRONTEND_WIDGET_H
#define FRONTEND_WIDGET_H

#include "sprite.h"
#include "tooltip_state.h"

class FrontendWidget {
public:
    void draw_frontend_widget(); // @ 0x401130
    int hide_border_init(); // @ 0x4010e0
    int unhide_border_init(); // @ 0x401110
    int highlight_border(); // @ 0x402800
    int unhighlight_border(); // @ 0x4027e0
    FrontendWidget* stack_widget_below(FrontendWidget* previous_widget); // @ 0x4027b0
    int layout_frontend_widget(); // @ 0x4024a0
    int set_frontend_widget_shortcut_key(int shortcut_key_code); // @ 0x402790
    FrontendWidget* border_input_text_init(int arg2, char* text, int flags); // @ 0x403410
    void border_input_text(); // @ 0x4035b0
    void border_add_text_number(int value); // @ 0x401030
    int border_sprite_extend(int sprite_a, int sprite_c, int sprite_b, char flag); // @ 0x404540
    unsigned char border_mouse_test(); // @ 0x404580, iOS cRBorder::MouseTest()
    void update_frontend_widget_interaction(); // @ 0x402820
    int initialize_frontend_widget(int flags, char* text, int widget_type,
        float x, float y, Color4f* color, int alignment, float anchor_x);
    void initialize_frontend_sprite_button(int flags, int sprite, float x, float y,
        Color4f* color, float z, int layer);

    unsigned int list_kind; // +0x00
    unsigned int list_flags; // +0x04
    FrontendWidget* list_prev; // +0x08
    FrontendWidget* list_next; // +0x0c
    int widget_type; // +0x10
    char unknown_014[0x44 - 0x014];
    float hide_blend; // +0x44
    char unknown_048[0x4c - 0x048];
    float frame_x; // +0x4c
    float frame_y; // +0x50
    float frame_width; // +0x54
    float frame_height; // +0x58
    unsigned char texture_hit_test_enabled; // +0x05c
    char unknown_05d[0x64 - 0x05d];
    int texture_hit_test_sprite; // +0x064
    char unknown_068[0x178 - 0x068];
    int warning_field; // +0x178
    float slider_value; // +0x17c
    float slider_target_value; // +0x180
    char unknown_184[0x194 - 0x184]; // slider child pointer / hit-bound overlay
    int shortcut_key_code; // +0x194
    char unknown_198[0x1a0 - 0x198];
    unsigned int widget_flags; // +0x1a0
    char unknown_1a4[0x1ec - 0x1a4];
    Color4f idle_text_color; // +0x1ec
    char unknown_1fc[0x208 - 0x1fc];
    float warning_overlay_alpha; // +0x208
    float hover_blend_target; // +0x20c
    float hover_blend_current; // +0x210
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
    float active_padding; // +0x220
    float text_effect_target; // +0x224
    float text_effect_current; // +0x228
    float border_edge_shrink; // +0x22c
    float border_edge; // +0x230
    unsigned char compact_border; // +0x234
    char unknown_235[0x238 - 0x235];
    float layout_x; // +0x238
    float layout_y; // +0x23c
    float texture_hit_x; // +0x240
    float texture_hit_y; // +0x244
    float layout_width; // +0x248
    float layout_height; // +0x24c
    float texture_hit_width; // +0x250
    float texture_hit_height; // +0x254
    char unknown_258[0x25c - 0x258];
    int layout_mode; // +0x25c
    float layout_center_x; // +0x260
    char unknown_264[0x26c - 0x264];
    float stack_gap; // +0x26c
    char unknown_270[0x28c - 0x270];
    TooltipState tooltip; // +0x28c
    char text_buffer[0x420]; // +0x2cc
    int font_id; // +0x6ec
    float font_scale; // +0x6f0
    float layout_anchor_x; // +0x6f4
    float layout_anchor_y; // +0x6f8
    char unknown_6fc[0x718 - 0x6fc];
    FrontendWidget* child_widget_0; // +0x718
    FrontendWidget* child_widget_1; // +0x71c
    FrontendWidget* child_widget_2; // +0x720
};

#endif
