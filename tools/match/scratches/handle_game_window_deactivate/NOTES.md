# handle_game_window_deactivate

Window deactivation helper at `0x407440`.

Recovered behavior:

- exits immediately when `g_window_deactivated` is already set;
- when fullscreen config is active, pauses the audio backend, marks the window
  deactivated, and minimizes the main window with `ShowWindow(..., 6)`;
- reads `data_4df860` after the fullscreen branch and clears it when nonzero.
