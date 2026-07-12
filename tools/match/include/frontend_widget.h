// Exact 0x724-byte Windows cRBorder/front-end widget view. Cross-checked by
// allocation, both initializers, draw/update/layout, mouse, tooltip, warning,
// score, tip, and row-event paths.
#ifndef FRONTEND_WIDGET_H
#define FRONTEND_WIDGET_H

#include "sprite.h"
#include "tooltip_state.h"

// Semantic cRBorder view over BorderRecord storage. Its first 0x10 bytes are
// the exact BodNode intrusive-list prefix; later front-end fields deliberately
// overlay generic BodBase lanes whose gameplay names do not apply here.
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

    unsigned int list_kind; // +0x00, BodNode::list_kind view
    unsigned int list_flags; // +0x04, BodNode::list_flags view
    FrontendWidget* list_prev; // +0x08, BodNode::list_prev view
    FrontendWidget* list_next; // +0x0c, BodNode::list_next view
    char unknown_010[0x44 - 0x10];
    float hide_blend; // +0x44
    int border_texture_id; // +0x48, nine-slice frame texture
    union {
        float frame_x;
        float authored_left;
    }; // +0x4c
    union {
        float frame_y;
        float authored_top;
    }; // +0x50
    union {
        float frame_width;
        float authored_width;
    }; // +0x54
    union {
        float frame_height;
        float authored_height;
    }; // +0x58
    unsigned char texture_hit_test_enabled; // +0x05c
    char unknown_05d[0x60 - 0x05d];
    int background_texture_id; // +0x060
    int texture_hit_test_sprite; // +0x064
    char unknown_068[0x7c - 0x068];
    int widget_type; // +0x7c, border style/font preset
    char unknown_080[0x178 - 0x080];
    float sprite_shadow_offset; // +0x178, optional second sprite draw offset
    union {
        float slider_value;
        float slider_position_target;
    }; // +0x17c
    union {
        float slider_target_value;
        float slider_position_current;
    }; // +0x180
    float slider_hit_left; // +0x184
    float slider_hit_right; // +0x188
    float slider_hit_top; // +0x18c
    float slider_hit_bottom; // +0x190
    int shortcut_key_code; // +0x194
    char unknown_198[0x1a0 - 0x198];
    unsigned int widget_flags; // +0x1a0
    unsigned int previous_widget_flags; // +0x1a4
    char unknown_1a8[0x1ac - 0x1a8];
    Color4f current_fill_color; // +0x1ac
    Color4f idle_fill_color; // +0x1bc
    Color4f hot_fill_color; // +0x1cc
    Color4f current_text_color; // +0x1dc
    Color4f idle_text_color; // +0x1ec
    Color4f hot_text_color; // +0x1fc; warning animation drives its alpha lane
    float hover_blend_target; // +0x20c
    float hover_blend_current; // +0x210
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
    union {
        float current_padding;
        float active_padding;
    }; // +0x220
    float text_effect_target; // +0x224
    float text_effect_current; // +0x228
    float render_inset_delta; // +0x22c
    float render_inset_base; // +0x230
    unsigned char render_inset_dynamic; // +0x234
    char unknown_235[0x238 - 0x235];
    union {
        float layout_x;
        float layout_left;
    }; // +0x238
    union {
        float layout_y;
        float layout_top;
    }; // +0x23c
    float texture_hit_x; // +0x240
    float texture_hit_y; // +0x244
    float layout_width; // +0x248
    float layout_height; // +0x24c
    float texture_hit_width; // +0x250
    float texture_hit_height; // +0x254
    float border_edge; // +0x258, symmetric sprite extent expansion
    union {
        int layout_mode;
        int text_alignment;
    }; // +0x25c
    union {
        float layout_center_x;
        float anchor_x;
    }; // +0x260
    float teardown_progress; // +0x264, advanced while widget flag 0x400 is set
    float teardown_progress_step; // +0x268
    float stack_gap; // +0x26c
    int texture_id; // +0x270, sprite button texture
    int texture_layer; // +0x274
    int mouse_history_warmup_frames; // +0x278, suppresses initial movement edge
    float previous_mouse_x; // +0x27c
    float previous_mouse_y; // +0x280
    char unknown_284[0x28c - 0x284];
    FrontendWidgetTooltip tooltip; // +0x28c, authored cRToolTip owner
    char text_buffer[0x420]; // +0x2cc
    int font_id; // +0x6ec
    float font_scale; // +0x6f0
    float layout_anchor_x; // +0x6f4
    float layout_anchor_y; // +0x6f8
    char unknown_6fc[0x718 - 0x6fc];
    union {
        FrontendWidget* child_widget_0;
        FrontendWidget* slider_less_widget;
    }; // +0x718
    union {
        FrontendWidget* child_widget_1;
        FrontendWidget* slider_more_widget;
    }; // +0x71c
    union {
        FrontendWidget* child_widget_2;
        FrontendWidget* slider_value_widget;
    }; // +0x720
};

typedef char FrontendWidget_must_be_0x724[
    (sizeof(FrontendWidget) == 0x724) ? 1 : -1];

#endif
