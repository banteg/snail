# Port divergences

Recovered source in `decomp/` compiles unchanged for the port, with one switch:
the port build defines `SNAIL_PORT`. A `SNAIL_PORT` guard is allowed only where a
matched VC6 source shape depends on x86 ABI leniency, or on x87 register
precision, that a portable target does not have, and never to change behaviour. Each guard is listed here; the VC6 side
of every guard still matches.

| Where | Native shape | Port shape | Why |
|---|---|---|---|
| `decomp/game/Game/update_backdrop.cpp`, `tools/match/include/backdrop.h` | `return render_backdrop();` from an `int` function, with `render_backdrop` declared `int` everywhere but its own definition | `render_backdrop()` is `void` everywhere; `update_backdrop` returns 0 on that path | VC6 returned `render_backdrop`'s leftover `eax`, and nothing reads `update_backdrop`'s result. Wasm requires one signature per function. |
| `decomp/game/SubGame/get_track_cell_row_index.cpp` | subtracts `(int)g_track_row_cells_offset`, a symbol whose address is the immediate `0x4340e0` | `offsetof(cRGame, subgame.runtime_cells)` | The immediate falls inside the image's address range, so matching requires a relocation; wasm cannot place a symbol at a fixed address. Same value. |
| `tools/match/include/rshell_prelude.h` | includes the DirectX 8.1 SDK and `windows.h`, then 13,762 stand-in enumerators | empty | the prelude only sets VC6's frontend symbol numbering, which decides an operand order in `read_repeating_text_input_key_code`; no declaration in it is used |
| `decomp/engine/RMaths/initialize_trigonometry_tables.cpp` | `float angle`, which VC6 keeps in an x87 register at the C runtime's 53-bit precision (RMathInit runs before Direct3D 8 lowers it to 24-bit) | `double angle` | the `Sin`/`Cos` tables must hold the same entries; float angles change more than half of them by a ULP. Same values the original computed |
| `decomp/game/SubGame/update_subgoldy.cpp` (two lateral-velocity decays), `tools/match/include/x87_store.h` | `velocity.x = (1 - rate * 0.1f) * velocity.x` stored from an x87 register | stored through `x87_store_float` | the x87 register's wide exponent range rounds an underflowing product to 24 bits before the store rounds it to a denormal; wasm rounds once. Same values the original stored |

## Shell behaviour that differs from the shipped build

| Where | Shipped | Port | Why |
|---|---|---|---|
| `port/shell/runtime.cpp` `debug_report_stub` | empty (`0x44b7c0`) | prints to stderr | diagnostics only; changes no game state |
| `port/shell/files.cpp` `initialize_game_data_archive`, `click_mouse_screen` | also call `GetClipCursor` / `SetCursorPos` | without the Win32 cursor calls | no window yet (stage 4 restores them on SDL3) |
| `port/shell/input_script.cpp` `update_mouse` | DirectInput deltas and Win32 window and clip rectangles | scripted absolute pointer for a 640x480 client area at the screen origin | both native branches reduce to the same `update_input_controller_pointer_region` call for that window; buttons arrive as `game_window_proc` would set them |
| `port/shell/main.cpp` startup | `timeGetTime() % 1000` random draws before construction | `--warmup N`, default 0 | the draw count was wall-clock noise; a fixed count makes runs repeat |
| `port/shell/bass_emu.cpp` | BASS 2.0 (`tBass.dll`) | emulated BASS subset | the game stops a looped sound by passing its channel to `BASS_SampleStop`, and asks `BASS_ChannelIsActive` about a sample (voice overlap checks). The emulation relates channels to their sample for both; the shipped `BASS.DLL` is packed, so this reading of BASS 2.0 is unverified |
| `port/shell/game_session.cpp` audio start | `initialize_audio_subsystem` registers a hidden `BASS` window first | no window | BASS used the window only as its owner |
| `port/web/snail.js`, `save_game` | score tables saved only on a clean quit | also saved whenever the page is hidden or closed | a browser tab never quits; the saved files are the ones the quit path writes |
