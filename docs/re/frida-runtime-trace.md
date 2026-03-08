# Frida Runtime Trace

This page describes the Frida harness for capturing the runtime evidence we still need from the original Windows game.

The script lives at [tools/frida/snailmail-runtime-trace.js](/Users/banteg/dev/banteg/snail-mail/tools/frida/snailmail-runtime-trace.js).

The Windows-side operational handoff lives at [windows-frida-handoff.md](windows-frida-handoff.md).

## Goal

The remaining static RE gap is no longer basic file formats. It is runtime behavior:

- when named `Path=` rows become live attachment probes and follow states
- how the player state evolves while those attachments stay active
- how ordinary player movement samples runtime cells and floor semantics outside attachment mode
- how often `Garbage:`, `Salt:`, and slug logic actually spawn entities
- when pickups and ring rows become live runtime entities or effects
- which row and cell positions those systems choose at runtime

The Frida script is intentionally narrow. It only hooks the points that answer those questions.

## Hook Set

Current hooks in the script:

- `0x437eb0` `normalize_level_runtime_fields`
  - logs the normalized runtime `Garbage:` and `Salt:` scalars
  - also records `mode_before`, `mode_after`, and the active-level flag bytes so tutorial-style runs do not get misreported as track id `7`
  - now also records the live track build flags and the active row window `[track_row_start, track_row_end)`
- `0x429ae0` `find_segment_path_index_by_name`
  - logs `Path=<name>` to runtime index resolution
  - emits a canonical path name from the recovered hardcoded table whenever the raw lookup buffer is not safely NUL-terminated
- `0x43b120` `update_player_track_movement_and_triggers`
  - emits sampled before and after player snapshots
  - records current runtime cell, attachment-active state, and follow-state progress on a rate-limited basis
  - now also records the current build-flag word seen by the active gameplay state
  - now includes the embedded follow-state summary, including template metadata, output position, orientation, and `offset_y`
  - this is a `thiscall` method, so the script now reads the player object from `ecx`
- `0x42c770` `try_enter_track_attachment_from_swept_motion`
  - logs attempted path-attachment entry with swept position and velocity
- `0x420c40` `begin_track_attachment_follow_state`
  - logs the actual transition into attachment-follow state
  - now emits both the full follow-state summary and the resolved attachment-template summary
- `0x420cb0` `update_track_attachment_follow_state`
  - emits sampled follow-state updates with current row, progress, and movement output
  - now includes template sample-count and width fields plus the follow-state output pose
- `0x43af60` `end_track_attachment_follow_state`
  - logs the point where the player drops back out of attachment-follow mode
  - this is also a `thiscall` method, and the script now prefers the embedded follow-state cell over the transient player cell so exit rows stay meaningful
- `0x43d4d0` `sample_track_floor_height_at_position`
  - logs sampled floor-query positions and the runtime cell chosen for that query
  - now also includes the runtime cell floor slot from `cell + 0x14`, which is the special height source for shipped tile `0x16`
- `0x43da80` `spawn_track_garbage_hazard`
  - logs garbage spawns with the chosen runtime cell
- `0x43d6c0` `spawn_track_health_pickup`
  - logs health pickup placement with the chosen runtime cell
- `0x43d890` `spawn_track_jetpack_pickup`
  - logs jetpack pickup placement with the chosen runtime cell
- `0x43df10` `spawn_track_ring_or_special_effect`
  - logs ring and special-effect dispatch with the chosen runtime cell and effect kind
- `0x441560` `spawn_salt_runtime_entity`
  - logs salt-pool spawns with the world position passed in
- `0x4417d0` `update_salt_hazard`
  - emits sampled live salt-slot positions and velocities so hazard motion can be reconstructed
- `0x441740` `deactivate_salt_runtime_entity`
  - logs the salt slot position and velocity when a live salt object is removed
- `0x43dc80` `spawn_slug_runtime_entity`
  - logs slug spawns with the chosen runtime cell

The script also calls `get_track_cell_row_index` at `0x447040` so cell-based events include a generated runtime row index when the call is safe.

## Output

The script writes one JSON object per line to a generated NDJSON file under `C:\share\snail\frida\`.

Current filename pattern:

```text
C:\share\snail\frida\snailmail-trace-YYYYMMDD-HHMMSS-<pid>.ndjson
```

It also mirrors the same JSON lines to standard output so live debugging still works without changing the payload format.

Event names currently emitted:

- `module_ready`
- `hooks_installed`
- `level_start`
- `path_lookup`
- `player_update`
- `attachment_probe`
- `attachment_begin`
- `attachment_update`
- `attachment_end`
- `floor_sample`
- `garbage_spawn`
- `health_pickup`
- `jetpack_pickup`
- `ring_effect`
- `salt_spawn`
- `salt_update`
- `salt_deactivate`
- `slug_spawn`

Important payload details:

- `level_start.selected_track_id` is only populated when the active-level pointer flags are set
- `level_start.mode_before` and `level_start.mode_after` are always recorded and are the correct fallback fields when the active-level pointer is absent
- `level_start.build_flags` is the live track-build mask that drives glyph normalization and several entity-spawn gates
- `level_start.track_row_start` and `level_start.track_row_end` are the current active spawn window used by the entity-population pass
- `path_lookup.path_name` is the preferred canonical name
- `path_lookup.path_name_raw` keeps the raw pointer read for debugging
- `path_lookup.path_name_from_index` is the table-derived name from the recovered `51`-entry path list
- `cell.flags` is the runtime per-cell flag dword read directly from `cell + 0x4`
- `cell.floor_height` is the runtime floor slot read from `cell + 0x14`
- `template_summary` captures the active attachment template record:
  - origin
  - kind
  - sample count
  - width or scale
  - subdivision count
  - sample-array pointers
  - current per-sample delta and length fields
- `follow_state_summary` captures the active attachment-follow state:
  - current sample index and progress
  - vertical offset
  - output pose
  - orientation-like vector fields
  - resolved template summary

If one hook becomes noisy, the script rate-limits it and emits a matching `*_suppressed` event once.

Once a capture exists, summarize it locally from the repo root:

```bash
uv run snail trace summary /path/to/snailmail-trace.ndjson
uv run snail trace plan
```

That converts the raw NDJSON into grouped counts for:

- normalized level-start scalars
- `Path=` name to index lookups
- sampled player updates and attachment lifecycle events
- attachment probes and follow-state transitions
- garbage, salt, slug, pickup, and ring-effect rows

The `trace plan` command uses the extracted corpus to rank good first-run targets:

- path-heavy segments and levels
- ring-heavy segments and levels
- no-fall-heavy segments and levels
- jetpack-off-heavy segments and levels
- salt-candidate segments with authored `&` rows
- authored-salt levels with explicit `&` rows
- high-garbage levels
- high-salt levels
- levels and segments with many `M` glyph rows, which are the current best static slug candidates

For the next capture, the new high-value questions are narrower:

- tile `0x16` rows:
  - does the logged `cell.floor_height` stay fixed at the builder-seeded value or change dynamically in live play
- attachment-follow updates:
  - how `follow_state_summary.output_position`, `offset_y`, and the template sample metadata evolve across entry, steady follow, and exit
- attachment exit:
  - whether the exit row or floor slot differs systematically by template kind

## Latest March 8 Read

The longer local capture at [`artifacts/frida/snailmail-trace-20260308-170041-12920.ndjson`](/Users/banteg/dev/banteg/snail-mail/artifacts/frida/snailmail-trace-20260308-170041-12920.ndjson) is the current best dynamic baseline.

Key facts from that run:

- `attachment_probe`: `1628`
- `attachment_begin`: `101`
- `attachment_update`: `4096`
- `attachment_end`: `44`
- `floor_sample`: `4096`
- `garbage_spawn`: `278`
- `health_pickup`: `10`
- `jetpack_pickup`: `2`
- `ring_effect`: `29`
- `salt_spawn`: `65`
- `salt_update`: `4096`
- `slug_spawn`: `180`

Useful confirmed tile mappings from that capture:

- attachment probes: runtime tile types `29` and `30`
- actual attachment-follow updates: runtime tile type `30`
- health pickups: runtime tile type `23`
- jetpack pickups: runtime tile type `25`
- slug spawns: runtime tile type `18`
- garbage spawns: dominated by runtime tile types `1` and `33`
- ring effects:
  - effect kind `4` mostly appeared on runtime tile types `2`, `3`, and `4`
  - effect kind `2` appeared on runtime tile types `8`, `9`, and `10`

One important operational note:

- that March 8 long capture predates the latest local `thiscall` fix for `player_update` and `attachment_end`
- the next Windows recapture should therefore use the current repo version of the script, not an older copied copy

## Current Recommended Targets

As of the current extracted corpus and parser state, `uv run snail trace plan --limit 3` recommends these first captures:

- path-heavy run: [`LEVELS/ARCADE028.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE028.TXT)
  - strongest current path target when repeated segment placements are counted as real playthrough exposure
  - `33` path rows across `20` path-bearing segment placements
- ring-heavy run: [`LEVELS/TUTORIAL.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT)
  - current top ring-tagged level
  - `12` authored ring rows across the tutorial chain
  - best first probe for confirming how `Ring=None`, `Ring=PowerUp`, `Ring=Explode`, and `Ring=Slow` surface in live runtime behavior
- no-fall run: [`LEVELS/ARCADE047.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE047.TXT)
  - current top level by explicit `NoFall` rows once repeated segment placements are counted
  - `286` `NoFall` rows, driven mostly by repeated trampoline-family segments
  - best first probe if you want to correlate trampoline-heavy authored rows with the now-recovered runtime `NoFall` lane at mask `0x100`
- jetpack-off run: [`LEVELS/ARCADE025.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE025.TXT)
  - current top level by repeated `JetPackOff` segment exposure
  - `3` explicit `JetPack=Off` rows in one short arcade flow
  - best first probe if you want to watch how the runtime behaves around authored jetpack suppression without mixing in large no-fall sections
- garbage-heavy run: [`LEVELS/ARCADE040.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE040.TXT)
  - current top garbage level
  - `Garbage:100`
- salt-heavy run: [`LEVELS/ARCADE039.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE039.TXT)
  - current top salt level
  - `Salt:100`
  - notable static clue: it has `0` explicit `&` rows, so it is the best first probe for the fallback salt branch on runtime tile kinds `1` and `15`
- authored salt level run: [`LEVELS/ARCADE037.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE037.TXT)
  - current top level by explicit `&` rows once repeated segment placements are counted
  - useful first probe if you want the densest authored-salt exposure in one short arcade flow
- clean authored salt tutorial run: [`LEVELS/TUTORIAL.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT)
  - still the best tutorial-grade authored-salt target
  - notable static clue: it has `Salt:0`, so it remains the cleanest first probe for authored salt placements that should resolve directly through runtime tile `0x22`
- authored salt segment run: [`SEGMENTS/TUTORIAL 8.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/SEGMENTS/TUTORIAL%208.TXT)
  - current top segment by explicit `&` rows
  - best static target for verifying the tile-family branch that feeds `spawn_salt_hazard`
- no-fall segment run: [`SEGMENTS/TRAMPOLINES.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/SEGMENTS/TRAMPOLINES.TXT)
  - current top segment by explicit `NoFall` rows
  - `84` no-fall-tagged rows in one segment
  - best static target if you want a concentrated trampoline or no-fall capture without full-level noise
- jetpack-off segment run: [`SEGMENTS/JETPACKOFF.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/SEGMENTS/JETPACKOFF.TXT)
  - current only segment with an explicit `JetPack=Off` annotation
  - best static target for isolating any runtime response to authored jetpack suppression
- slug-like run: [`LEVELS/ARCADE029.TXT`](/Users/banteg/dev/banteg/snail-mail/artifacts/extracted/SnailMail.dat/LEVELS/ARCADE029.TXT)
  - current top `M`-glyph-heavy level
  - useful first probe for the remaining slug and salt ambiguity

Regenerate the ranked lists after any parser or corpus changes instead of treating the recommendations above as permanent truth.

## Windows Usage

Attach to the real gameplay process, not the Reflexive wrapper. Prefer a locally generated [`SnailMail_unwrapped.exe`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail_unwrapped.exe) on the Windows machine and start it from its own binary directory so it can resolve adjacent game files correctly. If you only have the original shipped files, the Frida script also accepts [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG).

Generate the preferred gameplay target first when needed:

```bash
uv run snail unwrap
```

Spawn the game under Frida:

```bash
cd C:\path\to\repo\artifacts\bin
frida -f .\SnailMail_unwrapped.exe -l ..\..\tools\frida\snailmail-runtime-trace.js
```

If spawn still exits immediately, start the game normally from `artifacts\bin` and attach instead:

```bash
cd C:\path\to\repo
frida -n SnailMail_unwrapped.exe -l .\tools\frida\snailmail-runtime-trace.js
```

Watch the first console line from the script. It prints the exact NDJSON path it opened under `C:\share\snail\frida\`.

If you only have the wrapper path handy, do not attach to `SnailMail.exe`. In the common case the wrapper launches a separate gameplay process, so the script needs the gameplay image directly. Falling back to `SnailMail.RWG` is still valid if you have not generated the unwrapped image yet.

## First Capture Plan

Use a few focused capture runs instead of one giant noisy trace:

1. Start a level and quit quickly.
   - confirms `level_start`
   - records the normalized `Garbage:` and `Salt:` runtime scalars
2. Play a path-heavy level and deliberately enter at least one visible attachment section.
   - look for `path_lookup`, `attachment_probe`, `attachment_begin`, `attachment_update`, and `attachment_end`
   - this is the shortest path to proving how path templates become live follow-state transitions and how the player exits them
3. Play a level with visible garbage, salt, slugs, rings, and pickups.
   - compare `garbage_spawn`, `salt_spawn`, `salt_update`, `slug_spawn`, `ring_effect`, `health_pickup`, and `jetpack_pickup`
   - this should settle the remaining ambiguity around the salt-managed runtime pool and the entity dispatch rows

## Notes

- The script assumes the current 2006 gameplay image with preferred PE base `0x400000`.
- It resolves all hook addresses relative to the actual loaded module base at runtime.
- The hook set is designed for 32-bit Windows Frida because both [`SnailMail_unwrapped.exe`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail_unwrapped.exe) and [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG) are 32-bit PEs with the same gameplay code after unwrap.
- The current script does not decode every attachment-template field. It focuses on the row, tile type, world position, and attachment pointer so we can correlate dynamic behavior back to the existing static notes.
