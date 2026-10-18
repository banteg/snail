// Headless entry point (snail.wasm): the game session (game_session.cpp) at a
// fixed 1/60 s per tick, with scripted input and a presenter that shows
// nothing. The browser build (web_main.cpp) runs the same session live.
//
// Usage: snail.wasm [--ticks N] [--keys SCRIPT] [--warmup N] [--trace] [--profile P] [--replay A3]
//        snail.wasm --tape TAPE --tape-out STATES
//   --ticks   ticks to run (default 600; with --keys, until the script ends)
//   --keys    input script (shell/input_script.cpp)
//   --warmup  random draws before construction in Original; the original
//             used timeGetTime() % 1000, so a run is reproducible only with
//             this. Ultimate makes none, as Android does
//   --trace   print front-end state changes and each screen's widgets
//   --profile original (default) or ultimate (shell/profile.h); --replay and
//             --tape recordings come from the original
//   --replay  replay row 3 of ScoreA.dat (B: ScoreB.dat) against its recording
//             (shell/replay_oracle.cpp); pair with scripts/high_scores.keys
//   --tape    replay a session the original recorded and write the port's
//             state per tick (shell/lockstep_tape.cpp; snail port lockstep)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "extras.h"
#include "fixes.h"
#include "profile.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "game_session.h"
#include "input_script.h"
#include "lockstep_tape.h"
#include "replay_oracle.h"

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

int live_slug_count()
{
    int live = 0;
    for (const cRSlug& slug : g_game->subgame.slug_hazards.slots) {
        if (slug.state != SUB_SLUG_STATE_INACTIVE)
            ++live;
    }
    return live;
}

}  // namespace

int main(int argc, char** argv)
{
    int ticks = -1;
    int warmup = 0;
    const char* keys = 0;
    const char* tape = 0;
    const char* tape_out = 0;
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
        else if (strcmp(argv[i], "--profile") == 0 && i + 1 < argc
                 && (strcmp(argv[i + 1], "original") == 0 || strcmp(argv[i + 1], "ultimate") == 0))
            g_port_ultimate = strcmp(argv[++i], "ultimate") == 0;
        else if (strcmp(argv[i], "--tape") == 0 && i + 1 < argc)
            tape = argv[++i];
        else if (strcmp(argv[i], "--tape-out") == 0 && i + 1 < argc)
            tape_out = argv[++i];
        else if (strcmp(argv[i], "--replay") == 0 && i + 1 < argc) {
            if (!replay_oracle_configure(argv[++i])) {
                fprintf(stderr, "snail: --replay takes a bank letter and row, like A3 or B10\n");
                return 2;
            }
        }
        else {
            fprintf(stderr, "usage: snail [--ticks N] [--keys SCRIPT] [--warmup N] [--trace] [--profile P] [--replay A3]\n");
            return 2;
        }
    }
    // WASI starts in the root of the preopened file system; the launcher passes the caller's directory.
    if (const char* directory = getenv("PWD"))
        chdir(directory);
    if (tape)
        return tape_out ? run_tape(tape, tape_out) : 2;
    if (keys && !load_input_script(keys)) {
        fprintf(stderr, "snail: cannot read key script %s\n", keys);
        return 2;
    }
    if (ticks < 0)
        ticks = replay_oracle_enabled() ? 60 * 60 * 30 : keys ? last_scripted_tick() : 600;

    if (!start_game(warmup))
        return 1;
    fprintf(stderr, "snail: world initialized\n");
    if (replay_oracle_enabled())
        replay_oracle_started();

    int state = -1;
    int subgame_state = -1;
    int tramp_rings = 0;
    int sway_rings = 0;
    int upright_hazards = 0;
    int slugs = 0;
    int lives = -1;
    int padding = 0;
    int parcels = 0;
    unsigned int widgets = 0;
    for (int tick = 0; tick < ticks; ++tick) {
        set_scripted_input(tick);
        if (int result = run_fixed_step(true)) {
            fprintf(stderr, "snail: quit requested at tick %d\n", tick);
            save_game();
            end_game();
            return 0;
        }
        render_frame();
        if (replay_oracle_enabled() && replay_oracle_tick(tick)) {
            end_game();
            return replay_oracle_report();
        }
        if (trace && g_game->players[0].frontend_state != state) {
            state = g_game->players[0].frontend_state;
            fprintf(stderr, "tick %d: frontend_state %d\n", tick, state);
        }
        if (trace && g_game->subgame.subgame_state != subgame_state) {
            subgame_state = g_game->subgame.subgame_state;
            if (subgame_state == 2) {
                const tColour& f = g_game->subgame.level_definition.fringe_color;
                fprintf(stderr, "tick %d: level \"%s\" track_set %d (%s) fringe (%.3f, %.3f, %.3f) rows %d segments %d backdrop %s\n",
                    tick, g_game->subgame.level_definition.level_display_name,
                    g_game->track.current_texture_set,
                    extras_track_texture_name(g_game->track.current_texture_set),
                    f.r, f.g, f.b, g_game->subgame.runtime_row_count,
                    g_game->subgame.level_definition.segment_count,
                    extras_sprite_texture_name(g_game->backdrop.pending_primary_texture_id));
                // Pieces BuildLevel laid from the finish line on (port/patches/22-challenge-finish.patch).
                const cRSubGame& sub = g_game->subgame;
                int pieces = 0;
                for (int row = sub.completion_row_start; row < sub.runtime_row_count; ++row) {
                    if (row == sub.completion_row_start
                        || sub.runtime_rows[row].row_event_id != sub.runtime_rows[row - 1].row_event_id)
                        ++pieces;
                }
                fprintf(stderr, "tick %d: finish rows %d pieces %d\n",
                    tick, sub.runtime_row_count - sub.completion_row_start, pieces);
            }
        }
        if (trace && extras_tramp_ring_active_count() != tramp_rings) {
            tramp_rings = extras_tramp_ring_active_count();
            if (tramp_rings)
                fprintf(stderr, "tick %d: tramp_rings %d, first at x %.2f\n", tick, tramp_rings, extras_tramp_ring_x());
            else
                fprintf(stderr, "tick %d: tramp_rings 0\n", tick);
        }
        if (trace && extras_swaying_ring_count() != sway_rings) {
            sway_rings = extras_swaying_ring_count();
            fprintf(stderr, "tick %d: sway_rings %d\n", tick, sway_rings);
        }
        if (trace && g_game->subgame.player.visible_life_stock != lives) {
            lives = g_game->subgame.player.visible_life_stock;
            fprintf(stderr, "tick %d: lives %d\n", tick, lives);
        }
        if (trace && extras_padding_pick_count() != padding) {
            padding = extras_padding_pick_count();
            fprintf(stderr, "tick %d: padding_segments %d\n", tick, padding);
        }
        if (trace && g_game->subgame.player.parcels_collected != parcels) {
            parcels = g_game->subgame.player.parcels_collected;
            fprintf(stderr, "tick %d: parcels %d\n", tick, parcels);
        }
        if (trace && fixes_upright_hazard_count() != upright_hazards) {
            upright_hazards = fixes_upright_hazard_count();
            fprintf(stderr, "tick %d: upright_hazards %d\n", tick, upright_hazards);
        }
        if (trace && live_slug_count() != slugs) {
            slugs = live_slug_count();
            fprintf(stderr, "tick %d: slugs %d\n", tick, slugs);
        }
        // Once a screen has settled, list its widgets (for writing click scripts).
        if (trace && g_game->fade.state == 0 && widget_set_signature() != widgets) {
            widgets = widget_set_signature();
            fprintf(stderr, "tick %d: widgets\n", tick);
            print_widgets();
        }
    }
    fprintf(stderr, "snail: ran %d ticks\n", ticks);
    if (!replay_oracle_enabled() && !tape)
        save_game();
    end_game();
    return replay_oracle_enabled() ? replay_oracle_report() : 0;
}
