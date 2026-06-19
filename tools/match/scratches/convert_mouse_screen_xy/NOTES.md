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
