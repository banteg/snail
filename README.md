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

## Asset Format Notes

Verified archive and asset format notes live in [`docs/asset-formats.md`](/Users/banteg/dev/banteg/snail-mail/docs/asset-formats.md).

The rewrite direction and runtime goals live in [`docs/rewrite/README.md`](/Users/banteg/dev/banteg/snail-mail/docs/rewrite/README.md).

Current confirmed asset families in [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat):

- `.ogg` audio
- `.tga` textures
- `.txt` scripts and object definitions
- `.x2` text mesh or animation fragments
- an embedded `BASS.DLL`

The Zig runtime currently reads [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) directly and renders `OBJECTS/FONT/FONT-MENU-HOVER.TGA` from the archive.
The raylib build in this repo enables TGA support explicitly because upstream raylib ships with `SUPPORT_FILEFORMAT_TGA` disabled by default.

## Native Tools Already Available

- `r2` and `rabin2` for PE inspection and disassembly
- `binwalk` and `7z` for container probing
- `objdump`, `strings`, and `file` for quick triage
- `zig build run` for the native Zig + raylib rewrite scaffold

## Immediate Next Targets

- diff the behavior of [`SnailMail.exe`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.exe) and [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG) to separate launcher code from gameplay code
- reverse the structure of [`SnailMail.dat`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.dat) and carve assets into named files
- identify how Reflexive purchase flow hooks into the actual game runtime
