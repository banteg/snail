# game_startup_and_main_loop @ 0x406dc0

Structure-first recovery for the WinMain-style startup and main loop.

- Rejects a second `"SnailMailWindowClass"` instance, loads config, initializes
  the archive, display/input timing globals, and the first loading/game runtime.
- Runs the native message pump, restart-on-dirty startup branch, fixed timestep
  accumulation, active-window input update path, and shutdown save/uninit path.
- Keeps scalar runtime globals scratch-local for now; this function touches many
  cross-cutting app shell flags that need a deliberate shared header pass later.

Initial scratch is expected to be partial because the native block layout is
heavily shaped by out-of-line early returns and x87 timestep comparisons.

Focused match result: 63.14% (`325` target instructions, `337` candidate
instructions), with `95` masked operands resolved, `31` unresolved, and `4`
masked mismatches.

2026-06-20 config/startup symbol pass:

- The post-load config helper at `0x42f5b0` is now recovered as
  `validate_config_tail_stub`; raw image disassembly shows it ignores the
  config-tail pointer and returns true.
- Startup now calls the recovered `initialize_game_window_and_input_wrapper`
  at `0x4119c0`, matching the native call target before the real body at
  `0x4119d0`.
- The config-tail pointer and load-valid flag are named, reducing masked audit
  debt from the previous local baseline without changing the function's control
  flow or register-shape residuals.

Known shape gaps:

- Native keeps `ebx` as the zero register and `edi` as the quit flag; this
  scratch still lets MSVC pick `ebp`/`edi` early and cache `1` in `ebx`.
- The fixed timestep x87 comparisons are behaviorally modeled but not laid out
  like native.
- Several app-shell globals still use scratch-local names, so the matcher reports
  symbol-level mismatches around `data_4dfafc`/`data_4dfb04` and nearby flags.
