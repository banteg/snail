# Port divergences

Recovered source in `decomp/` compiles unchanged for the port, with one switch:
the port build defines `SNAIL_PORT`. A `SNAIL_PORT` guard is allowed only where a
matched VC6 source shape depends on x86 ABI leniency, or on x87 register
precision, that a portable target does not have, and never to change behaviour. Each guard is listed here; the VC6 side
of every guard still matches.

| Where | Native shape | Port shape | Why |
|---|---|---|---|
| `decomp/game/Game/update_backdrop.cpp` | the `case 1` path calls `void render_backdrop()` and falls off the end of the `int` function (C4715) | returns 0 after the call | VC6 returns `render_backdrop`'s leftover `eax`, and nothing reads `update_backdrop`'s result. A portable target has no defined value for a missing return. |
| `decomp/game/G0/shutdown_bass_audio_window.cpp` | when `UnregisterClassA` fails, calls `void abort_startup_with_3d_error()` and falls off the end of the `int` function (C4715) | returns 0 after the call | VC6 returns the callee's leftover `eax`; the callee exits the process, so nothing reads it. A portable target has no defined value for a missing return. |
| `decomp/game/SubGame/get_track_cell_row_index.cpp` | subtracts `(int)g_track_row_cells_offset`, a symbol whose address is the immediate `0x4340e0` | `offsetof(cRGame, subgame.runtime_cells)` | The immediate falls inside the image's address range, so matching requires a relocation; wasm cannot place a symbol at a fixed address. Same value. |
| `decomp/include/rshell_prelude.h` | included first in the RShell unit: the DirectX 8.1 SDK and `windows.h`, 11,563 stand-in enumerators, then the CRT and project headers RShell's members include | empty | the prelude only sets VC6's frontend symbol numbering, which decides an operand order in `read_repeating_text_input_key_code`; no declaration in it is used |
| `decomp/engine/RMaths/initialize_trigonometry_tables.cpp` | `float angle`, which VC6 keeps in an x87 register at the C runtime's 53-bit precision (RMathInit runs before Direct3D 8 lowers it to 24-bit) | `double angle` | the `Sin`/`Cos` tables must hold the same entries; float angles change more than half of them by a ULP. Same values the original computed |
| `decomp/game/SubGame/update_subgoldy.cpp` (two lateral-velocity decays), `decomp/include/x87_store.h` | `velocity.x = (1 - rate * 0.1f) * velocity.x` stored from an x87 register | stored through `x87_store_float` | the x87 register's wide exponent range rounds an underflowing product to 24 bits before the store rounds it to a denormal; wasm rounds once. Same values the original stored |

## Patches

Larger changes are diffs against the recovered files in `port/patches/`, applied
in name order to the copies the port compiles (`port/generated/patched/`;
`zig build` and `snail port link` refresh them). `decomp/` stays as VC6
matches it. A hunk applies only where its
exact old text occurs once; a decomp edit that moves a patched site stops the
build instead of being built around. The Ultimate rules sit at their native
sites behind `g_port_ultimate` (`port/shell/profile.h`), so Original runs the
recovered code.

| Patch | Change | Why |
|---|---|---|
| `01-layout-offsets` | `cRSubGame::AddGarbage` takes its pool's word offsets from `offsetof` | the matched source spells them as Windows numbers, which the port's larger tables would leave pointing at the salt pool |
| `02-mobile-capacity` | 3600 runtime rows, 200 catalog segments and 150 track render cache rows; the row limit is 3500 in Ultimate and 3100 in Original | Android's BuildLevel (0007e88c) builds courses up to 3500 rows from 176 segments; both originals only report a longer track |
| `03-pro-lives` | a new Pro-Challenge game starts with 8 lives | Android's BuildLevel |
| `04-parcel-radius` | parcels are collected within 1.73, not 1.24, in Ultimate | Android's `cRSubGoldy::Collision` (00077f5c) |
| `05-challenge-padding` | `Random:` levels lay Padding between each pair of random segments in Ultimate, without drawing RAND for it | Android's `cRSubTracks::Init` (000850d4) and BuildLevel |
| `06-random-track-code` | in Ultimate only `Track: r` (code 8) picks a random space backdrop and flip, then a random fringe colour; Pro 1-5 (`Track: 5`) keep their SpacePro sky | Android's `cRSubTracks::Init` (000850d4) and `cRSubGame::StartLevel` (000817ac); Windows reads `Track: r` as 5, which Android uses as a track set |
| `12-path-camera` | in Ultimate a path without a heading keeps its own roll, so a turnover rolls the camera; the snail can leave a path sideways while the jetpack is on; S-bends lift the camera linearly, to 0.55 of the snail's height at the top; off a lift path the lift eases out by 0.98 a tick instead of dropping to 0 | Android's `cRPathFollowGoldy::Traverse` (0004d70c) and `cRCameraman::AI` (00071248); the shell's S-bends carry the kind Android's `BuildSBend` (0004ee74) gives them |
| `13-trampoline-ring` | the Ultimate trampoline ring starts from the bounce itself, so the no-fall clamp and path entries add none | Android's `cRSubGoldy::AI` (0007ac54) adds a ring only there |
| `17-route-numerals` | in Ultimate a route card's title leads with the level's Roman numeral, and a card that would start left of 40 is anchored at 50 | Android's `cRGalaxy::BoxOn` (00058d80) |
| `18-frontend-texts` | in Ultimate the main menu's first entry reads Play and Postal reads Postal Adventure; after the Pro galaxy the thanks-for-playing screen shows Android's three Pro texts | Android's `cRMainMenu::Init` (000697d4), `cRIntro::Init` (000674f8), `cRSplash::Init` (0006aba4) and `cRSplash::AI` (0006a900) |

Narrow seams wrap a matched function in the shell instead (`port/wrapped.txt`,
its body renamed `*_recovered`): the mobile content in `port/shell/extras*.cpp`
and the fixes for the original's own bugs; see [Original bugs](original-bugs.md).

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
