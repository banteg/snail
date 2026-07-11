// initialize_default_runtime_config @ 0x406c10 (cdecl startup initializer)

#include "runtime_config.h"

void initialize_default_runtime_config()
{
    int one = 1;
    int zero = 0;
    int forty = 40;

    g_runtime_config.fullscreen_enabled = (char)one;
    g_runtime_config.render_flags = 0xfe | 0x500;
    g_runtime_config.load_valid_flag = (unsigned char)one;
    g_runtime_config.validation_tail[0] = (unsigned char)zero;
    g_runtime_config.display_mode_index = one;
    g_runtime_config.stream_volume = 0.6f;
    g_runtime_config.sample_volume = 0.6f;
    g_runtime_config.reserved_18 = zero;
    g_runtime_config.reserved_14 = zero;
    g_runtime_config.reserved_0c = zero;
    g_runtime_config.reserved_10 = zero;
    g_runtime_config.steering_sensitivity[0] = 0.75f;
    g_runtime_config.steering_sensitivity[1] = 0.75f;
    g_runtime_config.completion_bonus_x_source = forty;
    g_runtime_config.completion_bonus_y_source = forty;
    g_runtime_config.default_challenge_speed_slider = 0.3f;
    g_runtime_config.reserved_4c = (unsigned char)zero;
    g_runtime_config.reserved_4d = (unsigned char)zero;
    g_runtime_config.high_score_selected_bank = zero;
    g_runtime_config.reserved_50 = zero;
    g_runtime_config.reserved_54 = zero;
    g_runtime_config.reserved_58 = zero;
    g_runtime_config.reserved_5c = zero;
    g_runtime_config.last_entered_player_name[0] = (char)zero;
    g_runtime_config.highest_galaxy_route_index = one;
    g_runtime_config.landscape_backdrop_variant_selector = one;
    g_runtime_config.last_loading_budget = one;
    g_runtime_config.reserved_b0 = 10.0f;
    g_runtime_config.reserved_b4 = 2.5f;
    g_runtime_config.reserved_b8 = -1.5f;
    g_runtime_config.reserved_bc = -1.0f;
    g_runtime_config.new_game_tutorial_started = (unsigned char)zero;
}
