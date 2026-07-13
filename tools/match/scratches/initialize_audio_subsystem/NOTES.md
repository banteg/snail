# `initialize_audio_subsystem` recovery notes

Target: `initialize_audio_subsystem @ 0x407a10` (`cdecl`).

The retained source models the hidden BASS window bootstrap:

- fills a stack `WNDCLASSA` with `bass_audio_window_proc` as the
  window procedure;
- registers the `"BASS"` class;
- creates the hidden window with the shared blank text buffer;
- initializes `g_audio_backend` using the hidden window handle;
- applies saved sample and stream volume configuration.

The separately tracked shutdown helper at `0x407b00` now gives this function an
honest manifest boundary without a scratch-local `END` override. The body is
instruction-exact: 73 target instructions and 73 candidate instructions.

The reference manifest now names the real startup/window references used here:
`g_application_instance` (`data_4dfad8`), `g_bass_window` (`data_4dfaf8`),
`bass_audio_window_proc`, and `shutdown_bass_audio_window`. The masked operand audit is clean:
23 resolved operands, no unresolved operands, and no mismatches.

2026-07-11 window-owner consolidation: the hidden BASS window now shares the
same `WndClassA`, `HINSTANCE`, and `HWND` ABI declarations as the main window.
This also makes the ownership split explicit: `g_application_instance` is the
WinMain value used here, while `g_game_window_instance` at `0x50327c` belongs
only to main-window registration. The backend's older generic `void*` method
view still needs a zero-cost cast at the call boundary. Focused matching remains
instruction-exact at 73/73 with 23 clean operands.
