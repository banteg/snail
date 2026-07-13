#ifndef COMPLETION_SCREEN_TYPES_H
#define COMPLETION_SCREEN_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct TwinkleManager {
    uint8_t twinkles[0xf0];
    int32_t active_state;
    int32_t twinkle_count;
} TwinkleManager;

typedef struct FrontendWidget FrontendWidget;
typedef struct FrontendWidgetTooltip FrontendWidgetTooltip;
typedef struct FrontendWidgetTextBuffer FrontendWidgetTextBuffer;

typedef struct FrontendWidgetTextBuffer {
    uint8_t raw[0x420];
} FrontendWidgetTextBuffer;

typedef struct FrontendWidgetTooltip {
    uint8_t _pad_00[0x4];
    int32_t state;
    uint32_t mode_flags;
    FrontendWidget* owner_widget;
    float delay_progress;
    float delay_step;
    FrontendWidget* tooltip_widget;
    uint8_t _pad_1c[0x1c];
    FrontendWidget* owner_widget_38;
    uint8_t _pad_3c[0x4];
} FrontendWidgetTooltip;

typedef struct FrontendWidget {
    uint32_t list_kind;
    uint32_t list_flags;
    FrontendWidget* list_prev;
    FrontendWidget* list_next;
    uint8_t _pad_10[0x34];
    float hide_blend;
    int32_t border_texture_id;
    float authored_left;
    float authored_top;
    float authored_width;
    float authored_height;
    uint8_t texture_hit_test_enabled;
    uint8_t _pad_5d[0x3];
    int32_t background_texture_id;
    int32_t texture_hit_test_sprite;
    uint8_t _pad_68[0x14];
    int32_t widget_type;
    TwinkleManager twinkle_manager;
    float sprite_shadow_offset;
    float slider_position_target;
    float slider_position_current;
    float slider_hit_left;
    float slider_hit_right;
    float slider_hit_top;
    float slider_hit_bottom;
    int32_t shortcut_key_code;
    uint8_t _pad_198[0x8];
    uint32_t widget_flags;
    uint32_t previous_widget_flags;
    uint8_t _pad_1a8[0x4];
    Color4f current_fill_color;
    Color4f idle_fill_color;
    Color4f hot_fill_color;
    Color4f current_text_color;
    Color4f idle_text_color;
    Color4f hot_text_color;
    float hover_blend_target;
    float hover_blend_current;
    float idle_padding;
    float hot_padding;
    float target_padding;
    float current_padding;
    float text_effect_target;
    float text_effect_current;
    float render_inset_delta;
    float render_inset_base;
    uint8_t render_inset_dynamic;
    uint8_t _pad_235[0x3];
    float layout_left;
    float layout_top;
    float texture_hit_x;
    float texture_hit_y;
    float layout_width;
    float layout_height;
    float texture_hit_width;
    float texture_hit_height;
    float border_edge;
    int32_t text_alignment;
    float anchor_x;
    float teardown_progress;
    float teardown_progress_step;
    float stack_gap;
    int32_t texture_id;
    int32_t texture_layer;
    int32_t mouse_history_warmup_frames;
    float previous_mouse_x;
    float previous_mouse_y;
    uint8_t _pad_284[0x8];
    FrontendWidgetTooltip tooltip;
    FrontendWidgetTextBuffer text_buffer;
    int32_t font_id;
    float font_scale;
    float layout_anchor_x;
    float layout_anchor_y;
    uint8_t _pad_6fc[0x1c];
    FrontendWidget* slider_less_widget;
    FrontendWidget* slider_more_widget;
    FrontendWidget* slider_value_widget;
} FrontendWidget;

/* Authored cRExit, exact 0x1c-byte root owner. */
typedef struct Exit {
    int32_t state;
    uint8_t _pad_04[0x08 - 0x04];
    int32_t previous_frontend_state;
    float prompt_y;
    FrontendWidget* prompt_title;
    FrontendWidget* yes_button;
    FrontendWidget* no_button;
} Exit;

typedef struct Completion {
    FrontendWidget* title_widget;
    FrontendWidget* delivered_count_widget;
    FrontendWidget* bonus_summary_widget;
    FrontendWidget* bonus_icon_widget;
    FrontendWidget* continue_widget;
    int32_t continue_state;
    uint8_t continue_visible;
    uint8_t _pad_19[0x1c - 0x19];
    int32_t delivered_count;
    int32_t perfect_delivery;
    int32_t delivered_count_progress;
    int32_t delivered_count_display;
    float delivered_count_progress_limit;
    float delivered_count_progress_step;
    Vec3 widget_world;
    float bonus_progress;
    float bonus_progress_step;
    int32_t bonus_score;
    int32_t total_score;
} Completion;

#endif
