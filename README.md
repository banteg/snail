# Snail Mail RE Notes

This repo is for decompiling and rebuilding the 2006 Windows game bundle in [`artifacts/bin`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin).

## Current Findings

- [`SnailMail.exe`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.exe) is a 32-bit Windows GUI PE from June 28, 2006. It looks like the Reflexive launcher or wrapper layer rather than the heavy game runtime.
- [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG) is also a PE32 executable and imports `d3d8.dll` and `DINPUT8.dll`, which makes it a strong candidate for the core gameplay runtime.
- [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) is a 27 MiB opaque container. It is not recognized as a standard archive by `binwalk` or `7z`, but it does contain embedded asset-like signatures such as `BMP`, `JPEG`, and zlib headers.
- [`tBass.dll`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/tBass.dll) exports the legacy BASS audio API.
- [`ReflexiveArcade`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/ReflexiveArcade) contains the Reflexive storefront and updater runtime, including `ReflexiveArcade.dll`.

## Repo Tooling

Use the repo CLI for repeatable inspection instead of ad hoc one-off shell commands:

```bash
uv run snail inspect
uv run snail inspect artifacts/bin/SnailMail.dat
uv run snail inspect --write reports/bundle.json
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail format artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT
uv run snail format artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT
uv run snail trace summary snailmail-trace.ndjson
uv run snail trace plan
```

The command emits JSON with:

- file sizes and SHA-256 hashes
- Shannon entropy for opaque blobs
- common embedded signature offsets (`BMP`, `JPEG`, `PNG`, `RIFF`, zlib, etc.)
- PE metadata for executables and DLLs, including imports, sections, and export previews
- decoded archive metadata when the target is [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat)

The archive subcommands add:

- `archive manifest`: a decoded `SnailMail.dat` index summary with extension and root counts plus entry previews
- `archive extract`: a real extractor for the archive, including payload decode and a generated `manifest.json`

The format parser adds:

- `format`: structured JSON for decoded `_OBJECT.TXT`, `SEGMENTS/*.TXT`, and `LEVELS/*.TXT` assets
- `trace summary`: structured JSON rollups for Frida NDJSON runtime captures
- `trace plan`: ranked level and segment candidates for the next runtime capture, including path-heavy, ring-heavy, authored-salt, and scalar-salt targets

## Asset Format Notes

Verified archive and asset format notes live in [`docs/asset-formats.md`](/Users/banteg/dev/banteg/snail-mail/docs/asset-formats.md).

The rewrite direction and runtime goals live in [`docs/rewrite/README.md`](/Users/banteg/dev/banteg/snail-mail/docs/rewrite/README.md).

Current static reverse-engineering notes for the hardcoded segment path system and track-runtime pipeline live in [`docs/reverse/path-system.md`](/Users/banteg/dev/banteg/snail-mail/docs/reverse/path-system.md).

The Windows runtime trace harness for Frida lives in [`docs/reverse/frida-runtime-trace.md`](/Users/banteg/dev/banteg/snail-mail/docs/reverse/frida-runtime-trace.md).

Current confirmed asset families in [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat):

- `.ogg` audio
- `.tga` textures
- `.txt` object, segment, and level definitions
- `.x2` text mesh or animation fragments
- an embedded `BASS.DLL`

The Zig runtime currently reads [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) directly and provides an archive-backed browser for:

- `.tga` textures
- `.ogg` audio as both one-shot sounds and music streams
- `.x2` mesh rendering and animation playback
- `OBJECTS/*/_OBJECT.TXT` 3D previews with archive-backed textures
- `LEVELS/*.TXT` and `SEGMENTS/*.TXT` parsing plus sequential 3D track previews with typed row semantics, hazard or pickup markers, and instanced segment `3DModel=` meshes where matching `.X2` assets exist

Current static RE on the path system now also shows that the hardcoded `Path=` templates are not only visual: `P/p` cells install sampled attachment pointers onto runtime track cells, and the main player movement update can transition into a dedicated attachment-follow state backed by those path objects.

The raylib build in this repo enables TGA and OGG support explicitly so the runtime can consume the original asset formats directly from the archive.

## Native Tools Already Available

- `r2` and `rabin2` for PE inspection and disassembly
- `binwalk` and `7z` for container probing
- `objdump`, `strings`, and `file` for quick triage
- `zig build run` for the native Zig + raylib rewrite scaffold

## Runtime Commands

Use the Zig runtime to exercise original assets directly from [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat):

```bash
zig build
zig build test
zig build run
zig build run -- --smoke-test
```

Interactive controls:

- `1`: texture browser
- `2`: audio browser
- `3`: `.x2` model browser
- `4`: object browser
- `5`: level browser
- `Left` / `Right`: cycle entries
- `Up` / `Down`: jump by 10 entries in texture, audio, model, and object modes
- `Up` / `Down` in level mode: step through the selected level's segment list
- `Space`: play current audio entry as a one-shot sound
- `Enter`: play current audio entry as a music stream
- `S`: stop audio preview
- `F`: flip `V` texture coordinates in model and object modes
- `P`: pause or resume the current animation clip
- `R`: restart the current animation clip

## Immediate Next Targets

- confirm whether `Trigger:` lists in `X/_ANIMATION.TXT` affect timing beyond the numbered frame interpolation already implemented
- confirm transform, winding, and material flags against more in-game RWG call sites
- continue tracing the hardcoded `Path=` route system from `SnailMail.RWG`, especially the exact name-to-template mapping and attachment-entry tile semantics, so level previews can move from sequential blockouts to faithful lane geometry and eventually drive gameplay
