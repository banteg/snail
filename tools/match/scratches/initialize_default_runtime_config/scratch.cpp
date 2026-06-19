// initialize_default_runtime_config @ 0x406c10 (cdecl startup initializer)

extern char g_config_fullscreen_enabled; // data_4df920
extern float g_config_sample_volume;     // data_4df918
extern float g_config_stream_volume;     // data_4df91c
extern int g_render_flags;               // data_4df934, byte-tested elsewhere
extern int g_high_score_selected_bank;   // data_4df9c0
extern int g_last_loading_budget;        // data_4df9c4
extern unsigned char g_new_game_tutorial_started; // data_4df9d8

extern int g_config_reserved_0c;
extern int g_config_reserved_10;
extern int g_config_reserved_14;
extern int g_config_reserved_18;
extern unsigned char g_config_validation_tail_start;
extern unsigned char g_config_load_valid_flag;
extern int g_config_display_mode_index;
extern float g_steering_sensitivity[2];
extern int g_completion_bonus_x_source;
extern float g_config_default_challenge_speed_slider;
extern int g_completion_bonus_y_source;
extern unsigned char g_config_reserved_4c;
extern unsigned char g_config_reserved_4d;
extern int g_config_reserved_50;
extern int g_config_reserved_54;
extern int g_config_reserved_58;
extern int g_config_reserved_5c;
extern unsigned char g_last_entered_player_name; // data_4df978
extern int g_highest_galaxy_route_index;
extern int g_landscape_backdrop_variant_selector; // data_4df9bc
extern float g_config_reserved_b0;
extern float g_config_reserved_b4;
extern float g_config_reserved_b8;
extern float g_config_reserved_bc;

void initialize_default_runtime_config()
{
    int one = 1;
    int zero = 0;
    int forty = 40;

    g_config_fullscreen_enabled = (char)one;
    g_render_flags = 0xfe | 0x500;
    g_config_load_valid_flag = (unsigned char)one;
    g_config_validation_tail_start = (unsigned char)zero;
    g_config_display_mode_index = one;
    g_config_stream_volume = 0.6f;
    g_config_sample_volume = 0.6f;
    g_config_reserved_18 = zero;
    g_config_reserved_14 = zero;
    g_config_reserved_0c = zero;
    g_config_reserved_10 = zero;
    g_steering_sensitivity[0] = 0.75f;
    g_steering_sensitivity[1] = 0.75f;
    g_completion_bonus_x_source = forty;
    g_completion_bonus_y_source = forty;
    g_config_default_challenge_speed_slider = 0.3f;
    g_config_reserved_4c = (unsigned char)zero;
    g_config_reserved_4d = (unsigned char)zero;
    g_high_score_selected_bank = zero;
    g_config_reserved_50 = zero;
    g_config_reserved_54 = zero;
    g_config_reserved_58 = zero;
    g_config_reserved_5c = zero;
    g_last_entered_player_name = (unsigned char)zero;
    g_highest_galaxy_route_index = one;
    g_landscape_backdrop_variant_selector = one;
    g_last_loading_budget = one;
    g_config_reserved_b0 = 10.0f;
    g_config_reserved_b4 = 2.5f;
    g_config_reserved_b8 = -1.5f;
    g_config_reserved_bc = -1.0f;
    g_new_game_tutorial_started = (unsigned char)zero;
}
