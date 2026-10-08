# Modern port plan

Status (2026-10-08, v0.1.0): stages 1 and 2 done, stages 3 and 4 running.
The recovered source lives in [`decomp/`](../../decomp/README.md). `port/`
links it into a headless wasm32 program for scripts and oracles, and into a
build you can play in the browser, hosted at
[snail.banteg.xyz](https://snail.banteg.xyz), or natively on macOS: see
[Playing in the browser](#playing-in-the-browser) and
[Playing natively](#playing-natively-macos). Both oracles match the original
bit for bit on everything recorded so far.
This page records the decisions and the order of work; update it as stages
land.

## Approach: build the port from the recovered source

The port compiles the matched C++ itself and replaces only the original's own
platform layer. It does not transcribe the game into another language.

The shelved Zig/raylib port (about 58k lines, March–June 2026, removed in
`570772c30`) transcribed gameplay by hand. Its invalidation ledger collected
about 25 invented models that later had to be overturned, such as score-bank
decryption, pose interpolation, and a struct taken for a global. Small errors
cascaded: one +0.27 z error at an attachment exit changed collisions and speed
downstream. Compiling the recovered source avoids this class of failure,
because no second copy of the game logic exists. The ledger and the replay
oracle are readable with `git show 570772c30^:<path>`.

What makes this practical:

- **785 functions** of recovered C++ (about 50k lines) on 158 shared headers
  (about 9k lines) in `tools/match/`. There is no inline assembly. Only 8
  scratches declare local compatibility types.
- **637 of 662** port-relevant functions are byte-proven. The remaining 25 are
  semantically complete and fuzzy-match at 77–100% (`tools/match/STATUS.md`).
- **The engine already has a seam.** Gameplay calls an `RShell` API (files,
  archive, memory, input, sound), a `G0` render facade and `cRSound`/voice/music
  calls, never Direct3D or BASS directly. The Android and iOS builds replaced
  D3D8, DirectInput and BASS with OpenGL ES 1.1 and OpenAL under the same API.
  `port_scope` in `analysis/symbols/gameplay-functions.json` marks it: 586
  `core`, 76 `boundary`, 120 `replaceable-platform`, 3 `third-party`.
- **The loop is already port-friendly.** The original runs fixed 1/60 s updates
  (`cRGame::AI`) separately from rendering, with no interpolation.
  `subgame_rate` is a gameplay speed scalar, not a timestep.

## Decisions

| Area | Choice | Why |
|---|---|---|
| Language | C++ for core and shell | the core is the recovered source; the shell implements C++ boundary types (`cRObject`, `cRViewport`) directly |
| Build | `zig build` (zig cc) | one host cross-compiles Windows, Linux and macOS. Explicit targets, including a 32-bit MSVC-layout target for bring-up |
| Platform | SDL3 | window, HiDPI, event pump, gamepads, timers and paths. We own the main loop, as `game_startup_and_main_loop` did |
| Renderer | the recovered `G0`/`GDX` renderer on an emulated Direct3D 8 subset; presenters on WebGL2 (now) and the SDL3 GPU API | the game's own render code runs unchanged. SDL3 GPU gives one native path to Metal, D3D12 and Vulkan, with explicit pipeline state and no hidden GL state to leak |
| Audio | the recovered `cRBass` on an emulated BASS 2.0 subset; presenters on Web Audio and SDL3_mixer | the game's own sample, music and voice code runs unchanged. Sounds stay the archive's OGG files, decoded by the presenter. SDL3_mixer replaced the planned miniaudio: it already has tagged buses, per-track gain, pan, rate and loops |
| Assets | the original `SnailMail.dat`, read in place | the game's own loaders (X2 meshes, animations, objects, segments, levels) are recovered code. The shell adds only TGA and OGG decoding |

**Why not raylib.** The game brings its own mesh loader, fonts, sprites, UI and
cameras, so raylib's high-level layer would go unused. Its `rlgl` batching
caches GL state behind the renderer; the shelved port hit state leaking into
sibling draws and the glyph atlas showing up as an albedo. By default,
`EndDrawing` also couples the buffer swap, frame wait and input polling, while
the original runs several fixed steps per rendered frame.

**Why no hand-written Metal or D3D12 backends.** The game is a 640x480 D3D8
title that draws a few thousand textured quads per frame. Writing a backend per
API buys nothing. SDL3 GPU gives native Metal on macOS (where OpenGL is
deprecated and frozen at 4.1), D3D12 on Windows and Vulkan on Linux from one
code path. A presenter needs one shader pair (the pixel half of the fixed
function pipeline), and the browser already has one on WebGL2.

## The renderer: an emulated Direct3D 8 device

The recovered renderer talks to Direct3D 8 through a small subset, so the
port emulates that subset and compiles the renderer unchanged: `G0` (camera,
objects, toon edges, sprites, texture refs) and `GDX` (device creation,
buffers, render states, overlays).

| Direct3D 8 use | Subset |
|---|---|
| vertex formats | `XYZ\|DIFFUSE\|TEX1` and `XYZ\|TEX1`; no pre-transformed vertices |
| draws | triangle lists and fans, line lists (toon edges), indexed and not |
| transforms | world, view, projection, texture 0 (`COUNT2`) |
| render states | z test and write, alpha blend and test, cull, linear vertex fog; lighting off |
| texture stage 0 | modulate or select, texture and diffuse arguments; wrap or clamp |
| D3DX | TGA textures from memory or file (colour key), `MatrixTranslation`, `MatrixOrthoLH`, `Vec3Normalize` |

`port/shell/d3d8_device.cpp` keeps the fixed-function state and runs the vertex
stage on the CPU (transforms, texture transform, fog factors). Every draw
reaches a presenter (`render_backend.h`) as clip-space triangles or lines with
a snapshot of the pixel state, still in Direct3D conventions. The WebGL2
presenter (`port/web/renderer.js`) applies texture stage 0, alpha test, fog,
blending, depth and culling, and Direct3D's viewport and pixel centres. The
SDL3 GPU presenter will consume the same draws.

## Audio: an emulated BASS 2.0

The game loads BASS at run time: `initialize_bass_audio_backend` extracts
`Bass.dll` from the archive to `tBass.dll`, loads it and binds 23 functions by
name. The shell's `LoadLibraryA` and `GetProcAddress` hand it an emulation
instead (`port/shell/bass_emu.cpp`), so the whole `cRBass` backend and the
voice manager compile unchanged. Samples (`BASS_SampleLoad` with
`max` instances and `OVER_POS` override), sample channels, OGG streams, the
two global volumes, pause and stop are emulated; the presenter
(`audio_backend.h`) decodes the archive's OGG files and plays channels on a
sample or stream bus (Web Audio in `port/web/audio.js`, nothing headless).
The extracted `tBass.dll` is written and deleted as the original did.

## Source layout

The recovered source is organised like crimson's: one file per function in
link-order units, with each scratch's `SOURCE=` pointing into the tree (see
[decomp/README.md](../../decomp/README.md)). Shared headers stay in
`tools/match/include/`.

```
decomp/
  layout.json            unit membership, link-order evidence and port_scope per function
  game/<Unit>/           Border, Cheat, Completion, … G0, Game, GDX, GL, Golb, Path, SubGame, …
  engine/<Unit>/         BassPlay, Font, … RMaths, RSound, RSprite, … Viewport
    <function>.cpp       one file per recovered function
port/
  build.zig              compiles sources.txt with cflags.txt, plus shell/ and generated/
  sources.txt            the recovered files the port compiles (`snail port sources --write`)
  replaced.txt           boundary functions the shell reimplements
  portable.txt           platform functions whose recovered bodies are portable C
  compat/                POSIX stand-ins for MSVC CRT headers (direct.h, io.h)
  shell/                 the only new hand-written runtime code
    main.cpp             replaces game_startup_and_main_loop and the window procedure
    files.cpp            archive start-up and _findfirst over the file system
    input_script.cpp     scripted input for headless runs
    runtime.cpp          MSVC rand, debug output, C++-linkage CRT names
    abi_shims.cpp        calls whose recovered caller and callee disagree on a signature
    game_session.cpp     the startup and loop steps both programs share
    input_state.cpp      live keys, pointer and buttons, read by the recovered polling code
    d3d8_device.cpp      the emulated Direct3D 8 device; d3dx_*.cpp for D3DX
    backend_*.cpp        presenters: null (headless) and web (WebGL2 and Web Audio imports)
    main.cpp, web_main.cpp  the headless and browser entry points
    bass_emu.cpp         the emulated BASS 2.0 library the recovered audio code binds
  web/                   the browser page: WASI, WebGL2 and Web Audio presenters, input
  native/                the native host for snail-web.wasm via wasm2c: WASI, SDL3 GPU, SDL3_mixer
  scripts/               input scripts for headless runs
  generated/             local, never committed (holds the original's data bytes)
    image_data.s         the exe's .rdata and .data, with names and relocations
    link_aliases.s       forwarders from stand-in call names to recovered definitions
tools/match/scratches/   matching configs, NOTES and experiments; SOURCE= points into decomp/
```

Units follow the alphabetical Windows link order in
`analysis/ownership/windows-link-order.json`. Game objects run from `Border.o`
to `Voice.o`, followed by the engine library from `BassPlay.o` to
`Viewport.o`. Note that `RObject` and `RShell` link within the game sequence. The two unnamed runs with name candidates (`G0`, `GDX`) and
twelve small `between-*` gaps are flagged as such in `layout.json`. Matching keeps working per function: the
matcher compiles the file `SOURCE=` names, so `decomp/` becomes the single
source of truth for both matching and the port.

Which functions the port compiles:

- `core`: always, unchanged.
- `boundary`: compiled, except the functions in `port/replaced.txt`, which
  the shell reimplements (now only `set_fullscreen_mode`). Direct3D 8 and
  DirectInput calls reach the shell's emulated devices; BASS calls reach the
  silent audio backend.
- `replaceable-platform` and `third-party`: compiled only when listed in
  `port/portable.txt`, because the recovered body is portable against the
  shell's devices (the tracked allocator, archive reader, error reporting,
  keyboard polling, the Direct3D renderer and D3DX matrix helpers).

## Correctness rules

- **No invented models.** If behaviour is unknown, match the function first.
  The port never carries its own guess at gameplay.
- **Core code changes only through the matcher.** A change must still match,
  or sit behind a `SNAIL_PORT` guard with an entry in the divergence ledger
  ([divergences.md](divergences.md)).
- **Exact `rand`.** Track generation reseeds with `RandSeed(runtime_build_seed)`,
  so the port implements the MSVC `rand` LCG exactly. `gRMathRand2` and the
  sine tables are recovered code and come along unchanged.
- **Float sums in the binary's order.** VC6 reassociates float additions; clang
  evaluates the source exactly. When a matched function's float sum is
  written in another order than the object computes it, rewrite it in the
  object's order (the VC6 object stays byte-identical) so the port rounds the
  same. The session oracle finds these.
- **Floats.** The original's x87 runs at 24-bit precision once Direct3D 8
  creates its device (control word 0x7f, from the lockstep capture), so
  float arithmetic in registers rounds like the port's float32. Code that
  runs before that (`RMathInit`) ran at 53-bit precision; where VC6 keeps
  such a value in a register, the port declares it `double` under
  `SNAIL_PORT`. Any tick-level divergence is measured by the oracles, not
  assumed away.
- **PORT(verified)** means checked against native behaviour: multi-frame
  screenshot comparisons and oracle runs, not a single good frame.

## Oracles

- **Function level:** the existing native harnesses
  (`tools/match/compare_loaders_native.py` and the other `compare_*_native.py`)
  run recovered code against relocated original code.
- **Simulation level: the replay oracle.** `uv run snail port oracle` replays
  the high-score runs the original Windows game recorded
  (`tests/fixtures/replays`, 20 postal and challenge runs) in the headless
  port and compares the snail's z with the recording, tick by tick. A
  recording stores each tick's lateral position and input flags, which
  playback feeds back in, and the z the original's physics produced, which
  playback leaves to the port's simulation. So any difference is a port
  divergence; the tolerance is the recording's own 1/32 quantum. The replay
  starts through the High Scores screen's Replay handler (the shipped game
  hides those buttons but keeps the handler), and playback runs to the run's
  end marker. As of 2026-10-08 all 20 replays match, 57,817 ticks, every one
  within 0.0007 of the original. Next: more of the state per tick (lateral
  x, speed, score) and per-tick captures from the original through Frida
  (`tools/frida/`, `docs/re/frida-runtime-trace.md`) for what replays don't
  record.
- **Simulation level: the session oracle.** The lockstep capture
  ([docs/re/frida-lockstep-capture.md](../re/frida-lockstep-capture.md))
  records whole sessions of the original: the startup warmup, the input
  state before every tick, the render cadence, a snapshot after every tick,
  and frames. `uv run snail port lockstep <session dirs>` replays each in the
  headless port from the same save files and compares every tick. Results on
  the first five sessions (2026-10-08: menus, tutorial, postal, time trial,
  challenge with high-score entries; 43,050 ticks):
  - the RNG state after the startup warmup matches in every session;
  - every integer field (front-end and subgame state, level mode, score,
    lives, shooting tier, both RNG states, `cRGame::AI`'s result) matches on
    every tick;
  - floats drift by single-precision ULPs once the snail follows a path:
    at most 0.0005 in z after 9,600 ticks, without reaching any integer
    state.

  Every source of drift is now pinned:
  - **Trig tables (fixed):** the lockstep capture's `fpu` rows show the x87
    at 24-bit precision (control word 0x7f) from Direct3D 8's device
    creation on, which makes in-register float arithmetic round like the
    port's float32. `RMathInit` runs earlier, at the C runtime's default
    53-bit precision, and VC6 keeps each table angle in a register without
    rounding it to float, so the `Sin`/`Cos` tables were built from double
    angles: more than half of the 8,192 entries differ from float-angle
    tables by a ULP. Path orientation looks them up (`tMatrix::Interpolate`,
    the template builders), which is where the y drift came from. A
    `SNAIL_PORT` guard declares the angle `double` for the port
    ([divergences.md](divergences.md)); the VC6 object is unchanged.
  - **Float sum order (fixed):** VC6 reassociates float sums (no `/Op`).
    `base_position.z = p * dir.z + transform.z + anchor.z` compiles to
    `(p * dir.z + anchor.z) + transform.z`; written in that order, clang
    rounds the same and the VC6 object stays byte-identical. See
    [Correctness rules](#correctness-rules).
  - **Denormal stores (fixed):** an x87 register has a wider exponent
    range, so a float product that underflows is rounded to 24 bits first
    and to a denormal on store; wasm rounds once. The snail's lateral
    velocity decays into denormals when nothing steers it. At the two decay
    sites a `SNAIL_PORT` guard stores through `x87_store_float`
    (`tools/match/include/x87_store.h`), which rounds twice the same way.

  With these fixes, all 10 captured sessions match the original bit for bit
  on every tick and field (56,977 ticks).
- **Render level:** `snail-native --frames N --screenshot` captures any frame
  deterministically; `snail screenshots compare` compares against original
  captures.

## Playing in the browser

```
uv run snail port link && uv run snail port data
cd port && zig build
uv run snail port serve
```

Then open http://127.0.0.1:8017/. `snail-web.wasm` is the same program as the
headless one, built as a WASI reactor: the page loads `SnailMail.dat` from
`artifacts/bin/` into an in-memory file system (the server sends it gzipped
with its XOR obfuscation removed, 7.1 MB instead of 27.4 MB, and the page
restores the original bytes), forwards keys (as DirectInput
scan codes), pointer, buttons and wheel, and calls the game once per animation
frame with the elapsed time. The loop keeps the original's timing: whole 1/60 s
steps from an accumulator capped at 25 steps, then one rendered frame. While
it loads, the page shows the game's own loading screen (`Sprites/Loading.tga`
with `LoadingBarOn.tga` filled as `cRLoadingBar` fills it, both served from the
archive as AVIF, about 16 KB together); when the game has started it waits for
a click or key press, which unlocks sound (browsers require a gesture) without
reaching the game, so the intro plays from its start.
Files the game writes (`SnailMail.cfg` with progress and options, the
`ScoreA/B/C.dat` tables) persist in the browser's IndexedDB. The game wrote
its score tables only when quitting, so the page runs those saves when it is
hidden or closed. `?reset` clears them, and `?mute` silences the game until
`?mute=0` (the page remembers either).
`?warmup=N` fixes the random warmup for a repeatable start.

### Enhancements

The gear in the page's corner switches the port's enhancements over the
original, one by one or all at once (Original, Enhanced); the page remembers
the choice. They live in the host and the presenters, never in the game's
logic, so the oracles hold either way.

- **Sharp rendering:** the presenter draws at the canvas's size in device
  pixels instead of 640x480. Viewports scale, while the half-pixel offset stays
  half an original pixel, so every draw lands where it did, only finer.
- **Fullscreen:** the game's own Fullscreen option (`set_fullscreen_mode`, which
  the shell replaces) puts the page in fullscreen. Browsers allow that only
  after a gesture, so a saved fullscreen setting waits for the click that
  starts the game. Leaving fullscreen through the browser turns the option off,
  so the Options menu stays truthful. In fullscreen, Escape still reaches the
  game where the browser supports keyboard lock; holding it leaves fullscreen.
- **Trap the mouse:** a click locks the pointer to the game (pointer lock), and
  its motion moves the game's cursor at the speed it had. Escape lets it go.
  The original trapped the pointer only by taking over the display in
  fullscreen.
- **See further ahead:** the track is drawn three times as far
  (`shell/draw_distance.cpp`). The original's view ends at its far plane, 52
  units from the camera; the whole track is built at level start, but its
  render caches are linked only 46 units ahead of the snail, and row models and
  uncached cells 38 units ahead, by the fixed step. Before a frame renders, the
  shell links what the game would link further on, moves the far plane (and
  fog band) out to match, and undoes every write after drawing, so the
  simulation never sees it. Pickups, hazards and parcels still appear 38 units
  ahead, where the game spawns them: spawning draws random numbers. Both
  oracles match with it on (`--draw-distance` in the headless program).
  The original's linear vertex fog (30 to 50 units) does not show with its
  right-handed view, in the port as in captures of the original.

### Hosting

https://snail.banteg.xyz serves the same page as static files from Cloudflare
(a Worker with static assets, [`port/wrangler.jsonc`](../../port/wrangler.jsonc)):

```
uv run snail port pack
wrangler deploy -c port/wrangler.jsonc
```

`pack` writes `artifacts/web/`: the page, a stripped `ReleaseFast` build of
`snail-web.wasm` (4.1 MB, about 0.2 MB as sent compressed; the DWARF is 7 MB of
the development build), the packed archive and the loading screen images. The release build replays the
lockstep sessions and high-score runs bit for bit, like the development one.
The deploy also points the custom domain at the Worker and provisions its
certificate.

## Playing natively (macOS)

```
brew install sdl3 sdl3_mixer wabt
cd port && zig build native -Doptimize=ReleaseFast
zig-out/bin/snail-native [--mute] <directory with SnailMail.dat>
```

Native builds can't compile the game for 64-bit yet (stage 5), so the native
host runs the same 32-bit `snail-web.wasm`: wasm2c translates it to C, and
`port/native/` implements its imports in an SDL3 window. WASI maps to the real
file system (the data directory is the root, paths match case-insensitively),
so saves land beside `SnailMail.dat` as they did on Windows. The presenters
are SDL3 GPU (Metal shaders for now; other platforms need SPIR-V or DXIL
versions of the same two shaders) and SDL3_mixer. The window scales the
640x480 frame with letterboxing. `--frames N --screenshot FILE` runs N fixed
frames in a hidden window and saves the last one; runs with the same
`--warmup` give byte-identical frames.

The native host has the same enhancements, on by default: rendering at the
window's pixel resolution, the game's Fullscreen option making the window
fullscreen (the window's own controls turn the option off and on), a click
trapping the pointer (Escape in a window, or leaving it, frees it), and the
longer view.
`--no-hidpi`, `--no-fullscreen` and `--no-trap-mouse` switch them off one by
one, `--draw-distance S` sets the view (default 3, 1 for the original's),
`--original` switches all of them off; compare screenshots with the original's at
640x480 with `--original`.

## Building the headless port

```
uv run snail port link && uv run snail port data
cd port && zig build
cd <dir with SnailMail.dat>
node <repo>/port/shell/run.mjs <repo>/port/zig-out/bin/snail.wasm --keys <repo>/port/scripts/tutorial.keys --trace
```

The headless loop is `game_startup_and_main_loop` at a fixed 1/60 s per tick:
poll input, run `cRGame::AI`, then render the scene through the emulated
device, with a presenter that shows nothing. Options:

- `--keys SCRIPT` replays keys, mouse buttons and pointer positions
  (`shell/input_script.cpp` documents the format; `port/scripts/` has
  examples). Keys go through the recovered `update_keyboard_input` via a
  DirectInput device; the mouse is a 640x480 window at the screen origin.
- `--trace` prints front-end state changes and, whenever the screen changes,
  each visible widget with its rectangle and text, which is what a script
  needs to click it.
- `--warmup N` sets the random draws before construction. The original made
  `timeGetTime() % 1000` of them; the port defaults to none, so runs repeat
  exactly.
- `--ticks N` runs that many ticks (default: until the script ends, or 600).

`port/scripts/tutorial.keys` goes through the main menu into the tutorial and
plays it. A fresh profile unlocks only the tutorial, as in the original.

When the program traps, pipe the stack trace through `uv run snail port
symbolize`, which adds the recovered `file:line` to every wasm frame from the
build's DWARF line table.

The target is `wasm32-wasi`, run under Node's WASI. It has the MSVC x86 data
layout the size asserts expect (4-byte pointers, 8-byte-aligned `double`, no
`long double` in the source) without a Windows runtime, and it runs anywhere.
Until stage 5, native builds run this same 32-bit program through wasm2c (see
[Playing natively](#playing-natively-macos)).

Wasm is strict where x86 was lenient, and that strictness is the useful part:
every call must agree with its definition's signature, at link time and in
indirect calls at run time. The build surfaced every recovered declaration that
disagreed with its definition; most were fixed in the source (all still match),
and the rest are listed in [divergences.md](divergences.md).

Memory accesses are strict too. x86 addressing wraps at 32 bits, so a matched
shape such as `p[(int_offset - size_t_offset) / sizeof(int)]` reaches `p[-2]`
through an unsigned index near 2^30. Wasm folds the constant into a load offset
that does not wrap, and traps. The fix is to keep that arithmetic signed in the
source; the VC6 output stays byte-identical, so the match is unchanged.

**Data comes from the original image.** Recovered code declares its globals,
strings, tables and vtables `extern`. `snail port data` emits the exe's
`.rdata` and `.data` as one contiguous block per section, with every known name
as a weak label at its original offset and every pointer as a relocation:

- a pointer to a recovered function becomes a function-table entry with the
  exact signature its compiled object defines;
- a word that reads as text counts as a pointer only if its target starts a
  string in initialized data (string tables do; `"txt\0"` reads as `0x747874`);
- callback slots whose recovered target has another signature get a generated
  adapter that passes `this` and drops the result;
- pointers into library code the port does not compile become zero, listed in
  `generated/image_data.json`.

The zero-filled tail of `.data` stays in the same section as the initialized
bytes. Arrays such as `g_animation_directory` run across that boundary, and a
separate `.bss` section is placed after libc's own state, which the game then
overwrote.

**Link names.** Matching compares call targets by address, so recovered code
sometimes calls a function under a stand-in owner (`RuntimeSlot::…`) or one of
several identical-code-folded owners. `snail port link` compiles every source,
resolves each undefined call through the function manifest, and emits a
forwarder when the signatures are compatible; `generated/link_report.json`
lists the rest for the shell.

**Compiler flags** (`cflags.txt`): `-fno-strict-return`, because matched
functions that fall off the end of a non-void body (VC6 returned `eax`) would
trap; sanitizers and the stack protector off, as the original had neither.

## Stages

1. **Organise the source.** Done: `decomp/` holds all 785 functions in 58
   link-order units, every scratch points at its file with `SOURCE=`, and every
   match is unchanged. Left over: fold the eight scratch-local compatibility
   types (such as `SubgoldyPathView`) into shared headers; meanwhile
   `port/shell/abi_shims.cpp` bridges the calls made through them.
2. **Headless link.** Done: 682 recovered files compile unchanged and link
   with the shell. The program constructs the 19.8 MB `cRGame`, loads every
   asset from `SnailMail.dat`, and a key script plays through the intro, main
   menu and new-game menu into the tutorial: level generation, render caches
   and gameplay with its prompts, deaths and restarts. Randomised 20,000-tick
   scripts through gameplay and the exit prompt run without a trap, and runs
   repeat exactly. See
   [Building the headless port](#building-the-headless-port).
3. **Oracles.** Running: the replay oracle passes on every recorded run, and
   the session oracle replays all 10 captured sessions of the original bit
   for bit (see [Oracles](#oracles)). Left: comparing the captured frames
   with the port's renders, and longer sessions. Fix divergences in the
   matcher, never only in the port.
4. **Shell.** Running: the recovered renderer draws through the emulated
   Direct3D 8 device and the recovered audio code through an emulated BASS
   2.0, and the browser build plays from the intro through the menus into
   gameplay with keyboard, mouse and sound, and saves persist; it is hosted at
   snail.banteg.xyz (see [Hosting](#hosting)). The native host runs the same
   build in an SDL3 window on macOS (SDL3 GPU, SDL3_mixer).
   Left: SPIR-V and DXIL shaders for Linux and Windows, and screenshot
   comparisons against the original.
5. **64-bit and platforms.** Turn absolute size asserts into field-offset
   checks and remove the byte-stride casts that assume 4-byte pointers (about a
   dozen scratches, mostly path builders). Then ship macOS arm64, Windows x64
   and Linux.
6. **Modern options.** Resolution, widescreen and frame interpolation live only
   in `shell/`, behind flags. They never change core behaviour.

Matching the remaining 25 partials continues in parallel. The port can include
them now, but `update_subgoldy`, `update_golb_ai` and
`update_track_attachment_follow_state` are where a wrong reading cascades, so
oracle divergences there are checked against their NOTES first.
