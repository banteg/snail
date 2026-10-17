// initialize_default_runtime_config @ 0x406c20 (compiler-generated initializer)

#include "runtime_config.h"

inline RuntimeConfig::RuntimeConfig()
{
    int one = 1;
    int zero = 0;
    int forty = 40;

    fullscreen_enabled = (char)one;
    render_flags = 0xfe | 0x500;
    registration_key_valid = (unsigned char)one;
    registration_key[0] = (char)zero;
    display_mode_index = one;
    stream_volume = 0.6f;
    sample_volume = 0.6f;
    reserved_18 = zero;
    reserved_14 = zero;
    reserved_0c = zero;
    reserved_10 = zero;
    steering_sensitivity[0] = 0.75f;
    steering_sensitivity[1] = 0.75f;
    challenge_speed_percent = forty;
    challenge_difficulty_percent = forty;
    default_challenge_speed_slider = 0.3f;
    reserved_4c = (unsigned char)zero;
    reserved_4d = (unsigned char)zero;
    high_score_selected_bank = zero;
    reserved_50 = zero;
    reserved_54 = zero;
    reserved_58 = zero;
    reserved_5c = zero;
    last_entered_player_name[0] = (char)zero;
    highest_galaxy_route_index = one;
    landscape_backdrop_variant_selector = one;
    last_loading_budget = one;
    reserved_b0 = 10.0f;
    reserved_b4 = 2.5f;
    reserved_b8 = -1.5f;
    reserved_bc = -1.0f;
    new_game_tutorial_started = (unsigned char)zero;
}

RuntimeConfig g_runtime_config; // 0x4df918
