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
| `07-track-rules` | in Ultimate a health pickup scores 250, filed under the bonus kind; the ring counter stops at 8, not 10; a default ramp ring turns slow only on its first roll (above 0.93), with no second roll and no Time Trial rule; a wall turret fires when RAND(100) is below 4 + (1 - `salt_frequency`) * -3.5, not 4 | Android's `cRSubGoldy::Collision` (00077f5c, `ScoreAdd` kind 6 at 00070ed0), `cRSubGame::AI` (00082214), `cRSubGame::AddRing` (00073290) and `cRSubLoc::AI` (00077760); the Windows player keeps six score buckets |
| `08-segment-messages` | in Ultimate a segment's message is read from the row 10 ahead of the snail, and `cRTipManager::UnInitTips` clears the tips still showing before it | Android's `cRSubGoldy::AI` (0007ac54) |
| `09-completion-rules` | in Ultimate `cRCompletion::UnInit` pays a skipped tally's bonus, and any difference from the tally's total, through `ScoreAdd`; the replay cursor and sample count hold while the summary waits for a click | Android's `cRCompletion::UnInit` (00061740), which fixes an [original bug](original-bugs.md), and `cRSubGoldy::AI` |
| `10-slug-and-row-capacity` | 16 slug slots; `AddSlug` fills 16 in Ultimate and 8 in Original. `RowFromPos` clamps at row 3599, not 3199, in Ultimate | Android's `cRSubGame` constructor (00025a68), `AddSlug` (0007953c) and every loop over the pool hold 16 slugs; its `RowFromPos` (0006c008) clamps at the last of its 3600 rows |
| `11-track-window` | in Ultimate, rows are scanned to the window's trailing edge plus 48, not 46, and to 40 rows past the finish line, not 20; the trailing edge follows the snail to 30 rows past the line instead of stopping 30 rows before it, and starts at -3, not -19; the finish banner, the salt fade-in and shots reach 48 rows ahead, not 46; a WALL2 cell stops a shot only between heights -1 and 7 | Android's `cRSubGame::AI` (00082214), `cRSubGoldy::AI` (0007ac54) and `Init` (00079da8), `cRBanner::AI` (0006da24), `cRSalt::AI` (00072318) and `cRSubGolb::AI` (000635d4) |
| `12-path-camera` | in Ultimate a path without a heading keeps its own roll, so a turnover rolls the camera; the snail can leave a path sideways while the jetpack is on; S-bends lift the camera linearly, to 0.55 of the snail's height at the top; off a lift path the lift eases out by 0.98 a tick instead of dropping to 0 | Android's `cRPathFollowGoldy::Traverse` (0004d70c) and `cRCameraman::AI` (00071248); the shell's S-bends carry the kind Android's `BuildSBend` (0004ee74) gives them |
| `13-trampoline-ring` | the Ultimate trampoline ring starts from the bounce itself, so the no-fall clamp and path entries add none | Android's `cRSubGoldy::AI` (0007ac54) adds a ring only there |
| `15-pause-quit-scores` | ending a Challenge or Time Trial run from the pause menu skips `cRSubGame::Complete` in Ultimate, so the run records no score | Android's `cRExit::AI` (00062568) |
| `16-time-trial-completion` | a Time Trial finish opens the completion panel in Ultimate: the continue prompt, and on a new best time a blinking "NEW FASTEST TIME!" and the Perfect jingle | Android's `cRCutScene::AI` (00072a5c), `cRCompletion::Init` (0006102c) and `cRCompletion::AI` (00060c0c) |
| `17-route-numerals` | in Ultimate a route card's title leads with the level's Roman numeral, and a card that would start left of 40 is anchored at 50 | Android's `cRGalaxy::BoxOn` (00058d80) |
| `18-frontend-texts` | in Ultimate the main menu's first entry reads Play and Postal reads Postal Adventure; after the Pro galaxy the thanks-for-playing screen shows Android's three Pro texts | Android's `cRMainMenu::Init` (000697d4), `cRIntro::Init` (000674f8), `cRSplash::Init` (0006aba4) and `cRSplash::AI` (0006a900) |
| `20-sound-cues` | in Ultimate, the damage warning plays postalloop every 72 ticks on a timer of its own, not at each 26-tick blink, and lets the last one finish; invincibility starts silently | Android's `cRWarning::Init` (00070334), `Start` (0006ecb0), `AI` (000704f4) and `StopSample` (0006d3f4), and `cRInvincible::Start` (0006d1fc) |
| `21-upramp-sound` | in Ultimate, the mobile `upramp` sample plays on raised and plain ramps, once the snail is more than a row past the last ramp that played it, and at the SuperTramp launch; the `cRSound::Init` wrapper (`port/shell/extras.cpp`) registers it after the PC bank, so every PC sound id stays put | Android's `gSFXBank` (0009bacc), which inserts it at 42, `cRSubGoldy::AI` (0007ac54) and `cRPathFollowGoldy::Traverse` (0004d70c) |
| `22-challenge-finish` | a `Random:` level's finish is laid in pieces as long as the random picks (and their Padding) that carry on past the finish line in Ultimate, each from the Finish segment's first row and each with its pick and mirror draws; Original lays it whole | Android's BuildLevel (0007e88c), measured with `snail android trace` |
| `24-ultimate-path-search` | in Ultimate, mid-air path re-entry tests whether a gravity-adjusted swept segment crosses the attachment sample's plane from above and lands inside the sample quad of half-width `width_cells * 0.5` in XZ, then seeds progress and height from the pre-move position | Android's `cRPath::Search` (0004e318), `PointTriangle` (0004c13c) and `cRSubGoldy::AI` (0007ac54) |

Narrow seams wrap a matched function in the shell instead (`port/wrapped.txt`,
its body renamed `*_recovered`): the mobile content and rules in
`port/shell/extras*.cpp`, among them the typed cheats (`cRCheat::AI`), the
Fluctuosa unlock (`cRGalaxy::Init`) and the High Scores banks
(`cRHighScore::Init`, `UnInit` and `AI`), and the fixes that act around a
function; see [Original bugs](original-bugs.md).
The Ultimate `cRSubTracks::Init` lays Padding before every listed
segment of a level that is not `Mode:Challenge`, as Android's Init (000850d4)
does; the mobile level files stay as Android ships them. `j_rand` and
`RandSeed` give Ultimate's `RAND` and `SRAND`
Android's generator, an index stepped through `RandTable.bin` (`Rand()`
000267f0, `RandSeed` 00029588), in place of the C runtime's `rand`.

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
