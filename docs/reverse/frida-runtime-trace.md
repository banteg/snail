# Frida Runtime Trace

This page describes the Frida harness for capturing the runtime evidence we still need from the original Windows game.

The script lives at [tools/frida/snailmail-runtime-trace.js](/Users/banteg/dev/banteg/snail-mail/tools/frida/snailmail-runtime-trace.js).

## Goal

The remaining static RE gap is no longer basic file formats. It is runtime behavior:

- when named `Path=` rows become live attachment probes and follow states
- how often `Garbage:`, `Salt:`, and slug logic actually spawn entities
- which row and cell positions those systems choose at runtime

The Frida script is intentionally narrow. It only hooks the points that answer those questions.

## Hook Set

Current hooks in the script:

- `0x437eb0` `normalize_level_runtime_fields`
  - logs the normalized runtime `Garbage:` and `Salt:` scalars plus selected track id
- `0x429ae0` `find_segment_path_index_by_name`
  - logs `Path=<name>` to runtime index resolution
- `0x42c770` `try_enter_track_attachment_from_swept_motion`
  - logs attempted path-attachment entry with swept position and velocity
- `0x420c40` `begin_track_attachment_follow_state`
  - logs the actual transition into attachment-follow state
- `0x43da80` `spawn_track_garbage_hazard`
  - logs garbage spawns with the chosen runtime cell
- `0x441560` `spawn_salt_runtime_entity`
  - logs salt-pool spawns with the world position passed in
- `0x43dc80` `spawn_slug_runtime_entity`
  - logs slug spawns with the chosen runtime cell

The script also calls `get_track_cell_row_index` at `0x447040` so cell-based events include a generated runtime row index when the call is safe.

## Output

The script writes one JSON object per line to standard output.

Event names currently emitted:

- `module_ready`
- `hooks_installed`
- `level_start`
- `path_lookup`
- `attachment_probe`
- `attachment_begin`
- `garbage_spawn`
- `salt_spawn`
- `slug_spawn`

If one hook becomes noisy, the script rate-limits it and emits a matching `*_suppressed` event once.

## Windows Usage

Attach to the real gameplay process, not the Reflexive wrapper. The easiest path is to start [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG) directly on the Windows machine.

Spawn the game under Frida and save NDJSON output:

```bash
frida -f C:\path\to\SnailMail.RWG -l tools\frida\snailmail-runtime-trace.js > snailmail-trace.ndjson
```

Attach to an already running RWG process:

```bash
frida -n SnailMail.RWG -l tools\frida\snailmail-runtime-trace.js > snailmail-trace.ndjson
```

If you only have the wrapper path handy, do not attach to `SnailMail.exe` unless you have confirmed that `SnailMail.RWG` runs inside the same process. In the common case it is a separate process, so the script needs the RWG image directly.

## First Capture Plan

Use three focused capture runs instead of one long noisy trace:

1. Start a level and quit quickly.
   - confirms `level_start`
   - records the normalized `Garbage:` and `Salt:` runtime scalars
2. Play a segment with `P/p` path tiles.
   - look for `path_lookup`, then `attachment_probe`, then `attachment_begin`
   - this is the shortest path to proving how path templates become live follow-state transitions
3. Play a level with visible garbage, salt, or slugs.
   - compare `garbage_spawn`, `salt_spawn`, and `slug_spawn`
   - this should settle the remaining ambiguity around the salt-managed runtime pool

## Notes

- The script assumes the current 2006 RWG image with preferred PE base `0x400000`.
- It resolves all hook addresses relative to the actual loaded module base at runtime.
- The hook set is designed for 32-bit Windows Frida because [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG) is a 32-bit PE.
- The current script does not decode every attachment-template field. It focuses on the row, tile type, world position, and attachment pointer so we can correlate dynamic behavior back to the existing static notes.
