#ifndef RUNTIME_CONFIG_H
#define RUNTIME_CONFIG_H

enum RuntimeRenderFlag {
    // Independently consumed by the authored cRStarManager lifecycle.
    RUNTIME_RENDER_STAR_FIELD = 0x00000004,
    // Gates fireworks, pickup bursts, ring showers, and Golb impact sprites.
    RUNTIME_RENDER_PARTICLE_EFFECTS = 0x00000010,
    // Gates the runtime row attachment bodies and built track-fringe meshes.
    RUNTIME_RENDER_TRACK_FRINGE = 0x00000020,
    // Selects per-character wave animation in the front-end font path.
    RUNTIME_RENDER_FONT_WAVE = 0x00000100,
    // Selects the 32-bit rather than 16-bit Direct3D display mode.
    RUNTIME_RENDER_32_BIT_COLOR = 0x00000400,
};

enum RuntimeRenderFlagBit {
    RUNTIME_RENDER_FONT_WAVE_BIT = 8,
};

struct RuntimeConfig {
    float sample_volume;                         // +0x00
    float stream_volume;                         // +0x04
    char fullscreen_enabled;                     // +0x08
    unsigned char unknown_09[3];                 // +0x09
    int reserved_0c;                             // +0x0c
    int reserved_10;                             // +0x10
    int reserved_14;                             // +0x14
    int reserved_18;                             // +0x18
    unsigned int render_flags;                   // +0x1c
    unsigned char validation_tail[0x11];         // +0x20
    unsigned char load_valid_flag;               // +0x31
    unsigned char unknown_32[2];                 // +0x32
    int display_mode_index;                      // +0x34
    float steering_sensitivity[2];               // +0x38
    int completion_bonus_x_source;               // +0x40
    float default_challenge_speed_slider;        // +0x44
    int completion_bonus_y_source;               // +0x48
    unsigned char reserved_4c;                   // +0x4c
    unsigned char reserved_4d;                   // +0x4d
    unsigned char unknown_4e[2];                 // +0x4e
    int reserved_50;                             // +0x50
    int reserved_54;                             // +0x54
    int reserved_58;                             // +0x58
    int reserved_5c;                             // +0x5c
    char last_entered_player_name[0x40];          // +0x60
    int highest_galaxy_route_index;              // +0xa0
    int landscape_backdrop_variant_selector;     // +0xa4
    int high_score_selected_bank;                // +0xa8
    int last_loading_budget;                     // +0xac
    float reserved_b0;                           // +0xb0
    float reserved_b4;                           // +0xb4
    float reserved_b8;                           // +0xb8
    float reserved_bc;                           // +0xbc
    unsigned char new_game_tutorial_started;     // +0xc0
    unsigned char unknown_c1[3];                 // +0xc1
};

typedef char RuntimeConfig_must_be_0xc4[
    (sizeof(RuntimeConfig) == 0xc4) ? 1 : -1];

extern RuntimeConfig g_runtime_config; // data_4df918

#endif
