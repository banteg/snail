// Headless entry point: the startup sequence of game_startup_and_main_loop
// (decomp/game/G0/game_startup_and_main_loop.cpp) without the window, display
// and audio device, then its loop at a fixed 1/60 s per tick: update with the
// scripted keyboard, then render through the null device.
//
// Usage: snail.wasm [--ticks N] [--keys SCRIPT] [--warmup N] [--trace]
//   --ticks   ticks to run (default 600; with --keys, until the script ends)
//   --keys    keyboard script (shell/input_script.cpp)
//   --warmup  random draws before construction; the original used
//             timeGetTime() % 1000, so a run is reproducible only with this
//   --trace   print front-end state changes and each screen's widgets

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "archive_index.h"
#include "font_system.h"
#include "frontend_fade.h"
#include "game_root.h"
#include "input_polling.h"
#include "input_script.h"
#include "frontend_widget.h"
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
void render_game_frame_scene();                          // @ 0x4134c0
int present_backbuffer();                                // shell/render_null.cpp

namespace {

void run_static_initializers()
{
    for (StaticInitializer* slot = g_cpp_initializer_table; slot < g_cpp_initializer_table_end; ++slot) {
        if (*slot) {
            (*slot)();
        }
    }
}

bool widget_visible(cRBorder* widget)
{
    unsigned int flags = widget->widget_flags;
    return flags != 0
        && (flags & (FRONTEND_WIDGET_FLAG_HIDDEN | FRONTEND_WIDGET_FLAG_KILL_PENDING | FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE))
        == 0;
}

// Identifies the set of visible widgets, so the trace lists each screen once.
unsigned int widget_set_signature()
{
    unsigned int signature = 2166136261u;
    for (int i = 0; i < BORDER_RECORD_COUNT; ++i) {
        cRBorder* widget = (cRBorder*)&g_game->border_manager.borders[i];
        if (!widget_visible(widget))
            continue;
        signature = (signature ^ (unsigned int)i) * 16777619u;
        for (const char* c = widget->text_buffer; *c; ++c)
            signature = (signature ^ (unsigned char)*c) * 16777619u;
    }
    return signature;
}

void print_widgets()
{
    for (int i = 0; i < BORDER_RECORD_COUNT; ++i) {
        cRBorder* widget = (cRBorder*)&g_game->border_manager.borders[i];
        if (!widget_visible(widget))
            continue;
        unsigned int flags = widget->widget_flags;
        fprintf(stderr, "  widget %d at (%.0f, %.0f) size %.0f x %.0f flags %#x \"%.40s\"\n", i, widget->layout_x,
            widget->layout_y, widget->layout_width, widget->layout_height, flags, widget->text_buffer);
    }
}

}  // namespace

int main(int argc, char** argv)
{
    int ticks = -1;
    int warmup = 0;
    const char* keys = 0;
    bool trace = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--ticks") == 0 && i + 1 < argc)
            ticks = atoi(argv[++i]);
        else if (strcmp(argv[i], "--keys") == 0 && i + 1 < argc)
            keys = argv[++i];
        else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc)
            warmup = atoi(argv[++i]);
        else if (strcmp(argv[i], "--trace") == 0)
            trace = true;
        else {
            fprintf(stderr, "usage: snail [--ticks N] [--keys SCRIPT] [--warmup N] [--trace]\n");
            return 2;
        }
    }
    // WASI starts in the root of the preopened file system; the launcher passes the caller's directory.
    if (const char* directory = getenv("PWD"))
        chdir(directory);
    if (keys && !load_input_script(keys)) {
        fprintf(stderr, "snail: cannot read key script %s\n", keys);
        return 2;
    }
    if (ticks < 0)
        ticks = keys ? last_scripted_tick() : 600;

    run_static_initializers();
    install_scripted_keyboard();

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
    for (int i = 0; i < warmup; ++i) {
        RAND(1.0f, 0);
        gRMathRand2();
    }
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

    int state = -1;
    unsigned int widgets = 0;
    for (int tick = 0; tick < ticks; ++tick) {
        set_scripted_input(tick);
        for (int step = 0; step < g_game->fixed_update_count; ++step) {
            update_keyboard_input(0);
            update_joystick_input(0);
            update_mouse(0);
            FontAI();
            int result = g_game->AI();
            if (result == 1 || result == 2 || result == 3) {
                fprintf(stderr, "snail: quit requested at tick %d\n", tick);
                return 0;
            }
        }
        render_game_frame_scene();
        if (g_game->render_skip_count == 0)
            present_backbuffer();
        if (trace && g_game->players[0].frontend_state != state) {
            state = g_game->players[0].frontend_state;
            fprintf(stderr, "tick %d: frontend_state %d\n", tick, state);
        }
        // Once a screen has settled, list its widgets (for writing click scripts).
        if (trace && g_game->fade.state == 0 && widget_set_signature() != widgets) {
            widgets = widget_set_signature();
            fprintf(stderr, "tick %d: widgets\n", tick);
            print_widgets();
        }
    }
    fprintf(stderr, "snail: ran %d ticks\n", ticks);
    return 0;
}
