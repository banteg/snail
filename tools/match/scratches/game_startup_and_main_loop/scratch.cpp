// game_startup_and_main_loop @ 0x406dc0 (stdcall, ret 0x10)

#include "frontend_fade.h"
#include "game_root.h"
#include "high_score_bank.h"
#include "loading_screen.h"
#include "win32_window_state.h"

class StartupAudioBackendView {
public:
    int stop_audio_backend(); // @ 0x449b90
    void resume_audio_backend_if_paused(); // @ 0x449ba0
};

extern "C" __declspec(dllimport) HWND __stdcall FindWindowExA(
    HWND parent, HWND child_after, char* class_name, char* window_name);
extern "C" __declspec(dllimport) BOOL __stdcall PeekMessageA(
    WindowMessage* msg, HWND hwnd, UINT min_filter, UINT max_filter, UINT remove);
extern "C" __declspec(dllimport) BOOL __stdcall TranslateMessage(WindowMessage* msg);
extern "C" __declspec(dllimport) int __stdcall DispatchMessageA(WindowMessage* msg);
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();
extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) BOOL __stdcall ClipCursor(void* rect);

extern char* g_game_base;                    // data_4df904
extern char g_config_fullscreen_enabled;     // data_4df920
extern unsigned char g_config_load_valid_flag;
extern unsigned char g_main_loop_exit_requested;  // g_main_loop_exit_requested
extern unsigned char g_game_initialization_pending;  // g_game_initialization_pending
extern unsigned char data_4b7759;
extern unsigned char data_4b7758;
extern unsigned char g_window_deactivated;   // data_4b7654
extern unsigned char g_render_queue_active;  // data_4b7236
extern float g_authored_view_width;          // data_4df85c
extern float g_authored_view_height;         // data_4b7760
extern float g_frame_time_accumulator;  // g_frame_time_accumulator
extern float g_previous_frame_timestamp_seconds; // data_4dfb00
extern float g_current_frame_timestamp_seconds;  // g_current_frame_timestamp_seconds
extern float g_current_frame_update_steps;  // g_current_frame_update_steps
extern float g_mean_update_steps_per_frame;  // g_mean_update_steps_per_frame
extern float g_main_loop_frame_count;  // g_main_loop_frame_count

extern unsigned char data_4df918;
extern unsigned char g_config_validation_tail_start;
extern int data_4df858;
extern int data_4b775c;
extern unsigned char data_753c70;
extern StartupAudioBackendView g_audio_backend; // data_753c58

int query_directx_runtime_version(); // @ 0x44afc0
char validate_config_tail_stub(void* config_tail); // @ 0x42f5b0
void abort_startup_with_3d_error(); // @ 0x4088a0
int rebuild_game_archive_if_needed(); // @ 0x405370
void* load_config_file(char* file_name, void* buffer); // @ 0x42f470
void initialize_trigonometry_tables(); // @ 0x44c930
char initialize_game_data_archive(); // @ 0x430e40
int snapshot_current_display_mode(); // @ 0x407850
int initialize_mouse_authored_scale_from_clip_rect(); // @ 0x44bbb0
int probe_display_mode_count(); // @ 0x407880
int read_current_display_resolution(void* width, void* height); // @ 0x4078b0
int log_startup_timestamp(); // @ 0x406d30
char initialize_audio_subsystem(); // @ 0x407a10
int initialize_game_window_and_input_wrapper(char* window_name); // @ 0x4119c0
int noop_runtime_ai(); // @ 0x407b50
int set_fullscreen_mode(int enabled); // @ 0x414260
int initialize_main_loop_display_state(); // @ 0x406d70
int construct_game_runtime(); // @ 0x407b60
int set_tracked_allocation_mark(); // @ 0x431cb0
char initialize_game_assets_and_world(GameRoot* game); // @ 0x40acf0
void load_registered_texture_refs(int debug_fallback); // @ 0x412a00
int show_and_focus_game_window(); // @ 0x4073b0
BOOL sub_407490(); // @ 0x407490
int render_game_frame_scene(); // @ 0x4134c0
int present_backbuffer(); // @ 0x413520
int update_keyboard_input(); // @ 0x44b870
int update_joystick_input(); // @ 0x44b570
int update_mouse(HWND hwnd); // @ 0x44bc50
int update_font_wave_state(); // @ 0x449ca0
BOOL sub_407b00(); // @ 0x407b00
int free_tracked_allocations_to_mark(); // @ 0x431c70
void scalar_delete(void* pointer); // @ 0x48ba34
char* save_config_file(char* file_name, void* bytes, int byte_count); // @ 0x42f540
int uninitialize_game_data_archive(); // @ 0x430ef0
int uninitialize_input_devices(); // @ 0x411d80
int restore_desktop_display_mode(); // @ 0x407860
double random_float_below(float limit, int unused); // @ 0x44dc90 caller shape
int next_math_random_value(); // @ 0x44c900

int __stdcall game_startup_and_main_loop(
    int hInstance, int hPrevInstance, char* lpCmdLine, int nShowCmd)
{
    int quit_requested = 0;

    if (FindWindowExA(0, 0, "SnailMailWindowClass", 0) != 0)
        return 0;

    if (query_directx_runtime_version() < 0x801) {
        abort_startup_with_3d_error();
        return 0;
    }

    rebuild_game_archive_if_needed();
    load_config_file("SnailMail.cfg", &data_4df918);
    g_config_load_valid_flag = validate_config_tail_stub(&g_config_validation_tail_start);
    g_application_instance = hInstance;
    initialize_trigonometry_tables();

    if (initialize_game_data_archive() == 0)
        return 0;

    snapshot_current_display_mode();
    initialize_mouse_authored_scale_from_clip_rect();
    probe_display_mode_count();
    read_current_display_resolution(&data_4df858, &data_4b775c);
    g_authored_view_width = 640.0f;
    g_authored_view_height = 480.0f;
    g_game_initialization_pending = 1;
    g_window_deactivated = 0;
    log_startup_timestamp();

    do {
        WindowMessage msg;
        while (PeekMessageA(&msg, 0, 0, 0, 1) != 0) {
            if (msg.message == 0x12) {
                quit_requested = 1;
            } else {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }

        if (g_game_initialization_pending != 0) {
            initialize_audio_subsystem();
            initialize_game_window_and_input_wrapper("SnailMail");
            noop_runtime_ai();
            set_fullscreen_mode(g_config_fullscreen_enabled);
            initialize_main_loop_display_state();
            g_loading_screen.initialize_loading_screen();

            int warmup_count = timeGetTime() % 1000;
            if (warmup_count > 0) {
                do {
                    random_float_below(1.0f, 0);
                    next_math_random_value();
                    --warmup_count;
                } while (warmup_count != 0);
            }

            construct_game_runtime();
            set_tracked_allocation_mark();

            GameRoot* game = (GameRoot*)g_game_base;
            if (initialize_game_assets_and_world(game) == 0)
                quit_requested = 1;

            load_registered_texture_refs(1);
            ((GameRoot*)g_game_base)->initialize_game_last();
            g_game_initialization_pending = 0;
            data_4b7759 = 0;
            g_loading_screen.destroy_loading_screen();
            ((FrontendFade*)(g_game_base + 0x24))->begin_frontend_fade_in();
            show_and_focus_game_window();
        }

        if (data_4b7759 != 0) {
            render_game_frame_scene();
            if (*(int*)(g_game_base + 0x56c) == 0)
                present_backbuffer();
            data_4b7759 = 0;
        }

        do {
            g_current_frame_timestamp_seconds = (float)timeGetTime() * 0.001f;
        } while (g_frame_time_accumulator + g_current_frame_timestamp_seconds - g_previous_frame_timestamp_seconds
            < 0.0008333333333333334);

        float delta_seconds = g_current_frame_timestamp_seconds - g_previous_frame_timestamp_seconds;
        g_previous_frame_timestamp_seconds = g_current_frame_timestamp_seconds;
        g_frame_time_accumulator = delta_seconds + g_frame_time_accumulator;
        if (g_frame_time_accumulator > 0.41666666f)
            g_frame_time_accumulator = 0.41666666f;

        data_4b7758 = 0;
        g_current_frame_update_steps = 0.0f;

        while (g_frame_time_accumulator > 0.0f) {
            if (data_4b7758 != 0 || quit_requested != 0)
                break;

            g_current_frame_update_steps = g_current_frame_update_steps + 1.0f;
            g_frame_time_accumulator = g_frame_time_accumulator - 0.016666668f;

            float remaining = g_frame_time_accumulator;
            if (0.0f > remaining)
                remaining = -remaining;

            if (remaining >= 0.0000083333334f) {
                g_render_queue_active = (g_frame_time_accumulator <= 0.0f);
            } else {
                g_frame_time_accumulator = 0.0f;
                g_render_queue_active = 1;
            }

            HWND active_window = GetActiveWindow();
            if (active_window == g_main_window) {
                if (data_753c70 == 1)
                    g_audio_backend.resume_audio_backend_if_paused();
                if (active_window == g_main_window)
                    goto update_game;
            }

            if (g_window_deactivated != 0) {
update_game:
                int update_index = 0;
                if (((GameRoot*)g_game_base)->fixed_update_count > 0) {
                    do {
                        update_keyboard_input();
                        update_joystick_input();
                        update_mouse(g_main_window);
                        update_font_wave_state();
                        int frame_result = ((GameRoot*)g_game_base)->run_frame_update();
                        data_4b7759 = 1;
                        if (frame_result == 1 || frame_result == 2 || frame_result == 3) {
                            quit_requested = 1;
                            break;
                        }
                        ++update_index;
                    } while (update_index < ((GameRoot*)g_game_base)->fixed_update_count);
                }
            } else {
                ClipCursor(0);
                g_render_queue_active = 1;
                data_4b7759 = 1;
                if (g_config_fullscreen_enabled != 0)
                    sub_407490();
            }
        }

        data_4b7758 = 0;
        float update_average_total = g_mean_update_steps_per_frame * g_main_loop_frame_count + g_current_frame_update_steps;
        g_main_loop_frame_count = g_main_loop_frame_count + 1.0f;
        g_mean_update_steps_per_frame = update_average_total / g_main_loop_frame_count;
        noop_runtime_ai();
    } while (g_main_loop_exit_requested == 0 && quit_requested == 0);

    g_audio_backend.stop_audio_backend();
    sub_407b00();
    ((HighScoreBank*)(g_game_base + 0x6ffae0))->save_high_scores_and_config(1);
    ((HighScoreBank*)(g_game_base + 0x6ffae0))->save_high_scores_and_config(2);
    ((HighScoreBank*)(g_game_base + 0x6ffae0))->save_high_scores_and_config(4);
    ((HighScoreBank*)(g_game_base + 0x6ffae0))->save_high_scores_and_config(8);
    ((HighScoreBank*)(g_game_base + 0x6ffae0))->save_high_scores_and_config(16);
    noop_runtime_ai();
    free_tracked_allocations_to_mark();
    scalar_delete(g_game_base);
    uninitialize_game_data_archive();
    save_config_file("SnailMail.cfg", &data_4df918, 0xc4);
    uninitialize_input_devices();
    g_game_initialization_pending = 1;
    g_main_loop_exit_requested = 0;
    restore_desktop_display_mode();
    return 0;
}
