// Startup and loop steps of game_startup_and_main_loop
// (decomp/game/G0/game_startup_and_main_loop.cpp) without the window message
// pump, display-mode probing and audio device, which the shell replaces.

#include <stdio.h>

#include "archive_index.h"
#include "audio_system.h"
#include "authored_view_state.h"
#include "font_system.h"
#include "frontend_fade.h"
#include "game_root.h"
#include "game_session.h"
#include "input_polling.h"
#include "input_state.h"
#include "loading_bar.h"
#include "main_loop_state.h"
#include "rmath_random.h"
#include "runtime_config.h"

// The CRT ran these static initializers before WinMain; null slots belonged to
// library code or to globals the port's compiler initializes itself.
typedef void (*StaticInitializer)();
extern StaticInitializer g_cpp_initializer_table[];
extern StaticInitializer g_cpp_initializer_table_end[];

void* load_config_file(char* file_name, void* buffer);  // @ 0x42f470
char validate_config_tail_stub(char* config_tail);       // @ 0x42f5b0
char initialize_game_data_archive();                     // shell/files.cpp
char initialize_direct3d_renderer();                     // @ 0x4129c0
int set_cull_mode(int cull_front);                       // @ 0x4129f0
void initialize_main_loop_display_state();               // @ 0x406d70
int construct_game_runtime();                            // @ 0x407b60
void set_tracked_allocation_mark();                      // @ 0x431cb0
void load_registered_texture_refs(int debug_fallback);   // @ 0x412a00
void render_game_frame_scene();                          // @ 0x4134c0
int present_backbuffer();                                // @ 0x413520

bool start_game(int warmup)
{
    for (StaticInitializer* slot = g_cpp_initializer_table; slot < g_cpp_initializer_table_end; ++slot)
        if (*slot)
            (*slot)();

    load_config_file((char*)"SnailMail.cfg", &g_runtime_config);
    g_runtime_config.registration_key_valid = validate_config_tail_stub(g_runtime_config.registration_key);
    RMathInit();
    if (initialize_game_data_archive() == 0 || g_archive_index_records == 0) {
        fprintf(stderr, "snail: cannot open SnailMail.dat in the working directory\n");
        return false;
    }
    g_authored_view_width = 640.0f;
    g_authored_view_height = 480.0f;

    // initialize_audio_subsystem, past its message window.
    if (!g_audio_backend.initialize_bass_audio_backend(0))
        return false;
    g_audio_backend.set_global_sample_volume_config(g_runtime_config.sample_volume);
    g_audio_backend.set_global_stream_volume_config(g_runtime_config.stream_volume);

    // initialize_game_window_and_input, past the window itself.
    initialize_direct3d_renderer();
    install_input_devices();
    set_cull_mode(1);

    initialize_main_loop_display_state();
    g_loading_bar.Init();
    for (int i = 0; i < warmup; ++i) {
        RAND(1.0f, 0);
        gRMathRand2();
    }
    construct_game_runtime();
    set_tracked_allocation_mark();
    if (g_game->initialize_game_assets_and_world() == 0) {
        fprintf(stderr, "snail: initialize_game_assets_and_world failed\n");
        return false;
    }
    load_registered_texture_refs(1);
    g_game->InitLast();
    g_loading_bar.UnInit();
    g_game->fade.StartOn();
    return true;
}

int run_fixed_step(bool renders)
{
    g_render_queue_active = renders;
    for (int step = 0; step < g_game->fixed_update_count; ++step) {
        update_keyboard_input(0);
        update_joystick_input(0);
        update_mouse(0);
        FontAI();
        int result = g_game->AI();
        if (result == 1 || result == 2 || result == 3)
            return result;
    }
    return 0;
}

void render_frame()
{
    render_game_frame_scene();
    if (g_game->render_skip_count == 0)
        present_backbuffer();
}

void end_game()
{
    g_audio_backend.stop_audio_backend();
    g_audio_backend.uninitialize_bass_audio_backend();
}
