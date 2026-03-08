# Rewrite Plan

This directory captures the intended direction for the playable rewrite of Snail Mail.

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
- [`zig/src/main.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/main.zig)

Current behavior:

- the runtime opens a window
- reads [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) directly
- builds asset catalogs for the archive's `.tga`, `.ogg`, and `.x2` entries
- browses original textures directly from archive memory
- previews original OGGs as both one-shot sounds and music streams
- parses representative `.x2` files into mesh and material summaries

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

Interactive controls:

- `1`: texture browser
- `2`: audio browser
- `3`: `.x2` summary browser
- `Left` / `Right`: cycle entries
- `Up` / `Down`: jump by 10 entries
- `Space`: play current audio as a one-shot sound
- `Enter`: play current audio as a music stream
- `S`: stop audio preview

## Current .x2 Understanding

The `.x2` files are not opaque binary data. The current parser shows that representative files such as `X/SIGNSTOP.X2`, `X/PILLAR2.X2`, and `X/TURBO-BASE-000.X2` are text-based mesh files with:

- a leading `Frame <name> { ... }` block that contains one or more `Material` blocks
- a `MeshTextureCoords { ... }` block
- a final `Mesh <name> { ... }` block with vertex and face lists
- a trailing NUL byte at end of file

Observed caveat:

- the final mesh block appears to omit a closing `}` in shipped assets, so the parser intentionally tolerates EOF after the face list

Animation appears to be orchestrated separately by [`X/_ANIMATION.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/X/_ANIMATION.TXT), which references multiple `.x2` files as frame sequences.

## Non-Goals For Now

- redesigning core mechanics
- replacing original content with new authored formats
- building a conversion-heavy content pipeline before the runtime exists
