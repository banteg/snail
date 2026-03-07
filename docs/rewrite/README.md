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
- decodes `OBJECTS/FONT/FONT-MENU-HOVER.TGA` from the archive
- uploads it as a texture and draws it

Current note:

- upstream raylib has `SUPPORT_FILEFORMAT_TGA` disabled by default in `config.h`
- this repo enables `SUPPORT_FILEFORMAT_TGA=1` for the bundled raylib build so the runtime can use raylib's normal TGA loader directly

Useful commands:

```bash
zig build
zig build test
zig build run
zig build run -- --smoke-test
zig build run -- --archive-path artifacts/bin/SnailMail.dat
```

Notes:

- `zig build run` opens the interactive window and waits until you close it
- `zig build run -- --smoke-test` opens the window briefly and exits automatically for verification

## Non-Goals For Now

- redesigning core mechanics
- replacing original content with new authored formats
- building a conversion-heavy content pipeline before the runtime exists
