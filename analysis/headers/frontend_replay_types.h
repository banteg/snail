#ifndef FRONTEND_REPLAY_TYPES_H
#define FRONTEND_REPLAY_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef short int16_t;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct TwinkleManager {
    uint8_t twinkles[0xf0];
    int32_t active_state;
    int32_t twinkle_count;
} TwinkleManager;

typedef struct FrontendWidget FrontendWidget;
typedef struct FrontendWidgetTooltip FrontendWidgetTooltip;
typedef struct FrontendWidgetTextBuffer FrontendWidgetTextBuffer;

typedef enum FrontendWidgetFlag {
    FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED = 0x00000020,
    FRONTEND_WIDGET_FLAG_KILL_PENDING = 0x00000200,
    FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE = 0x00000400,
    FRONTEND_WIDGET_FLAG_HIDDEN = 0x00001000,
    FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE = 0x00002000,
    FRONTEND_WIDGET_FLAG_DISABLED = 0x00008000,
    FRONTEND_WIDGET_FLAG_POINTER_INSIDE = 0x00020000,
    FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED = 0x00080000,
    FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION = 0x40000000,
} FrontendWidgetFlag;

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
    uint8_t sprite_wobble_positive;
    uint8_t _pad_5e[0x2];
    int32_t background_texture_id;
    int32_t texture_hit_test_sprite;
    int32_t sprite_extend_texture_c;
    uint8_t _pad_6c[0x10];
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
    FrontendWidgetFlag widget_flags;
    FrontendWidgetFlag previous_widget_flags;
    uint8_t _pad_1a8[0x4];
    tColour current_fill_color;
    tColour idle_fill_color;
    tColour hot_fill_color;
    tColour current_text_color;
    tColour idle_text_color;
    tColour hot_text_color;
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
    int32_t input_cursor;
    int32_t input_cursor_visible;
    float input_cursor_blink_progress;
    float input_cursor_blink_step;
    uint32_t input_flags;
    int32_t input_length;
    int32_t input_capacity;
    FrontendWidget* slider_less_widget;
    FrontendWidget* slider_more_widget;
    FrontendWidget* slider_value_widget;
} FrontendWidget;

typedef struct SubSolution SubSolution;

/* Authored cRHighScore. Windows proves storage through +0xf4; the final class
   boundary before the following TipManager remains open by 0x14 bytes. */
typedef struct HighScore {
    int32_t field_00;
    int32_t mode;
    int32_t selected_bank;
    uint8_t _pad_0c[0x10 - 0x0c];
    uint8_t entering_name;
    uint8_t _pad_11[0x14 - 0x11];
    int32_t selected_rank;
    FrontendWidget* title_widget;
    FrontendWidget* back_button;
    FrontendWidget* bank_toggle_button;
    FrontendWidget* cancel_name_button;
    FrontendWidget* submit_name_button;
    FrontendWidget* row_background_widgets[10];
    FrontendWidget* rank_row_widgets[10];
    FrontendWidget* name_row_widgets[10];
    FrontendWidget* score_row_widgets[10];
    FrontendWidget* replay_row_widgets[10];
} HighScore;

/* Exact 0x48-byte Windows cRIntro owner; mobile has one additional widget. */
typedef struct Intro {
    int32_t replay_attract_bank_cursor;
    uint8_t hide_for_replay_latch;
    uint8_t _pad_05[0x08 - 0x05];
    float attract_reset_progress;
    float attract_reset_step;
    float replay_probe_progress;
    float replay_probe_step;
    uint8_t _pad_18[0x30 - 0x18];
    FrontendWidget* postal_button;
    FrontendWidget* time_trial_button;
    FrontendWidget* challenge_button;
    FrontendWidget* tutorial_button;
    FrontendWidget* help_button;
    FrontendWidget* back_button;
} Intro;
typedef Intro NewGameMenu;

#define SUB_SOLUTION_STRIDE 0x1fac0
#define SUB_SOLUTION_PLAYER_NAME_SIZE 0x14
#define SUB_SOLUTION_RUN_RECORD_COUNT 21600

typedef struct ScoreBucketBlock {
    int32_t values[6];
} ScoreBucketBlock;

typedef struct Time {
    float total_seconds;
    int32_t minutes;
    int32_t seconds;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} Time;

typedef union ScoreOrTime {
    float total_seconds;
    ScoreBucketBlock stats;
    Time timer;
} ScoreOrTime;

typedef struct ReplayRunRecord {
    int16_t lateral_x;
    int16_t delta_z;
    uint8_t flags;
    uint8_t reserved_05;
} ReplayRunRecord;

typedef struct SubSolution {
    int32_t active;
    int32_t score;
    ScoreOrTime score_or_time;
    int32_t score_tail;
    int32_t source_tail;
    int32_t replay_level_index;
    int32_t replay_mode_id;
    int32_t unknown_30;
    int32_t challenge_difficulty_scalar_bits;
    uint32_t runtime_build_flags;
    int32_t high_score_mode_tag;
    int32_t route_or_rank_index;
    int32_t replay_cursor;
    int32_t replay_speed_scalar_bits;
    int32_t challenge_speed_value;
    int32_t challenge_difficulty_value;
    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE];
    int32_t runtime_build_seed;
    int32_t replay_sample_count;
    ReplayRunRecord run_records[SUB_SOLUTION_RUN_RECORD_COUNT];
    float garbage_frequency;
    float salt_frequency;
    int32_t unknown_1fab8;
    int32_t unknown_1fabc;
} SubSolution;

#endif
