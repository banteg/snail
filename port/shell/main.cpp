// Headless entry point (snail.wasm): the game session (game_session.cpp) at a
// fixed 1/60 s per tick, with scripted input and a presenter that shows
// nothing. The browser build (web_main.cpp) runs the same session live.
//
// Usage: snail.wasm [--ticks N] [--keys SCRIPT] [--warmup N] [--trace]
//   --ticks   ticks to run (default 600; with --keys, until the script ends)
//   --keys    input script (shell/input_script.cpp)
//   --warmup  random draws before construction; the original used
//             timeGetTime() % 1000, so a run is reproducible only with this
//   --trace   print front-end state changes and each screen's widgets

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "frontend_widget.h"
#include "game_root.h"
#include "game_session.h"
#include "input_script.h"

namespace {

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

    if (!start_game(warmup))
        return 1;
    fprintf(stderr, "snail: world initialized\n");

    int state = -1;
    unsigned int widgets = 0;
    for (int tick = 0; tick < ticks; ++tick) {
        set_scripted_input(tick);
        if (int result = run_fixed_step(true)) {
            fprintf(stderr, "snail: quit requested at tick %d\n", tick);
            end_game();
            return 0;
        }
        render_frame();
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
    end_game();
    return 0;
}
