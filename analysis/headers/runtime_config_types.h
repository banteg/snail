#ifndef RUNTIME_CONFIG_TYPES_H
#define RUNTIME_CONFIG_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef enum RuntimeRenderFlag {
    RUNTIME_RENDER_STAR_FIELD = 0x00000004,
    RUNTIME_RENDER_PARTICLE_EFFECTS = 0x00000010,
    RUNTIME_RENDER_TRACK_FRINGE = 0x00000020,
    RUNTIME_RENDER_FONT_WAVE = 0x00000100,
    RUNTIME_RENDER_32_BIT_COLOR = 0x00000400,
} RuntimeRenderFlag;

typedef enum RuntimeRenderFlagBit {
    RUNTIME_RENDER_FONT_WAVE_BIT = 8,
} RuntimeRenderFlagBit;

/* Exact persisted SnailMail.cfg owner at 0x4df918. */
typedef struct RuntimeConfig {
    float sample_volume;
    float stream_volume;
    uint8_t fullscreen_enabled;
    uint8_t unknown_09[3];
    int32_t reserved_0c;
    int32_t reserved_10;
    int32_t reserved_14;
    int32_t reserved_18;
    RuntimeRenderFlag render_flags;
    uint8_t validation_tail[0x11];
    uint8_t load_valid_flag;
    uint8_t unknown_32[2];
    int32_t display_mode_index;
    float steering_sensitivity[2];
    int32_t completion_bonus_x_source;
    float default_challenge_speed_slider;
    int32_t completion_bonus_y_source;
    uint8_t reserved_4c;
    uint8_t reserved_4d;
    uint8_t unknown_4e[2];
    int32_t reserved_50;
    int32_t reserved_54;
    int32_t reserved_58;
    int32_t reserved_5c;
    char last_entered_player_name[0x40];
    int32_t highest_galaxy_route_index;
    int32_t landscape_backdrop_variant_selector;
    int32_t high_score_selected_bank;
    int32_t last_loading_budget;
    float reserved_b0;
    float reserved_b4;
    float reserved_b8;
    float reserved_bc;
    uint8_t new_game_tutorial_started;
    uint8_t unknown_c1[3];
} RuntimeConfig;

void __cdecl initialize_default_runtime_config_thunk(void);
void __cdecl initialize_default_runtime_config(void);
extern RuntimeConfig g_runtime_config;

#endif
