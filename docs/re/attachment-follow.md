# Attachment Follow State

The hardcoded path templates are not only visual. They feed a real player-follow state machine.

## First Confirmed Path Consumer

Inside `rebuild_track_runtime_from_segments`:

- the builder copies the parsed row `Path=` index into runtime `+0x5ccb68`
- `P` becomes runtime tile type `0x1e`
- `p` becomes runtime tile type `0x1d`
- the `P/p` branch indexes hardcoded path-template pairs at:
  - `arg1 + 0xff2914`
  - `arg1 + 0xff29bc`
- the selected template record is stored on the track-grid cell and then propagated into runtime-cell attachment pointers for neighboring rows

This is the first strong static point where named `Path=` rows clearly affect generated track attachments rather than just parser metadata.

## How Attachments Reach The Player

Inside the `P/p` branch of `rebuild_track_runtime_from_segments`:

- the selected hardcoded path-template record is written to the track cell at `+0x3bfb00`
- the record's neighbor count at `+0x48` determines how many runtime cells receive attachment flags
- those runtime cells get flag `0x40` first and then `0x80` for the second attachment lane
- the same pass stores attachment pointers into runtime `+0x5ccb6c` and `+0x5ccb70`

Later, `update_player_track_movement_and_triggers` checks those flags on the current runtime cell and calls `try_enter_track_attachment_from_swept_motion` on the corresponding attachment pointer.

## Follow-State Functions

The current chain looks like this:

1. `begin_track_attachment_follow_state`
2. `try_enter_track_attachment_from_swept_motion`
3. `update_track_attachment_follow_state`
4. `end_track_attachment_follow_state`

Related helper:

- `is_point_inside_track_attachment` is a cheaper point-membership predicate over the same sampled path object

## Recovered Follow-State Layout

The current high-confidence follow-state layout is:

- `+0x00`: active flag
- `+0x04`: active attachment-template record pointer
- `+0x08`: source runtime cell pointer
- `+0x0c`: current sample index
- `+0x10`: progress within the current sampled segment
- `+0x14`: vertical offset seed from `world_y - 0.49`
- `+0x18..+0x28`: orientation-like values updated each tick
- `+0x2c`: interpolated output position written by `update_track_attachment_follow_state`
- `+0x38`: player pointer

Recovered begin-state behavior from `begin_track_attachment_follow_state`:

- sets the active flag to `1`
- stores the selected attachment pointer from runtime cell `+0x38`
- stores the source runtime cell pointer
- zeros the sample index
- seeds progress from `world_z - cell_anchor_z`
- seeds vertical offset from `world_y - 0.49`
- stores the player pointer
- copies a row-derived value into `attachment + 0x98` through `get_track_cell_row_index`

Recovered end-state behavior from `end_track_attachment_follow_state`:

- copies `attachment->+0x98` into `player + 0x430`
- copies `player + 0x3a0` into `player + 0x42c`
- clears the active flag at `player + 0x384`
- sets `player + 0x41d = 1`
- seeds `player + 0x424` from current player `z`
- clears `player + 0x434`, `player + 0x44c`, and `player + 0x44d`

## March 8 Dynamic Capture

The long local capture at [`artifacts/frida/snailmail-trace-20260308-170041-12920.ndjson`](/Users/banteg/dev/banteg/snail-mail/artifacts/frida/snailmail-trace-20260308-170041-12920.ndjson) materially tightened the attachment picture.

High-confidence dynamic facts from that run:

- `attachment_probe` fired on runtime tile types `29` and `30`
- `attachment_begin` fired `101` times, `100` of them on tile type `30`
- `attachment_update` fired `4096` times and only reported tile type `30`
- the active attachment rows in this capture were `4`, `91`, `128`, `165`, `442`, and `479`
- the observed attachment kinds on those rows were:
  - row `4` -> kind `36`
  - rows `91`, `128`, `442`, `479` -> kind `16`
  - row `165` -> kind `42`

The same run also confirmed the follow-state update shape recovered from `update_track_attachment_follow_state`:

- `follow_sample_index` advances monotonically until the current segment length is exhausted
- `follow_progress` wraps back below `1.0` when the sample index increments
- the traced `effect_scale` argument tracks the per-tick path factor that gets scaled by the current sample length

Representative row `442` progression from the trace:

- sample `0` progressed through `0.125`, `0.220`, `0.318`, ..., `0.952`
- then wrapped to sample `1` at progress `0.066`
- then continued through sample `1` and into sample `2`

That matches the static control flow in `update_track_attachment_follow_state`, where the function adds the scaled path factor to the stored progress, advances the sample index on overflow, and interpolates against the neighboring sample records.

Additional static detail from `update_track_attachment_follow_state`:

- the live record pointer uses the sampled point array at attachment `+0x5c`
- each sampled point record is `0xa8` bytes
- the current sample delta length is read from sampled point `+0x8c`
- the current output position is written to follow-state `+0x2c`
- the update terminates the follow state when the sample index reaches the template end
- special-case movement branches still exist for attachment kinds `0x1f` and `0x2a`

Important caveat for this specific March 8 capture:

- `attachment_end` still reflected the pre-fix hook and reported the sentinel player cell (`tile_type = 32`, row `-6558`) instead of the embedded follow-state cell
- the local Frida script has now been corrected to read the player from `ecx` and prefer the follow-state cell on exit, so the next capture should produce a real end-row signal

## Practical Read

This is the current high-confidence static evidence that:

- `Path=<name>` affects gameplay movement, not only visuals
- `P/p` rows install attachment corridors onto the generated runtime track
- the player update can transition from normal floor-following into a path-follow state backed by hardcoded sampled geometry

## Current Unknowns

Still missing:

- the exact initialization path from the hardcoded path-name table to the path-template pair tables
- the detailed semantics of each path-template constructor beyond the current family grouping
- the exact constructor site for the named `WARP` slot
- the exact tile-id semantics around attachment entry, exit, and special-case movement reactions

## Practical Impact On The Rewrite

What the rewrite can already do confidently:

- parse `SEGMENTS/*.TXT` and `LEVELS/*.TXT`
- mirror the text metadata fields and row flags
- build a sequential blockout from segment rows
- attach semantic markers such as parcels, rings, models, and no-fall rows

What still needs more RE before the Zig runtime can match the original course shape:

- how each named `Path=` row maps onto the hardcoded template-pair tables
- how the original runtime samples those templates for player movement, object placement, and camera behavior
- which tile ids and row markers trigger attachment entry and exit versus ordinary floor-following
