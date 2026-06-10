# Snail Mail RE Notes

This repo is for decompiling and porting the 2006 Windows game bundle in [`artifacts/bin`](artifacts/bin).

## Current Findings

- [`SnailMail_unwrapped.exe`](artifacts/bin/SnailMail_unwrapped.exe) is the preferred gameplay reversing target. It is the reproducible decrypted gameplay image generated from the shipped wrapper assets.
- [`SnailMail.RWG`](artifacts/bin/SnailMail.RWG) is the original shipped wrapped gameplay image for the same runtime. Keep it around for provenance and wrapper-specific work.
- [`SnailMail.exe`](artifacts/bin/SnailMail.exe) is a 32-bit Windows GUI PE from June 28, 2006. It is the Reflexive launcher or wrapper layer rather than the gameplay runtime.
- [`SnailMail.dat`](artifacts/bin/SnailMail.dat) is a 27 MiB opaque container. It is not recognized as a standard archive by `binwalk` or `7z`, but it does contain embedded asset-like signatures such as `BMP`, `JPEG`, and zlib headers.
- [`tBass.dll`](artifacts/bin/tBass.dll) exports the legacy BASS audio API.
- [`ReflexiveArcade`](artifacts/bin/ReflexiveArcade) contains the Reflexive storefront and updater runtime, including `ReflexiveArcade.dll`.

## Repo Tooling

Use the repo CLI for repeatable inspection instead of ad hoc one-off shell commands:

```bash
uv run snail inspect
uv run snail inspect artifacts/bin/SnailMail.dat
uv run snail inspect --write reports/bundle.json
uv run snail unwrap --write-config artifacts/bin/ReflexiveArcade/RAW_002.decoded.txt
uv run snail archive manifest
uv run snail archive extract --output artifacts/extracted/SnailMail.dat
uv run snail format artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT
uv run snail format artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT
uv run snail trace summary /path/to/snailmail-trace.ndjson
uv run snail trace plan
uv run snail symbols
uv run snail screenshots compare artifacts/screenshots/snail-game-main_menu-000006-001.png artifacts/screenshots/reference-original/main-menu-new-game-selected--2026-03-10_01-35-25-36.png --search-offset 8 --search-scale 0.95:1.05:0.01
```

The command emits JSON with:

- file sizes and SHA-256 hashes
- Shannon entropy for opaque blobs
- common embedded signature offsets (`BMP`, `JPEG`, `PNG`, `RIFF`, zlib, etc.)
- PE metadata for executables and DLLs, including imports, sections, and export previews
- decoded archive metadata when the target is [`SnailMail.dat`](artifacts/bin/SnailMail.dat)

The archive subcommands add:

- `archive manifest`: a decoded `SnailMail.dat` index summary with extension and root counts plus entry previews
- `archive extract`: a real extractor for the archive, including payload decode and a generated `manifest.json`
- `unwrap`: a reproducible Reflexive unwrap pass that emits `SnailMail_unwrapped.exe` plus an optional decoded `RAW_002.wdt` config

The format parser adds:

- `format`: structured JSON for decoded `_OBJECT.TXT`, `SEGMENTS/*.TXT`, and `LEVELS/*.TXT` assets
- `trace summary`: structured JSON rollups for Frida NDJSON runtime captures
- `trace plan`: ranked level and segment candidates for the next runtime capture, including path-heavy, ring-heavy, no-fall, jetpack-off, authored-salt, and scalar-salt targets
- `symbols`: validation for the tracked Binary Ninja gameplay symbol manifest in `analysis/symbols/gameplay-functions.json`
- `screenshots compare`: writes normalized render/reference captures plus signed diff, absolute diff, and montage artifacts under `artifacts/screenshots/compare`

## Asset Format Notes

Browse the docs locally with `zensical serve`.

Verified archive and asset format notes live in [docs/original/asset-formats.md](docs/original/asset-formats.md).

The rewrite direction and runtime goals live in [docs/rewrite/index.md](docs/rewrite/index.md).
Use [docs/rewrite/remaining-work-checklist.md](docs/rewrite/remaining-work-checklist.md) for the active backlog, and use dated notes under `analysis/runtime/` for concrete parity audits and evidence trails.

Current static reverse-engineering notes for the hardcoded segment path system and track-runtime pipeline live in [docs/re/path-system.md](docs/re/path-system.md).

The tracked Binary Ninja symbol workflow lives in [docs/re/symbols.md](docs/re/symbols.md), with the version-controlled function manifest in `analysis/symbols/gameplay-functions.json`.

Executable bootstrap and obfuscation notes live in [docs/re/reflexive-wrapper.md](docs/re/reflexive-wrapper.md).

The Windows runtime trace harness for Frida lives in [docs/re/frida-runtime-trace.md](docs/re/frida-runtime-trace.md).

The Windows-agent runbook for collecting those captures lives in [docs/re/windows-frida-handoff.md](docs/re/windows-frida-handoff.md).

Confirmed asset families in [`SnailMail.dat`](artifacts/bin/SnailMail.dat):

- `.ogg` audio
- `.tga` textures
- `.txt` object, segment, and level definitions
- `.x2` text mesh or animation fragments
- an embedded `BASS.DLL`

The Zig runtime reads [`SnailMail.dat`](artifacts/bin/SnailMail.dat) directly and has a native game path plus an archive-backed debug browser. For live parity status, use [docs/rewrite/remaining-work-checklist.md](docs/rewrite/remaining-work-checklist.md).

Path-system evidence now shows that hardcoded `Path=` templates are gameplay data, not only visual data: `P/p` cells install sampled attachment pointers onto runtime track cells, and player movement can transition into attachment-follow state backed by those path objects. Current attachment parity details live in the rewrite backlog and dated runtime audit notes.

The raylib build in this repo enables TGA and OGG support explicitly so the runtime can consume the original asset formats directly from the archive.

## Native Tools Already Available

- `r2` and `rabin2` for PE inspection and disassembly
- `binwalk` and `7z` for container probing
- `objdump`, `strings`, and `file` for quick triage
- `zig build run` for the native Zig + raylib rewrite scaffold

## Runtime Commands

Use the Zig runtime to exercise original assets directly from [`SnailMail.dat`](artifacts/bin/SnailMail.dat):

```bash
zig build
zig build test
zig build run
zig build run -- debug
zig build run -- smoke
zig build run -- debug --archive-path artifacts/bin/SnailMail.dat
zig build run -- --runtime-dir artifacts/runtime
zig build run -- --fullscreen
```

Command behavior:

- `zig build` installs `zig-out/bin/snail`
- `zig build run` launches the default game path, shows the archive-backed loading screen, intro crawl, main menu, options menu, delivery-route map, high-score menu, and can enter the current tutorial or arcade level path
- `zig build run -- debug` opens the archive-backed debug browser
- `zig build run -- smoke` opens briefly, warms key asset paths, and exits for verification
- `zig build run` now defaults to a `1024x768` window, which keeps the original `4:3` presentation while staying larger than the original `640x480` windowed client; `debug` and `smoke` keep the wider tooling window
- windowed mode is still the intentional development default when no saved runtime config exists; `--fullscreen` or a saved fullscreen preference in `SnailMail.cfg` can still start fullscreen
- `--runtime-dir` selects the mutable runtime-state root, which defaults to `artifacts/runtime`
- `--start-phase main_menu` jumps directly into a game-path frontend screen for faster iteration
- `--start-mode postal|time-trial|challenge|tutorial [--start-route-index N]` enters a recovered mode-owned flow directly for visual and gameplay probes
- `--start-level-intro` launches the default tutorial through the frontend level-entry path, including the click-start intro state
- `--auto-dismiss-click-start` pairs with `--start-level-intro` to advance the click-start gate for automated captures
- `--debug-start-level LEVELS/TUTORIAL.TXT --debug-start-row 320.5 [--debug-start-lane 5.5]` loads a level shell directly at an arbitrary runtime row/lane for gameplay probes and screenshots
- `--screenshot-at intro:120` auto-captures a game-path frame into `artifacts/screenshots`; `F12` queues a manual screenshot during runtime
- `--hidden-window --timeout-seconds 10` runs raylib hidden and silent for offscreen capture or smoke work; hidden runs now require an explicit timeout so they cannot linger indefinitely
- the original executable reads and writes `SnailMail.cfg` plus `ScoreA.dat`, `ScoreB.dat`, and `ScoreC.dat`; the rewrite now uses the runtime root for those mutable files, loads and saves the raw `SnailMail.cfg` blob there, applies the recovered sound/music/fullscreen fields, and already loads compact score overlays from `ScoreA/B/C.dat`

Interactive controls for `zig build run -- debug`:

- `1`: texture browser
- `2`: audio browser
- `3`: `.x2` model browser
- `4`: object browser
- `5`: level browser
- `Left` / `Right`: cycle entries
- `Up` / `Down`: jump by 10 entries in texture, audio, model, and object modes
- `Up` / `Down` in level mode: step through the selected level's segment list
- `A` / `D` in level mode: move the deterministic runner left or right across the current track row
- `W` / `S` in level mode: speed up or slow down the deterministic runner
- `Space`: play current audio entry as a one-shot sound
- `Enter`: play current audio entry as a music stream
- `S`: stop audio preview
- `F`: flip `V` texture coordinates in model and object modes
- `P`: pause or resume the current animation clip
- `R`: restart the current animation clip

## Status Workflow

Use [docs/rewrite/remaining-work-checklist.md](docs/rewrite/remaining-work-checklist.md) for current priorities and known blind spots. Treat dated `analysis/runtime/*.md` notes as evidence-backed audit trails; when a dated audit contradicts older prose, prefer the newer audit and update the affected docs after the fix lands.
