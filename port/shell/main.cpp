// Headless entry point: the startup sequence of game_startup_and_main_loop
// (decomp/game/G0/game_startup_and_main_loop.cpp) without the window, display
// and audio device, then the fixed-step update loop for a number of frames.

#include <stdio.h>
#include <stdlib.h>

#include "archive_index.h"
#include "font_system.h"
#include "frontend_fade.h"
#include "game_root.h"
#include "input_polling.h"
#include "loading_bar.h"
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
void initialize_main_loop_display_state();               // @ 0x406d70
int construct_game_runtime();                            // @ 0x407b60
void set_tracked_allocation_mark();                      // @ 0x431cb0
void load_registered_texture_refs(int debug_fallback);   // shell/render_null.cpp

namespace {

void run_static_initializers()
{
    for (StaticInitializer* slot = g_cpp_initializer_table; slot < g_cpp_initializer_table_end; ++slot) {
        if (*slot) {
            (*slot)();
        }
    }
}

}  // namespace

int main(int argc, char** argv)
{
    int frames = argc > 1 ? atoi(argv[1]) : 600;
    run_static_initializers();

    load_config_file((char*)"SnailMail.cfg", &g_runtime_config);
    g_runtime_config.registration_key_valid =
        validate_config_tail_stub(g_runtime_config.registration_key);
    RMathInit();
    if (initialize_game_data_archive() == 0 || g_archive_index_records == 0) {
        fprintf(stderr, "snail: cannot open SnailMail.dat in the working directory\n");
        return 1;
    }
    initialize_main_loop_display_state();
    g_loading_bar.Init();
    construct_game_runtime();
    set_tracked_allocation_mark();
    if (g_game->initialize_game_assets_and_world() == 0) {
        fprintf(stderr, "snail: initialize_game_assets_and_world failed\n");
        return 1;
    }
    load_registered_texture_refs(1);
    g_game->InitLast();
    g_loading_bar.UnInit();
    g_game->fade.StartOn();
    fprintf(stderr, "snail: world initialized\n");

    for (int frame = 0; frame < frames; ++frame) {
        for (int step = 0; step < g_game->fixed_update_count; ++step) {
            update_keyboard_input(0);
            update_joystick_input(0);
            update_mouse(0);
            FontAI();
            int result = g_game->AI();
            if (result == 1 || result == 2 || result == 3) {
                fprintf(stderr, "snail: quit requested after %d frames\n", frame);
                return 0;
            }
        }
    }
    fprintf(stderr, "snail: ran %d frames\n", frames);
    return 0;
}
