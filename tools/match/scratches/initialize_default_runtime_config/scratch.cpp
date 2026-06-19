// initialize_default_runtime_config @ 0x406c10 (cdecl startup initializer)

extern char g_config_fullscreen_enabled; // data_4df920
extern float g_config_sample_volume;     // data_4df918
extern float g_config_stream_volume;     // data_4df91c
extern int g_render_flags;               // data_4df934, byte-tested elsewhere
extern int g_high_score_selected_bank;   // data_4df9c0
extern int g_last_loading_budget;        // data_4df9c4
extern unsigned char g_new_game_tutorial_started; // data_4df9d8

extern int data_4df924;
extern int data_4df928;
extern int data_4df92c;
extern int data_4df930;
extern unsigned char data_4df938;
extern unsigned char data_4df949;
extern int data_4df94c;
extern float data_4df950;
extern float data_4df954;
extern int data_4df958;
extern float data_4df95c;
extern int data_4df960;
extern unsigned char data_4df964;
extern unsigned char data_4df965;
extern int data_4df968;
extern int data_4df96c;
extern int data_4df970;
extern int data_4df974;
extern unsigned char g_last_entered_player_name; // data_4df978
extern int data_4df9b8;
extern int g_landscape_backdrop_variant_selector; // data_4df9bc
extern float data_4df9c8;
extern float data_4df9cc;
extern float data_4df9d0;
extern float data_4df9d4;

void initialize_default_runtime_config()
{
    int one = 1;
    int zero = 0;
    int forty = 40;

    g_config_fullscreen_enabled = (char)one;
    g_render_flags = 0xfe | 0x500;
    data_4df949 = (unsigned char)one;
    data_4df938 = (unsigned char)zero;
    data_4df94c = one;
    g_config_stream_volume = 0.6f;
    g_config_sample_volume = 0.6f;
    data_4df930 = zero;
    data_4df92c = zero;
    data_4df924 = zero;
    data_4df928 = zero;
    data_4df950 = 0.75f;
    data_4df954 = 0.75f;
    data_4df958 = forty;
    data_4df960 = forty;
    data_4df95c = 0.3f;
    data_4df964 = (unsigned char)zero;
    data_4df965 = (unsigned char)zero;
    g_high_score_selected_bank = zero;
    data_4df968 = zero;
    data_4df96c = zero;
    data_4df970 = zero;
    data_4df974 = zero;
    g_last_entered_player_name = (unsigned char)zero;
    data_4df9b8 = one;
    g_landscape_backdrop_variant_selector = one;
    g_last_loading_budget = one;
    data_4df9c8 = 10.0f;
    data_4df9cc = 2.5f;
    data_4df9d0 = -1.5f;
    data_4df9d4 = -1.0f;
    g_new_game_tutorial_started = (unsigned char)zero;
}
