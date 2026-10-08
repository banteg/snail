// Browser entry points (snail-web.wasm, a WASI reactor driven by
// port/web/snail.js). The page forwards input events and calls snail_frame
// from requestAnimationFrame with the elapsed time; this runs the original
// loop's timing: whole 1/60 s steps from an accumulator capped at 25 steps,
// then one rendered frame.

#include "game_session.h"
#include "input_state.h"
#include "lockstep_tape.h"
#include "runtime_config.h"

#define WEB_EXPORT(name) __attribute__((export_name(name)))

namespace {
const float kStepSeconds = 0.016666668f;      // g_frame_time_accumulator step
const float kMaxAccumulated = 0.41666666f;    // cap after a stall
const float kSnapToZero = 0.0000083333334f;
float g_accumulator = 0;
}  // namespace

WEB_EXPORT("snail_start") int snail_start(int warmup)
{
    return start_game(warmup) ? 1 : 0;
}

// Returns the game's quit code (1-3) once it asks to quit, otherwise 0.
WEB_EXPORT("snail_frame") int snail_frame(float elapsed_seconds)
{
    g_accumulator += elapsed_seconds;
    if (g_accumulator > kMaxAccumulated)
        g_accumulator = kMaxAccumulated;
    bool stepped = false;
    while (g_accumulator > 0) {
        g_accumulator -= kStepSeconds;
        if ((g_accumulator < 0 ? -g_accumulator : g_accumulator) < kSnapToZero)
            g_accumulator = 0;
        if (int result = run_fixed_step(g_accumulator <= 0))
            return result;
        stepped = true;
    }
    if (stepped)
        render_frame();
    return 0;
}

// The page calls this when it is hidden or closed: the game only saved its
// score tables on quitting, which a browser tab never does.
WEB_EXPORT("snail_save") void snail_save()
{
    save_game();
}

// The host left or entered fullscreen on its own (the browser's Escape, a
// window button): the game's option follows, as the Options menu shows it.
WEB_EXPORT("snail_fullscreen_changed") void snail_fullscreen_changed(int enabled)
{
    g_runtime_config.fullscreen_enabled = (char)(enabled != 0);
}

WEB_EXPORT("snail_fullscreen_enabled") int snail_fullscreen_enabled()
{
    return g_runtime_config.fullscreen_enabled;
}

WEB_EXPORT("snail_key") void snail_key(int scan_code, int down)
{
    input_set_key(scan_code, down != 0);
}

WEB_EXPORT("snail_pointer") void snail_pointer(int x, int y)
{
    input_set_pointer(x, y);
}

WEB_EXPORT("snail_button") void snail_button(int button, int down)
{
    input_set_button(button, down != 0);
}

WEB_EXPORT("snail_wheel") void snail_wheel(int direction)
{
    input_add_wheel(direction);
}

// Replaying a recorded session instead of live input (shell/lockstep_tape.cpp):
// snail_tape_open starts the game from session.tape in the game directory, as
// `snail port lockstep` writes it; each snail_tape_step runs one recorded tick
// and the frames after it, returning how many it rendered, or -1 at the end.
WEB_EXPORT("snail_tape_open") int snail_tape_open()
{
    return tape_open("session.tape") ? 1 : 0;
}

WEB_EXPORT("snail_tape_step") int snail_tape_step()
{
    return tape_step(nullptr);
}
