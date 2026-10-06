# Modern port plan

Status: stage 1 done (2026-10-06): the recovered source lives in
[`decomp/`](../../decomp/README.md). No port code exists yet. This page records
the decisions and the order of work; update it as stages land.

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
| Renderer | SDL3 GPU API behind our `G0` implementation | one code path with native Metal, D3D12 and Vulkan. Explicit pipeline state means no hidden GL state to leak |
| Audio | miniaudio | sample, OGG stream, voice, volume and pause, as BASS was used. One C file |
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
code path. The renderer needs only a few shaders (fixed-function emulation),
cross-compiled at build time. If a browser build becomes a goal, add a GL ES 3
/ WebGL2 or WebGPU backend behind the same `G0` implementation.

## The renderer: fixed-function emulation for `G0`

The mobile `GL.o` is the reference implementation. It uses about 45 OpenGL ES
1.1 calls:

- a matrix stack;
- client arrays and VBOs;
- fog (`glFogf`);
- blend, cull and depth state;
- `glTexEnvf`;
- `glLineWidth` for toon edges.

Our `G0` keeps that state model on SDL3 GPU:

- a matrix stack and current fog, blend, cull, depth, alpha and texture-stage
  state;
- a pipeline cache keyed by the state combination;
- one vertex/fragment shader pair that implements modulate texturing, vertex
  colour and linear fog;
- toon edges drawn as screen-space quads, since wide lines are not portable.

The entry points to implement come from the boundary scope:

- `render_camera`, `render_object` and `render_object_toon`;
- `build_object_texture_group_buffers` and `refresh_object_vertex_buffer`;
- texture refs (`load_registered_texture_ref`, `bind_texture_ref`);
- the sprite and font quad queues;
- `set_cull_mode`, `set_blend_mode` and `set_object_color`;
- the split-screen viewports.

D3D8 state that has no mobile counterpart, such as texture transforms and
blend modes the mobile build dropped, is recovered from the Windows boundary
functions.

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
  build.zig              compiles decomp/ (minus replaced functions) and shell/
  shell/                 the only new hand-written runtime code
    main.cpp             replaces game_startup_and_main_loop and the window procedure
    rshell_sdl.cpp       files, archive, memory, input lanes, timer
    g0_gpu.cpp           G0 on SDL3 GPU
    sound.cpp            samples, music, voice (miniaudio)
  data/                  tables recovered from the exe's data sections (generated)
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
- `boundary`: reviewed one by one. Bodies that only call `RShell`, `G0` or
  `cRSound`, such as the X2 loaders, are kept. Bodies that touch D3D8,
  DirectInput or BASS directly are reimplemented in `shell/`.
- `replaceable-platform` and `third-party`: never compiled. The three D3DX
  matrix helpers get small portable versions.

## Correctness rules

- **No invented models.** If behaviour is unknown, match the function first.
  The port never carries its own guess at gameplay.
- **Core code changes only through the matcher.** A change must still match,
  or sit behind `PORT_FIX` with an entry in a divergence ledger
  (`docs/port/divergences.md`, to be created with the first one).
- **Exact `rand`.** Track generation reseeds with `RandSeed(runtime_build_seed)`,
  so the port implements the MSVC `rand` LCG exactly. `gRMathRand2` and the
  sine tables are recovered code and come along unchanged.
- **Floats.** The original used x87 with 53-bit precision; the port uses SSE.
  Replays store positions, not inputs, so ghosts don't depend on this. Any
  tick-level divergence it causes is measured by the oracles, not assumed away.
- **PORT(verified)** means checked against native behaviour: multi-frame
  screenshot comparisons and oracle runs, not a single good frame.

## Oracles

- **Function level:** the existing native harnesses
  (`tools/match/compare_loaders_native.py` and the other `compare_*_native.py`)
  run recovered code against relocated original code.
- **Simulation level:** restore the replay oracle and the Windows `Score*.dat`
  fixtures from `570772c30^`, and lockstep-compare the headless port per tick.
  Add per-tick state captures from the original through the Frida tooling
  (`tools/frida/`, `docs/re/frida-runtime-trace.md`).
- **Render level:** `snail screenshots compare` against original captures.

## Stages

1. **Organise the source.** Done: `decomp/` holds all 785 functions in 58
   link-order units, every scratch points at its file with `SOURCE=`, and every
   match is unchanged. Left over for stage 2: fold the eight scratch-local
   compatibility types (such as `SubgoldyPathView`) into shared headers.
2. **Headless link.**
   - Write `port/build.zig`, null `G0` and sound backends, and a file-backed
     `RShell`.
   - Run startup, `construct_game_runtime` and
     `initialize_game_assets_and_world` on the real archive, then tick frames.
   - Target 32-bit with MSVC struct layout first, so the 263 lines of size
     asserts in `decomp/include` hold unchanged.
   - Extract the data tables (path names, sound bank, colour banks, BOD
     catalogs) into `port/data/`.
3. **Oracles.** Bring up the replay oracle and per-tick traces against the
   headless build, and fix divergences in the matcher, never only in the port.
4. **Shell.** SDL3 window and input, miniaudio, then `G0` on SDL3 GPU, verified
   with screenshot comparisons.
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
