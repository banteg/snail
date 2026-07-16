// Exact 0x724-byte Windows cRBorder/front-end widget view. Cross-checked by
// allocation, both initializers, draw/update/layout, mouse, tooltip, warning,
// score, tip, and row-event paths.
#ifndef FRONTEND_WIDGET_H
#define FRONTEND_WIDGET_H

#include "bod_types.h"
#include "sprite.h"
#include "tooltip_state.h"
#include "twinkle_manager.h"

class InputOkState;

// Shared cRBorder state word. Only bits with independent producer/consumer
// evidence are named; the remaining interaction/style bits stay numeric.
enum FrontendWidgetFlag {
    FRONTEND_WIDGET_FLAG_HIGHLIGHTED = 0x00000002,
    FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED = 0x00000004,
    FRONTEND_WIDGET_FLAG_HOVER_TEXT_EFFECT_ENABLED = 0x00000008,
    FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED = 0x00000010,
    FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED = 0x00000020,
    FRONTEND_WIDGET_FLAG_SECONDARY_INPUT_ENABLED = 0x00000040,
    FRONTEND_WIDGET_FLAG_SECONDARY_ACTION_TRIGGERED = 0x00000080,
    FRONTEND_WIDGET_FLAG_KILL_PENDING = 0x00000200,
    FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE = 0x00000400,
    FRONTEND_WIDGET_FLAG_SPRITE_MODE = 0x00000800,
    FRONTEND_WIDGET_FLAG_HIDDEN = 0x00001000,
    FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE = 0x00002000,
    FRONTEND_WIDGET_FLAG_DISABLED = 0x00008000,
    FRONTEND_WIDGET_FLAG_POINTER_INSIDE = 0x00020000,
    FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE = 0x00040000,
    FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED = 0x00080000,
    FRONTEND_WIDGET_FLAG_SLIDER = 0x00100000,
    FRONTEND_WIDGET_FLAG_FRAMELESS = 0x00400000,
    FRONTEND_WIDGET_FLAG_SUPPRESS_ACTION_SOUND = 0x00800000,
    FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION = 0x01000000,
    FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED = 0x08000000,
    FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION = 0x40000000,
};

// Semantic cRBorder view over BorderRecord storage. The exact record
// constructor initializes the inherited BodBase; widget-specific semantics
// begin at +0x38.
class FrontendWidget : public BodBase {
public:
    void draw_frontend_widget(); // @ 0x401130, iOS/Android cRBorder::Draw()
    void hide_border_init(); // @ 0x4010e0, Android cRBorder::HideInit()
    void unhide_border_init(); // @ 0x401110, Android cRBorder::UnHideInit()
    void highlight_border(); // @ 0x402800, Android cRBorder::Highlight()
    void unhighlight_border(); // @ 0x4027e0, Android cRBorder::UnHighlight()
    void stack_widget_below(FrontendWidget* previous_widget); // @ 0x4027b0,
        // Android cRBorder::SetBelow(cRBorder*)
    void layout_frontend_widget(); // @ 0x4024a0,
        // Android cRBorder::RePosition()
    void set_frontend_widget_shortcut_key(int shortcut_key_code); // @ 0x402790,
        // Android cRBorder::SetKeyLeft(int)
    void border_input_text_init(int capacity, char* text, int flags); // @ 0x403410,
        // Android cRBorder::InputTextInit(int, char*, int)
    void border_input_text(); // @ 0x4035b0, iOS/Android cRBorder::InputText()
    void border_add_text_number(int value); // @ 0x401030
    void border_sprite_extend(int sprite_a, int sprite_c, int sprite_b,
        char flag); // @ 0x404540, Android cRBorder::SpriteExtend(int, int, int, bool)
    unsigned char border_mouse_test(); // @ 0x404580, iOS cRBorder::MouseTest()
    void update_frontend_widget_interaction(); // @ 0x402820,
        // iOS/Android cRBorder::AI()
    void initialize_frontend_widget(int flags, char* text, int widget_type,
        float x, float y, tColour* color, int alignment, float anchor_x);
    void initialize_frontend_sprite_button(int flags, int sprite, float x, float y,
        tColour* color, float z, int layer);
    InputOkState* input_ok_state();

    char unknown_038[0x44 - 0x38];
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
    union {
        unsigned char texture_hit_test_enabled;
        unsigned char sprite_extend_enabled;
    }; // +0x05c
    unsigned char sprite_wobble_positive; // +0x05d, false mirrors the delayed wobble
    char unknown_05e[0x60 - 0x05e];
    union {
        int background_texture_id;
        int sprite_hot_texture_id;
    }; // +0x060
    union {
        int texture_hit_test_sprite;
        int sprite_hit_mask_texture_id;
    }; // +0x064
    int sprite_extend_texture_c; // +0x068, stored by border_sprite_extend
    char unknown_06c[0x7c - 0x06c];
    int widget_type; // +0x7c, border style/font preset
    TwinkleManager twinkle_manager; // +0x080, five inline twinkles and manager state
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
    unsigned int widget_flags; // +0x1a0, FrontendWidgetFlag word
    unsigned int previous_widget_flags; // +0x1a4
    char unknown_1a8[0x1ac - 0x1a8];
    tColour current_fill_color; // +0x1ac
    tColour idle_fill_color; // +0x1bc
    tColour hot_fill_color; // +0x1cc
    tColour current_text_color; // +0x1dc
    tColour idle_text_color; // +0x1ec
    tColour hot_text_color; // +0x1fc; warning animation drives its alpha lane
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
    int input_cursor; // +0x6fc, index of the visible editing marker
    int input_cursor_visible; // +0x700, toggled by the blink timer
    float input_cursor_blink_progress; // +0x704
    float input_cursor_blink_step; // +0x708
    unsigned int input_flags; // +0x70c, filter and OK-button placement modes
    int input_length; // +0x710, text length excluding the editing marker
    int input_capacity; // +0x714
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

inline InputOkState* FrontendWidget::input_ok_state()
{
    // Text-input widgets reuse the tooltip tail as an InputOkState. Its
    // source/OK pointers land at the tooltip's final two pointer lanes.
    return (InputOkState*)((char*)&tooltip + 0x1c);
}

#endif
