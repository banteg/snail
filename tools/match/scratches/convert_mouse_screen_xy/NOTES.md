# convert_mouse_screen_xy @ 0x44c100

First tracked scratch for the cursor-position to authored-coordinate bridge.

Recovered behavior:

- when windowed and the game cursor is captured, read the OS cursor directly
  into authored x/y and return the `y` output pointer on success;
- otherwise read the OS cursor as a delta from the authored viewport center;
- uncaptured mode multiplies both axes by
  `resolve_uncaptured_cursor_sensitivity_scale(g_steering_sensitivity[slot])`;
- captured/fullscreen delta mode applies only the screen-to-authored scales;
- failed `GetCursorPos` calls zero both outputs;
- after delta modes, recenter the OS cursor when the active window is the main
  game window.

This scratch uses the shared `MouseCursorState` view and the same imported
cursor APIs already used by `click_mouse_screen`.

Focused Wibo result: 74.46%, 116/115 instructions, prefix 3/115, with 32 clean
masked operands. The remaining differences are source-shape/register allocation
residuals around branch distances, output-zeroing blocks, and API-call setup
registers.

2026-06-21 zero-output store pass: writing the failure-path output zeros in
`y` then `x` order improves focused Wibo to 77.06%, still 116/115 instructions
with a 3/115 prefix and 32 clean masked operands. The swap nudges VC6's pointer
register choice in all three GetCursorPos failure blocks while preserving the
same observable zeroed outputs. The remaining residual is still branch distance
and API-call setup register ownership.

2026-06-21 follow-up zero-store audit: target-looking `x` then `y` zero stores,
raw integer zero stores, output pointer aliases, and an IDA-ordered captured
branch all failed to beat the retained `y` then `x` source. The `x` then `y`
forms preserve `eax == 0` locally but drop back to 74.46% overall; putting the
captured branch first reshapes the body to 53.28%. Keep the current
counterintuitive zero order until a broader branch-owner lead appears.
