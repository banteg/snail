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
instructions), with `96` masked operands resolved, `30` unresolved, and `4`
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

2026-06-20 startup-runtime reference pass:

- The shutdown call target at `0x48ba34` is now curated as the CRT
  `scalar_delete` helper. This clears one masked unresolved operand in the
  teardown path while leaving the control-flow/register residuals visible.

2026-06-20 startup shared-service type pass:

- Replaced the scratch-local `FrontendFade` and `SubHighScore` method-only
  stubs with the shared headers. The focused startup matcher stays at 63.14%
  (`337` candidate instructions, `96` resolved masked operands, `30`
  unresolved, `4` mismatches), while those two type rows disappear from
  `snail match types --paths`.
- The owner scratches still match after the promotion:
  `begin_frontend_fade_in`, `save_high_scores_and_config`,
  `resume_audio_backend_if_paused`, and `stop_audio_backend` all report
  100.00%.
- The callee at `0x449b90` does not read `ECX`, so its body alone cannot
  distinguish a zero-argument global from a member method. The later caller
  evidence below resolves that ABI ambiguity in favor of `AudioBackend`.

2026-06-20 unresolved-layout cleanup:

- The temporary startup-only audio shell kept the focused source honest while
  the stop call ABI was unresolved. It is superseded by the caller proof below.

Known shape gaps:

- Native keeps `ebx` as the zero register and `edi` as the quit flag; this
  scratch still lets MSVC pick `ebp`/`edi` early and cache `1` in `ebx`.
- The fixed timestep x87 comparisons are behaviorally modeled but not laid out
  like native.

2026-06-21 comparison-shape sweep:

- Spelling the fixed-timestep absolute-value check as `0.0f > remaining`
  instead of `remaining < 0.0f` improves focused Wibo from 63.14% to 63.65%.
  The candidate is still structurally mismatched in the main-loop register
  ownership, but this recovers one x87 comparison direction without changing
  behavior.

2026-06-21 main-loop timing global curation:

- Curated five main-loop timing globals in
  `analysis/symbols/gameplay-references.json`, recovering their names from this
  scratch's own fixed-timestep and per-frame average modeling:
  `g_frame_time_accumulator` (`0x4dfafc`),
  `g_current_frame_timestamp_seconds` (`0x4dfb04`),
  `g_current_frame_update_steps` (`0x4b763c`),
  `g_mean_update_steps_per_frame` (`0x4b7638`), and
  `g_main_loop_frame_count` (`0x4b7768`). The scratch externs now use these
  recovered names; the `data_4xxxxxx` spellings remain as aliases.
- Masked-audit debt dropped from `96 ok / 30 unresolved / 4 mismatch` to
  `119 ok / 7 unresolved / 4 mismatch`. The focused score is unchanged at
  63.14% because curation resolves masked operands without altering the
  normalized instruction stream; the remaining unresolved entries are app-shell
  call targets and flag bytes whose owners are still being recovered.
- The per-frame running average is a true cumulative mean:
  `mean = (frame_count * prev_mean + current_frame_steps) / (frame_count + 1)`,
  with `g_main_loop_frame_count` incremented once per rendered frame. Spelling
  the multiply as `mean * frame_count` (commutative) instead of
  `frame_count * mean` clears the two masked-operand mismatches at the
  `fld`/`fmul` pair by matching native's `fld frame_count; fmul mean` load
  order.

2026-06-20 display-resolution curation:

- Named the startup display-mode outputs as `g_current_display_width`
  (`0x4df858`) and `g_current_display_height` (`0x4b775c`), matching
  `read_current_display_resolution`.
- Focused matcher remains 63.14%; masked audit is now
  `121 ok / 4 unresolved / 5 mismatch`.
- The remaining unresolved operands are app-shell call targets
  `0x44afc0`, `0x406d70`, `0x412a00`, and `0x4134c0`; leave them uncurated
  until their bodies have stronger names than the current scratch placeholders.

2026-06-20 display-state helper curation:

- Named the startup frame-loop reset helper at `0x406d70` as
  `initialize_main_loop_display_state` after raw disassembly showed it clears
  the display-mode/view-sample state, window-deactivation latches, object
  texture transform matrix, and main-loop timing counters before loading-screen
  construction.
- Added the exact `clear_display_mode_state` helper at `0x407910`, which
  clears the queued view-sample count and current display-mode pointer. The
  adjacent `0x407920` helper clears the display-mode probe count after a
  minimized-window restore.
- The startup masked audit now has no unresolved app-shell call targets. The
  DirectX capability probe at `0x44afc0` is named as
  `query_directx_runtime_version` and still awaits a dedicated scratch; the
  texture registry loader at `0x412a00` and render-scene call at `0x4134c0`
  are named as `load_registered_texture_refs` and `render_game_frame_scene`.

2026-07-11 Win32 owner consolidation: startup now uses the shared
`WindowMessage`, `HINSTANCE`, and `HWND` declarations. This proves the entrypoint
stores its instance at `g_application_instance` (`0x4dfad8`) for the hidden
BASS window, while main-window creation uses the distinct cached instance at
`0x50327c`. The type-only rewrite leaves the focused 63.65%, 338/325 stream and
its six existing structural mismatches unchanged.

2026-07-13 audio backend ownership proof:

- Binary Ninja finds exactly one native xref to `0x449b90`, at startup-loop
  shutdown `0x407222`; the immediately preceding instruction loads
  `ECX = 0x753c58`, the address of `g_audio_backend`. That caller-side ABI
  evidence proves `stop_audio_backend` is an `AudioBackend` member even though
  its leaf body never reads `this`.
- Startup now uses the shared `AudioBackend` declaration for both stop and
  resume. The byte tested at `0x753c70` is therefore recovered as
  `g_audio_backend.is_paused` (`+0x18`), not a separate scratch-local global.

2026-07-13 main-loop state ownership pass:

- Binary Ninja xrefs show `0x4b7758` is confined to the startup/main-loop
  function: it is reset before and after the fixed-update loop and tested beside
  the local quit flag inside that loop. It is now
  `g_fixed_update_abort_requested`; no writer that arms it is present in this
  binary, so the name describes only the proven gate semantics.
- The same xref pass shows `0x4b7759` is the loop's render-request latch. It is
  set after each game update and by the inactive-window path, then consumed and
  cleared around `render_game_frame_scene` / `present_backbuffer`. It is now
  `g_frame_render_requested`.
- Added `main_loop_state.h` for the process-owned flags and fixed-timestep
  globals already shared by startup, window focus handling, render-queue
  producers, and subgame input gating. This removes their accidental ownership
  by individual scratch files and by `font_system.h`.

2026-07-13 BASS window ownership closure: shutdown now calls the separately
tracked `shutdown_bass_audio_window` owner by name. Its native body proves the
hidden window handle is zeroed only on the fatal destroy-failure path; successful
window destruction jumps directly to class unregistration.

2026-07-14 root-owner promotion:

- Startup now holds `data_4df904` as the proven `GameRoot*` and reaches the
  owned `FrontendFade +0x24`, `render_skip_count +0x56c`, and fixed-update
  state through that owner instead of byte arithmetic.
- The shutdown record at root `+0x6ffae0` is
  `GameRoot::subgame.sub_high_score`: root `+0x74618` plus
  `SubgameRuntime::sub_high_score +0x68b4c8` closes the address exactly.
- Calling `GameRoot::initialize_game_assets_and_world()` with its recovered
  thiscall ABI removes the scratch's false pushed argument and stack cleanup.
  Focused matching improves from 63.65%, 338/325 instructions and 125 clean
  masked operands to 63.84%, 336/325 and 126 clean masked operands, with the
  same six honest structural mismatches.
- The sampled display dimensions and minimized-window helper now use their
  curated names and exact types; these ownership/name promotions are
  codegen-neutral.

2026-07-16 input ABI and warmup arithmetic recovery:

- Native `0x40715d..0x407180` loads and pushes `g_main_window` separately for
  `update_keyboard_input`, `update_joystick_input`, and `update_mouse`, then
  releases all three cdecl arguments with one `add esp, 0xc`. The keyboard and
  joystick bodies do not read their window arguments, but this caller-side
  evidence closes their otherwise invisible ABI and is now shared through
  `input_polling.h`.
- All three poller owners remain exact after the signature promotion. The main
  loop gains the native argument loads/pushes and reduces its masked mismatches
  from five to three; the whole-function similarity metric shifts because the
  added instructions expose an existing fixed-update block-layout difference.
- The warmup count is a signed cast of the unsigned `timeGetTime()` result
  before `% 1000`. That produces native's `cdq; idiv` without corrupting the
  later unsigned timestamp conversion, which deliberately uses a zero-extended
  qword and `fild qword`. Changing the imported return type itself was rejected:
  it emitted `fild dword`, shrank the frame, and regressed the match.
- Together these recoveries improve the honest focused result from 63.84% to
  64.28% (`344/325` instructions, `127` clean masked operands, no unresolved
  operands, and three structural mismatches).

2026-07-16 authored-view ownership: the startup writes are now the canonical
producer of one logical 640x480 coordinate-space pair shared by renderer and
mouse code. Width and height remain separate process globals at their proven
addresses; no contiguous struct is invented. Focused output stays at the honest
64.28% baseline with 127 clean operands and three structural mismatches.
