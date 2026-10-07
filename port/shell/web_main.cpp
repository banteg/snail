// Browser entry points (snail-web.wasm, a WASI reactor driven by
// port/web/snail.js). The page forwards input events and calls snail_frame
// from requestAnimationFrame with the elapsed time; this runs the original
// loop's timing: whole 1/60 s steps from an accumulator capped at 25 steps,
// then one rendered frame.

#include "game_session.h"
#include "input_state.h"

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
