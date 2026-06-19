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
instructions), with `91` masked operands resolved, `21` unresolved, and `18`
masked mismatches.

Known shape gaps:

- Native keeps `ebx` as the zero register and `edi` as the quit flag; this
  scratch still lets MSVC pick `ebp`/`edi` early and cache `1` in `ebx`.
- The fixed timestep x87 comparisons are behaviorally modeled but not laid out
  like native.
- Several app-shell globals still use scratch-local names, so the matcher reports
  symbol-level mismatches around `data_4dfafc`/`data_4dfb04` and nearby flags.
