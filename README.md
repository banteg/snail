# Snail Mail RE Notes

This repo is for decompiling and rebuilding the 2006 Windows game bundle in [`artifacts/bin`](artifacts/bin).

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

## Asset Format Notes

Browse the docs locally with `zensical serve`.

Verified archive and asset format notes live in [docs/original/asset-formats.md](docs/original/asset-formats.md).

The rewrite direction and runtime goals live in [docs/rewrite/index.md](docs/rewrite/index.md).
The current verified versus fallback or scaffold ledger lives in [docs/rewrite/port-status.md](docs/rewrite/port-status.md).

Current static reverse-engineering notes for the hardcoded segment path system and track-runtime pipeline live in [docs/re/path-system.md](docs/re/path-system.md).

The tracked Binary Ninja symbol workflow lives in [docs/re/symbols.md](docs/re/symbols.md), with the version-controlled function manifest in `analysis/symbols/gameplay-functions.json`.

Executable bootstrap and obfuscation notes live in [docs/re/reflexive-wrapper.md](docs/re/reflexive-wrapper.md).

The Windows runtime trace harness for Frida lives in [docs/re/frida-runtime-trace.md](docs/re/frida-runtime-trace.md).

The Windows-agent runbook for collecting those captures lives in [docs/re/windows-frida-handoff.md](docs/re/windows-frida-handoff.md).

Current confirmed asset families in [`SnailMail.dat`](artifacts/bin/SnailMail.dat):

- `.ogg` audio
- `.tga` textures
- `.txt` object, segment, and level definitions
- `.x2` text mesh or animation fragments
- an embedded `BASS.DLL`

The Zig runtime currently reads [`SnailMail.dat`](artifacts/bin/SnailMail.dat) directly and provides an archive-backed browser for:

- `.tga` textures
- `.ogg` audio as both one-shot sounds and music streams
- `BACKGROUNDS/*.TXT` scripts plus their authored single-image or `_A`/`_B` split TGA layouts
- `.x2` mesh rendering and animation playback
- `OBJECTS/*/_OBJECT.TXT` 3D previews with archive-backed textures
- `LEVELS/*.TXT` and `SEGMENTS/*.TXT` parsing plus sequential 3D track previews with typed row semantics, hazard or pickup markers, and instanced segment `3DModel=` meshes where matching `.X2` assets exist
- a fixed-step level runner in level mode, so track stepping now happens on a deterministic simulation clock instead of render time
- a more original-shaped movement integrator in level mode, with a discrete `runtime_track_index` cursor plus fractional `movement_progress` and per-tick `movement_rate_scalar` instead of only a free-running row float
- a stricter gameplay-cell vocabulary in the Zig runtime, so the runner now distinguishes authored attachment tiles, trampoline rows, health, jetpack, garbage, salt, slug, ring, and parcel semantics instead of treating them as generic preview markers
- a preview path that now uses recovered runtime floor heights for cell slabs and gameplay markers, so ramp families and trampoline tile `0x16` no longer render as fully flat track
- a build-flags-aware runtime tile layer using the currently confirmed gameplay preset `0x00f5cfff`, so slug tiles respect their recovered gate and ambient garbage or salt fallback candidates on runtime tiles `0x01`, `0x0f`, and `0x15` are visible in the level preview and HUD
- deterministic runner-side encounter tracking for pickups, hazards, `NoFall`, `JetPack=Off`, and attachment entry or exit, with a model-free level-preview load path available for headless simulation tests
- a default `snail` path that now uses the original splash, intro-text, and menu assets and can hand off evidence-backed menu actions like `Tutorial`, `Challenge Mode`, `Help`, and `Credits`
- a default in-level camera that now follows the runner forward instead of reusing the debug orbit camera, making the level path much closer to a playable Turbo view
- the authored `Sample=` and `Message=` metadata from active level segments now surfaces in the default level path, so tutorial voice clips and their text prompts are no longer ignored there
- the default level path now also accepts mouse steering by mapping cursor motion onto the current lane bounds, which is closer to the tutorial’s intended control path than keyboard-only lane nudges
- the default level HUD now surfaces parcel progress and finish state, and `Enter` returns to the menu once the runner reaches the end of the authored level path
- the default front-end now uses decompile-backed menu labels and hierarchy: `New Game`, `High Scores`, `Options`, `Credits`, `Exit`, with a recovered `New Game` submenu of `Tutorial`, `Postal Mode`, `Time Trial`, `Challenge Mode`, `Help`, and `Back`
- `Help` now uses the shipped help background directly, while `INTRO/INTRO.TXT` and `INTRO/CREDITS.TXT` now share the recovered `SpaceRed` plus `INTROTEXT.OGG` text-screen flow; `Postal Mode`, `Time Trial`, `Challenge Mode`, and `Tutorial` now use the recovered mode-to-level handoff, while score presentation and later front-end progression still remain unresolved

Current static RE on the path system now also shows that the hardcoded `Path=` templates are not only visual: `P/p` cells install sampled attachment pointers onto runtime track cells, and the main player movement update can transition into a dedicated attachment-follow state backed by those path objects.

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
- `zig build run` launches the default game path, shows the archive-backed splash, intro crawl, and menu flow, and can enter the current tutorial or arcade level path
- `zig build run -- debug` opens the archive-backed debug browser
- `zig build run -- smoke` opens briefly, warms key asset paths, and exits for verification
- windowed mode is the intentional development default; `--fullscreen` is opt-in until the original fullscreen or config behavior is ported
- `--runtime-dir` selects the mutable runtime-state root, which defaults to `artifacts/runtime`
- the original executable reads and writes `SnailMail.cfg` plus `ScoreA.dat`, `ScoreB.dat`, and `ScoreC.dat`; the rewrite now uses the runtime root for those mutable files, and it already loads compact score overlays from `ScoreA/B/C.dat` there

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

Recent Frida evidence from the March 8 multi-level Windows capture is now consistent with that architecture:

- `mode 0` appeared five times in the postal-mode run
- `mode 4` appeared twice during replay playback
- `mode 1` appeared once in the challenge-mode run
- attachment probes hit runtime tile types `29` and `30`, but actual attachment-follow begins only occurred on tile type `30`
- slug spawns stayed pinned to tile type `18`
- garbage spawns were dominated by tile types `1` and `33`
- the new March 8 long capture also reinforced the port’s current attachment split: tile `29` behaves mostly like a probe lane, tile `30` dominates real follow-state updates, health uses tile `23`, jetpack uses tile `25`, and authored `$`, `J`, `s`, `&`, and `M` rows are now reflected directly in the Zig runner state

## Immediate Next Targets

- confirm whether `Trigger:` lists in `X/_ANIMATION.TXT` affect timing beyond the numbered frame interpolation already implemented
- confirm transform, winding, and material flags against more in-game RWG call sites
- keep moving the rewrite from viewer to gameplay runtime: the next useful work is faithful player motion plus actual ambient hazard population on top of the new deterministic runner scaffold, while the next hard wall is still curve-accurate attachment-follow, off-track fall behavior, and exact spawn timing semantics from `SnailMail_unwrapped.exe`
