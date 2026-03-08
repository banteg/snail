# Rewrite Plan

This section captures the intended direction for the playable rewrite of Snail Mail.

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

- [`build.zig`](/Users/banteg/dev/banteg/snail-mail/build.zig)
- [`build.zig.zon`](/Users/banteg/dev/banteg/snail-mail/build.zig.zon)
- [`zig/src/archive.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/archive.zig)
- [`zig/src/object.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/object.zig)
- [`zig/src/segment.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/segment.zig)
- [`zig/src/level.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/level.zig)
- [`zig/src/track.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/track.zig)
- [`zig/src/xanim.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/xanim.zig)
- [`zig/src/main.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/main.zig)

Current behavior:

- the runtime opens a window
- reads [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) directly
- builds asset catalogs for the archive's `.tga`, `.ogg`, `.x2`, `_OBJECT.TXT`, `SEGMENTS/*.TXT`, and `LEVELS/*.TXT` entries
- browses original textures directly from archive memory
- previews original OGGs as both one-shot sounds and music streams
- parses `.x2` meshes and renders them in a 3D preview using archive-backed textures
- parses [`X/_ANIMATION.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/X/_ANIMATION.TXT) and auto-plays matching `.x2` frame families with interpolated vertex animation
- parses `_OBJECT.TXT` quads and renders object previews in 3D using sibling TGA textures from the archive
- parses `LEVELS/*.TXT` and `SEGMENTS/*.TXT`, preserves typed row metadata such as `Path`, `Ring`, `Parcel`, `JetPack=Off`, `3DModel`, `NoFall`, and the post-row `*` flag, and renders a sequential 3D track preview with semantic markers
- resolves segment `3DModel=<name>.x` rows to matching `X/<NAME>.X2` meshes when those assets exist and instances them directly in the level preview
- runs model animation and the new level runner on a fixed `1/60` simulation clock instead of wall-clock render time
- includes a deterministic level runner that advances through the parsed track, samples row metadata, and exposes lane, cell, attachment, and recent-event state in the UI
- the level runner now distinguishes attachment probe rows from primary attachment-entry rows, mirroring the current runtime evidence that lowercase `p` mostly behaves like tile `29` probes while uppercase `P` is the normal tile `30` entry path
- the runner also consumes the authored gameplay-cell vocabulary directly, so `$`, `J`, `s`, `&`, `M`, parcel digits, ring rows, `NoFall`, and `JetPack=Off` now update deterministic runner counters instead of living only as preview markers
- the track loader now has an explicit no-model path for headless simulation tests, so gameplay coverage no longer depends on uploading decorative `.X2` meshes

Current note:

- upstream raylib has `SUPPORT_FILEFORMAT_TGA` disabled by default in `config.h`
- this repo enables `SUPPORT_FILEFORMAT_TGA=1` and `SUPPORT_FILEFORMAT_OGG=1` for the bundled raylib build so the runtime can use raylib's normal memory loaders directly

Useful commands:

```bash
zig build
zig build test
zig build run
zig build run -- --smoke-test
zig build run -- --archive-path artifacts/bin/SnailMail.dat
```

Notes:

- `zig build run` opens the interactive archive browser and waits until you close it
- `zig build run -- --smoke-test` opens the window briefly, loads texture and audio paths from the archive, and exits automatically for verification
- current level previews are still sequential approximations: the named `Path=` routes are now confirmed to resolve through a hardcoded `51`-entry table in the gameplay executable, `P/p` cells consume those indices through hardcoded path-template pairs, and the original player update can enter a dedicated attachment-follow state on those sampled path objects, but the exact name-to-template mapping is still under investigation

Interactive controls:

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

This behavior was cross-checked against the Binary Ninja database, Ghidra decompile, and the IDA output in [`artifacts/ida/SnailMail.RWG.c`](/Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail.RWG.c)

Observed caveat:

- the final mesh block appears to omit a closing `}` in shipped assets, so the parser intentionally tolerates EOF after the face list

Animation is orchestrated separately by [`X/_ANIMATION.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/X/_ANIMATION.TXT), which references multiple `.x2` files as frame sequences.

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

- the runner is intentionally conservative and still not a full movement port; faithful floor following, curve-accurate attachment-follow motion, off-track fall behavior, and hazard spawning are still blocked on more runtime evidence from `SnailMail_unwrapped.exe`

## Non-Goals For Now

- redesigning core mechanics
- replacing original content with new authored formats
- building a conversion-heavy content pipeline before the runtime exists
