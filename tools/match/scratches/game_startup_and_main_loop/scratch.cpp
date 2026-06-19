// game_startup_and_main_loop @ 0x406dc0 (stdcall, ret 0x10)

typedef int BOOL;
typedef int HWND;
typedef unsigned int UINT;

struct Msg {
    HWND hwnd;
    UINT message;
    UINT wparam;
    int lparam;
    unsigned int time;
    int pt_x;
    int pt_y;
};

typedef char Msg_must_be_0x1c[(sizeof(Msg) == 0x1c) ? 1 : -1];

#include "game_root.h"
#include "loading_screen.h"

class FrontendFade {
public:
    void begin_frontend_fade_in(); // @ 0x40abe0
};

class HighScoreBank {
public:
    char* save_high_scores_and_config(unsigned char save_mask); // @ 0x417940
};

class AudioBackend {
public:
    int stop_audio_backend(); // @ 0x449b90
    void resume_audio_backend_if_paused(); // @ 0x449ba0
};

extern "C" __declspec(dllimport) HWND __stdcall FindWindowExA(
    HWND parent, HWND child_after, char* class_name, char* window_name);
extern "C" __declspec(dllimport) BOOL __stdcall PeekMessageA(
    Msg* msg, HWND hwnd, UINT min_filter, UINT max_filter, UINT remove);
extern "C" __declspec(dllimport) BOOL __stdcall TranslateMessage(Msg* msg);
extern "C" __declspec(dllimport) int __stdcall DispatchMessageA(Msg* msg);
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();
extern "C" __declspec(dllimport) HWND __stdcall GetActiveWindow();
extern "C" __declspec(dllimport) BOOL __stdcall ClipCursor(void* rect);

extern char* g_game_base;                    // data_4df904
extern char g_config_fullscreen_enabled;     // data_4df920
extern unsigned char g_config_load_valid_flag;
extern int g_application_instance;           // data_4dfad8
extern HWND g_main_window;                   // data_4dfaf0
extern unsigned char data_4df864;
extern unsigned char data_4df90c;
extern unsigned char data_4b7759;
extern unsigned char data_4b7758;
extern unsigned char g_window_deactivated;   // data_4b7654
extern unsigned char g_render_queue_active;  // data_4b7236
extern float g_authored_view_width;          // data_4df85c
extern float g_authored_view_height;         // data_4b7760
extern float data_4dfafc;
extern float g_previous_frame_timestamp_seconds; // data_4dfb00
extern float data_4dfb04;
extern float data_4b763c;
extern float data_4b7638;
extern float data_4b7768;

extern unsigned char data_4df918;
extern unsigned char g_config_validation_tail_start;
extern int data_4df858;
extern int data_4b775c;
extern unsigned char data_753c70;
extern AudioBackend g_audio_backend; // data_753c58

int query_runtime_capability(); // @ 0x44afc0
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
int sub_406d70(); // @ 0x406d70
int construct_game_runtime(); // @ 0x407b60
int set_tracked_allocation_mark(); // @ 0x431cb0
char initialize_game_assets_and_world(GameRoot* game); // @ 0x40acf0
int sub_412a00(int value); // @ 0x412a00
int show_and_focus_game_window(); // @ 0x4073b0
BOOL sub_407490(); // @ 0x407490
int sub_4134c0(); // @ 0x4134c0
int sub_413520(); // @ 0x413520
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

    if (query_runtime_capability() < 0x801) {
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
    data_4df90c = 1;
    g_window_deactivated = 0;
    log_startup_timestamp();

    do {
        Msg msg;
        while (PeekMessageA(&msg, 0, 0, 0, 1) != 0) {
            if (msg.message == 0x12) {
                quit_requested = 1;
            } else {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }

        if (data_4df90c != 0) {
            initialize_audio_subsystem();
            initialize_game_window_and_input_wrapper("SnailMail");
            noop_runtime_ai();
            set_fullscreen_mode(g_config_fullscreen_enabled);
            sub_406d70();
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

            sub_412a00(1);
            ((GameRoot*)g_game_base)->initialize_game_last();
            data_4df90c = 0;
            data_4b7759 = 0;
            g_loading_screen.destroy_loading_screen();
            ((FrontendFade*)(g_game_base + 0x24))->begin_frontend_fade_in();
            show_and_focus_game_window();
        }

        if (data_4b7759 != 0) {
            sub_4134c0();
            if (*(int*)(g_game_base + 0x56c) == 0)
                sub_413520();
            data_4b7759 = 0;
        }

        do {
            data_4dfb04 = (float)timeGetTime() * 0.001f;
        } while (data_4dfafc + data_4dfb04 - g_previous_frame_timestamp_seconds
            < 0.0008333333333333334);

        float delta_seconds = data_4dfb04 - g_previous_frame_timestamp_seconds;
        g_previous_frame_timestamp_seconds = data_4dfb04;
        data_4dfafc = delta_seconds + data_4dfafc;
        if (data_4dfafc > 0.41666666f)
            data_4dfafc = 0.41666666f;

        data_4b7758 = 0;
        data_4b763c = 0.0f;

        while (data_4dfafc > 0.0f) {
            if (data_4b7758 != 0 || quit_requested != 0)
                break;

            data_4b763c = data_4b763c + 1.0f;
            data_4dfafc = data_4dfafc - 0.016666668f;

            float remaining = data_4dfafc;
            if (remaining < 0.0f)
                remaining = -remaining;

            if (remaining >= 0.0000083333334f) {
                g_render_queue_active = (data_4dfafc <= 0.0f);
            } else {
                data_4dfafc = 0.0f;
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
        float update_average_total = data_4b7768 * data_4b7638 + data_4b763c;
        data_4b7768 = data_4b7768 + 1.0f;
        data_4b7638 = update_average_total / data_4b7768;
        noop_runtime_ai();
    } while (data_4df864 == 0 && quit_requested == 0);

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
    data_4df90c = 1;
    data_4df864 = 0;
    restore_desktop_display_mode();
    return 0;
}
