# Rewrite Plan

This section captures the intended direction for the playable rewrite of Snail Mail.

The current verified versus fallback or scaffold ledger lives in [port-status.md](port-status.md).

## Stack Split

The project is split into two tracks:

- Python for reverse-engineering and tooling
- Zig + raylib for the actual game rewrite

Python is the right place for:

- archive parsing and extraction
- format inspection and verification
- test fixtures and one-off analysis tools
- asset and script documentation

Zig + raylib is the target runtime for:

- windowing and platform glue
- rendering
- input
- audio
- gameplay simulation
- loading the original game content

## Asset Policy

The Zig runtime should load the original asset formats directly.

That means the rewrite should consume the original decoded file types we have identified so far:

- `.tga`
- `.ogg`
- `.txt`
- `.x2`

The rewrite should not depend on a Python-only converted asset pipeline as a required runtime step. Python tools may still extract, inspect, and validate assets, but the final Zig game should understand the original content formats itself.

Practical interpretation:

- extracting `SnailMail.dat` during development is fine
- using Python to study or validate asset formats is fine
- requiring a custom offline conversion into a new engine-specific format is not the default plan

## Fidelity Rules

The rewrite should stay faithful to the original game mechanics.

This includes:

- movement feel
- collision behavior
- enemy behavior
- timers and scripted sequences
- weapon behavior
- scoring and progression

To keep that stable, simulation should be separated from rendering:

- gameplay runs on a fixed simulation tick
- rendering can run at higher frame rates

This avoids changing mechanics accidentally while still allowing visual improvements.

## Allowed Improvements

The rewrite is allowed to improve presentation where that does not alter gameplay rules.

Current approved improvement areas:

- higher frame rates
- higher rendering resolution
- longer draw distance
- better texture filtering

These changes should remain render-layer improvements. They should not silently modify:

- physics timing
- collision volumes
- movement speeds
- spawn timing
- gameplay balance

## Architecture Direction

The expected boundary between the two tracks is:

- Python discovers and documents how the original game works
- Zig reimplements the runtime behavior against the same asset formats

The preferred end state is:

- Python remains a developer toolchain
- Zig is the shipping game/runtime
- the Zig codebase can load the original content without Python being present

## Early Milestones

The first rewrite milestones should be:

1. Create the Zig + raylib application shell.
2. Load original `.tga` textures and `.ogg` audio.
3. Implement native Zig parsers for `.txt` and `.x2`.
4. Build a small asset or level viewer.
5. Start reconstructing gameplay systems on top of the original content.

## Current Scaffold

The repo now includes a minimal Zig + raylib runtime scaffold:

- [`build.zig`](../../build.zig)
- [`build.zig.zon`](../../build.zig.zon)
- [`zig/src/archive.zig`](../../zig/src/archive.zig)
- [`zig/src/object.zig`](../../zig/src/object.zig)
- [`zig/src/segment.zig`](../../zig/src/segment.zig)
- [`zig/src/level.zig`](../../zig/src/level.zig)
- [`zig/src/track.zig`](../../zig/src/track.zig)
- [`zig/src/xanim.zig`](../../zig/src/xanim.zig)
- [`zig/src/main.zig`](../../zig/src/main.zig)

Current behavior:

- the runtime opens a window
- reads [`SnailMail.dat`](../../artifacts/bin/SnailMail.dat) directly
- builds asset catalogs for the archive's `.tga`, `.ogg`, `.x2`, `_OBJECT.TXT`, `SEGMENTS/*.TXT`, and `LEVELS/*.TXT` entries
- parses `BACKGROUNDS/*.TXT` scripts and resolves both single-image and split `_A` / `_B` TGA background layouts directly from the archive
- browses original textures directly from archive memory
- previews original OGGs as both one-shot sounds and music streams
- parses `.x2` meshes and renders them in a 3D preview using archive-backed textures
- parses [`X/_ANIMATION.TXT`](../../artifacts/extracted/SnailMail.dat/X/_ANIMATION.TXT) and auto-plays matching `.x2` frame families with interpolated vertex animation
- parses `_OBJECT.TXT` quads and renders object previews in 3D using sibling TGA textures from the archive
- parses `LEVELS/*.TXT` and `SEGMENTS/*.TXT`, preserves typed row metadata such as `Path`, `Ring`, `Parcel`, `JetPack=Off`, `3DModel`, `NoFall`, and the post-row `*` flag, and renders a sequential 3D track preview with semantic markers
- resolves segment `3DModel=<name>.x` rows to matching `X/<NAME>.X2` meshes when those assets exist and instances them directly in the level preview
- runs model animation and the new level runner on a fixed `1/60` simulation clock instead of wall-clock render time
- includes a deterministic level runner that advances through the parsed track with a discrete `runtime_track_index` cursor plus fractional `movement_progress`, samples row metadata, and exposes lane, cell, attachment, and recent-event state in the UI
- the level runner now distinguishes attachment probe rows from primary attachment-entry rows, mirroring the current runtime evidence that lowercase `p` mostly behaves like tile `29` probes while uppercase `P` is the normal tile `30` entry path
- the runner also consumes the authored gameplay-cell vocabulary directly, so `(` trampoline rows, `$`, `J`, `s`, `&`, `M`, parcel digits, ring rows, `NoFall`, and `JetPack=Off` now update deterministic runner counters instead of living only as preview markers
- the level preview now also reuses the recovered runtime floor-height sampler for cell slabs and gameplay markers, so trampoline-family tile `0x16` and the basic ramp families render with their known vertical bias instead of a fully flat placeholder surface
- the preview and runner now also use the currently confirmed gameplay build preset `0x00f5cfff`, so slug rows respect their recovered runtime gate and the March 8 trace-driven fallback garbage or salt candidates on tiles `0x01`, `0x0f`, and `0x15` are surfaced in the UI instead of disappearing behind authored glyphs alone
- the track loader now has an explicit no-model path for headless simulation tests, so gameplay coverage no longer depends on uploading decorative `.X2` meshes
- the default `snail` path now reuses the original loading-screen, intro-text, and menu assets and can hand off evidence-backed menu actions like `Tutorial`, `Challenge Mode`, `Help`, and `Credits`
- the loading screen now advances from actual startup tasks in the port instead of a timer, though it still only covers the current front-end asset, script, music, and score loads rather than the original game's full world-init pass
- the default in-level camera now follows the runner forward instead of reusing the debug orbit camera, which makes the level path much closer to a playable Turbo viewpoint
- the authored `Sample=` and `Message=` metadata on active level segments now drives voice playback and timed prompt queueing in the default level path instead of being trapped in the debug browser only
- the runner now keeps a dedicated gameplay stopwatch shaped after the recovered `advance_timer_counters` helper, so route timing is carried by runtime state instead of only being reconstructed from `tick_count` at the result screen
- the gameplay HUD now also renders a dedicated damage gauge widget and a postal-only 9-slot life strip instead of leaving those recovered states only in debug text
- the default level path now also accepts mouse steering by mapping cursor motion onto the current lane bounds instead of relying on keyboard-only lane changes
- the default level HUD now surfaces parcel progress and finish state, and `Enter` returns to the menu once the runner reaches the end of the authored level path
- the front-end hierarchy now follows the recovered constructor labels from the binary: top level `New Game`, `High Scores`, `Options`, `Credits`, `Exit`, and `New Game` submenu `Tutorial`, `Postal Mode`, `Time Trial`, `Challenge Mode`, `Help`, `Back`
- the main menu, new-game menu, options screen, and high-score screen now also render as direct text overlays on the shipped `Menubg` backdrop instead of the older generic panel shell, which is much closer to the original Windows front-end composition
- `Help` uses the shipped help background directly, while `INTRO/INTRO.TXT` and `INTRO/CREDITS.TXT` now share the recovered `SpaceRed` plus `INTROTEXT.OGG` text-screen flow; `Postal Mode`, `Time Trial`, `Challenge Mode`, and `Tutorial` now use the recovered mode-to-level handoff, while score presentation and later front-end progression still remain unresolved
- the intro and credits crawl now also follows the recovered tilted text-plane setup from `initialize_intro_screen`, including the fixed intro focal scale, `Font3D` unit glyph height, shared duration scroll, right-to-left centered glyph placement, world-sized line or image placement, `Esc` or click skip behavior, and the recovered fade-to-black transition overlay
- single-image front-end backdrops like `SpaceRed` and `Starmap` now use the best current `320x240` crop window inside the shipped `512x256` textures plus the recovered 8x8 Distort-driven quad warp; the remaining gaps are the exact warped UV orientation, the original RNG-driven grid state, and any `Landscape` model path
- the runtime now has an explicit mutable state root at `artifacts/runtime`, and the high-score screen already loads compact `ScoreA.dat`, `ScoreB.dat`, and `ScoreC.dat` overlays from there when present

Current note:

- upstream raylib has `SUPPORT_FILEFORMAT_TGA` disabled by default in `config.h`
- this repo enables `SUPPORT_FILEFORMAT_TGA=1` and `SUPPORT_FILEFORMAT_OGG=1` for the bundled raylib build so the runtime can use raylib's normal memory loaders directly

Useful commands:

```bash
zig build
zig build test
zig build run
zig build run -- debug
zig build run -- smoke
zig build run -- debug --archive-path artifacts/bin/SnailMail.dat
```

Notes:

- `zig build` installs `zig-out/bin/snail`
- `zig build run` now enters the default game path, shows the archive-backed loading screen, intro crawl, main menu, options menu, delivery-route map, high-score menu, and can enter the current tutorial or arcade level path
- `zig build run -- debug` opens the interactive archive browser and waits until you close it
- `zig build run -- smoke` opens the window briefly, loads texture and audio paths from the archive, and exits automatically for verification
- `zig build run` now defaults to a `1024x768` window, which keeps the original `4:3` presentation while staying larger than the original `640x480` windowed client; `debug` and `smoke` keep the wider tooling window
- windowed mode stays the development default until a saved runtime config exists; `--fullscreen` or a saved fullscreen preference in `SnailMail.cfg` can still start fullscreen
- `--runtime-dir` overrides the mutable state root for `SnailMail.cfg` and `ScoreA/B/C.dat`; the default is `artifacts/runtime`, and the port now loads and saves the raw config blob there while applying the recovered sound/music/fullscreen fields
- current level previews are still sequential approximations: the named `Path=` routes are now confirmed to resolve through a hardcoded `51`-entry table in the gameplay executable, and the original player update can enter a dedicated attachment-follow state on installed sampled path objects, but the exact name-to-template mapping and installer path are still under investigation
- the debug `Segments` view now carries all public authored attachment families through that scaffold, including the nonlinear kind-`42` family, and the gameplay runner now consumes built templates for live attachment progression, curved-surface camera basis, natural-end exit pose, a first width-based side-exit rule, and a dedicated `SUPERTRAMP` launch exit; the remaining gaps are the installed runtime attachment bank and more exact family-specific follow/exit behavior

Interactive controls for `zig build run -- debug`:

- `1`: texture browser
- `2`: audio browser
- `3`: `.x2` model browser
- `4`: object browser
- `5`: level browser
- `Left` / `Right`: cycle entries
- `Up` / `Down`: jump by 10 entries in texture, audio, model, and object modes
- `Up` / `Down` in level mode: step through the selected level's segment list
- `A` / `D` in level mode: move the deterministic runner left or right
- `W` / `S` in level mode: adjust runner speed
- `Space`: play current audio as a one-shot sound
- `Enter`: play current audio as a music stream
- `Space` in level mode: pause or resume the deterministic runner
- `S`: stop audio preview
- `F`: flip `V` texture coordinates in model and object modes
- `P`: pause or resume the active animation clip
- `R`: restart the active animation clip or reset the deterministic runner in level mode

## Current .x2 Understanding

The `.x2` files are not opaque binary data. The current parser and renderer show that representative files such as `X/SIGNSTOP.X2`, `X/PILLAR2.X2`, and `X/TURBO-BASE-000.X2` are text-based mesh files with:

- a leading `Frame <name> { ... }` block that contains one or more `Material` blocks
- a `MeshTextureCoords { ... }` block
- a final `Mesh <name> { ... }` block with vertex and face lists
- a trailing NUL byte at end of file

The current Zig loader mirrors the original RWG logic closely enough to render static meshes and animated frame families:

- `TextureFilename` entries are resolved as `X/<basename>.tga`
- the material list assigns one material index per face
- faces with `4; ...` are quads and are triangulated at runtime
- faces with non-`4` counts are treated as triangles

This behavior was cross-checked against the Binary Ninja database, Ghidra decompile, and the IDA output in [`artifacts/ida/SnailMail.RWG.c`](../../artifacts/ida/SnailMail.RWG.c)

Observed caveat:

- the final mesh block appears to omit a closing `}` in shipped assets, so the parser intentionally tolerates EOF after the face list

Animation is orchestrated separately by [`X/_ANIMATION.TXT`](../../artifacts/extracted/SnailMail.dat/X/_ANIMATION.TXT), which references multiple `.x2` files as frame sequences.

Current playback behavior:

- the runtime groups `.x2` files by family key, for example `turbo-bobalong`
- the numeric suffix in each filename, for example `000` through `004`, defines the keyframe sample positions
- `Duration:` and `Mode:` control clip length and playback mode
- the renderer interpolates vertex positions between compatible keyframes and updates the uploaded mesh buffers in place

Current caveat:

- `Trigger:` lists from `_ANIMATION.TXT` are not applied yet; the viewer currently follows the numbered keyframes plus `Duration:` and `Mode:`

## Current Simulation Read

The strongest current design lesson from replay behavior and the March 8 Frida captures is still the same:

- the rewrite should treat gameplay as a deterministic headless simulation with rendering layered on top
- replay playback appears to reuse the same underlying gameplay state transitions rather than a render-only camera path
- the fixed-step Zig runner is therefore scaffolding, not polish: it keeps the port aligned with the likely architecture of the original game

Current caveat:

- the runner is intentionally conservative and still not a full movement port; it now preserves lateral offset through attachment rows instead of snapping to the midpoint, but faithful floor following, template-bank-driven attachment-follow motion, off-track fall behavior, and exact ambient hazard spawn timing are still blocked on more runtime evidence from `SnailMail_unwrapped.exe`

## Non-Goals For Now

- redesigning core mechanics
- replacing original content with new authored formats
- building a conversion-heavy content pipeline before the runtime exists
