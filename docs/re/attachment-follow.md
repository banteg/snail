# Attachment Follow State

The hardcoded path templates are not only visual. They feed a real player-follow state machine.

## First Confirmed Path Consumer

Inside `rebuild_track_runtime_from_segments`:

- the builder calls a missing `populate_runtime_track_cells_from_segments` stage after laying out the segment rows
- later consumers prove that stage installed:
  - row-cell attachment flag bit `0x40`
  - a row-cell owner pointer at `+0xa4`
  - an installed attachment record whose `+56` points at the live template
- `project_position_onto_track_attachment` chooses the active sample by `current_row - owner_row`, so the runtime clearly uses an installed owner/source-row chain rather than raw parser metadata

This is the first strong static point where named `Path=` rows clearly affect generated track attachments rather than just parser metadata, but this package does **not** yet prove the exact `P/p` glyph-to-runtime-tile mapping or the final authored-name-to-bank-slot bridge.

## How Attachments Reach The Player

The strong static chain from this bundle is:

- authored `Path=` name -> `find_segment_path_index_by_name` returns one of `51` hardcoded name-table indices
- a still-missing installer stage turns that authored index into installed runtime attachment records
- the generated row cells carry attachment flag bit `0x40` plus an owner pointer at `+0xa4`
- projection and entry then walk from the current row cell to that installed owner record and into the live template record at owner `+56`

Later, `update_subgoldy` can enter `try_enter_track_attachment_from_swept_motion`, but the entry test is against installed sampled geometry, not against row glyph metadata alone.

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
- `+0x04`: active attachment-template pointer
- `+0x08`: owner attachment-runtime record
- `+0x0c`: current segment index
- `+0x10`: progress within the current sampled segment
- `+0x14`: local height above the attachment surface
- `+0x18..+0x28`: live pose/orientation intermediates updated each tick
- `+0x2c`: interpolated output position written by `update_track_attachment_follow_state`
- `+0x38`: player pointer

Recovered begin-state behavior from `begin_track_attachment_follow_state`:

- sets the active flag to `1`
- stores the selected attachment pointer from runtime cell `+0x38`
- stores the owner attachment-runtime record
- zeros the segment index
- seeds progress from `world_z - cell_anchor_z`
- seeds local height from `world_y - 0.49`
- stores the player pointer
- copies a row-derived scalar into the live template record at `+0x98` through `get_track_cell_row_index`

Recovered end-state behavior from `end_track_attachment_follow_state`:

- copies `attachment->+0x98` into `player + 0x430`
- copies `player + 0x3a0` into `player + 0x42c`
- clears the active flag at `player + 0x384`
- sets `player + 0x41d = 1`
- seeds `player + 0x424` from current player `z`
- clears `player + 0x434`, `player + 0x44c`, and `player + 0x44d`

For the trace schema and partial Binary Ninja typing, those exit-side fields are intentionally named conservatively:

- `player + 0x424` -> `attachment_exit_anchor_z`
- `player + 0x42c` -> `post_follow_value_a`
- `player + 0x430` -> `post_follow_value_b`
- `player + 0x434` -> `attachment_exit_progress`
- `player + 0x438` -> `attachment_exit_progress_step`
- `player + 0x44c` / `+0x44d` -> `follow_effect_gate_a` / `follow_effect_gate_b`

Those names describe stable behavior without overcommitting to the final gameplay meaning yet.

## March 8 Dynamic Capture

The long local capture at [`artifacts/frida/snailmail-trace-20260308-170041-12920.ndjson`](../../artifacts/frida/snailmail-trace-20260308-170041-12920.ndjson) materially tightened the attachment picture.

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

- the live record pointer uses the sampled point array at template `+0x5c`
- each sampled point record is `0xa8` bytes
- the current sample delta length is read from sampled point `+0x8c`
- the current output position is written to follow-state `+0x2c`
- the update terminates the follow state when the sample index reaches the template end
- special-case movement branches still exist for attachment kinds `0x1f` and `0x2a`
- the mid/end row-cell writes in the special branch pull their payloads from the installed runtime record reached through the live source row, not from template `+0xa0/+0xa4` directly

The newer Windows-only package also tightened two family reads:

- kind `31` is the dedicated `SUPERTRAMP` launch-exit family
- kind `42` is the special nonlinear `WARP`-like branch used by both projection and live follow

That distinction matters because path-table slot `30` is still the authored `WARP` name, while runtime kind `42` is a separate field and currently the strongest match for that missing constructor family.

Important caveat for this specific March 8 capture:

- `attachment_end` still reflected the pre-fix hook and reported the sentinel player cell (`tile_type = 32`, row `-6558`) instead of the embedded follow-state cell
- the local Frida script has now been corrected to read the player from `ecx` and prefer the follow-state cell on exit, so the next capture should produce a real end-row signal

## March 8 Evening Capture

The longer evening capture at [`artifacts/frida/snailmail-trace-20260308-204003-8604.ndjson`](../../artifacts/frida/snailmail-trace-20260308-204003-8604.ndjson) broadened the live attachment coverage substantially.

High-confidence attachment facts from that run:

- `attachment_begin`: `120`
- `attachment_probe`: `707`
- `attachment_update`: `4096`
- `attachment_end`: `14`
- attachment probes still split across runtime tiles `29` and `30`
- actual attachment-follow updates still overwhelmingly stay on runtime tile `30`

The dynamic template summaries now give a stable live family table:

- kind `36` -> `27` samples, subdivision count `8`
- kind `35` -> `16` samples, subdivision count `3`
- kind `33` -> `16` samples, subdivision count `3`
- kind `34` -> `16` samples, subdivision count `3`
- kind `39` -> `45` samples, subdivision count `4`
- kind `32` -> `70` samples, subdivision count `4`
- kind `17` -> `30` samples, subdivision count `3`
- kind `0` -> `51` or `32` samples, subdivision count `3` or `4`
- kind `42` -> `66` samples, subdivision count `8`
- kind `16` -> `22` samples, subdivision count `4`
- kind `28` -> `30` samples, subdivision count `4`
- kind `29` -> `27` samples, subdivision count `4`
- kind `40` -> `32` samples, subdivision count `8`
- kind `45` -> `52` samples, subdivision count `3`

Representative live rows from that run:

- row `4` -> kind `36`, sample count `27`
- row `40` -> kind `28`, sample count `30`
- row `85` -> kind `29`, sample count `27`
- row `299` -> kind `34`, sample count `16`
- row `331` -> kind `35`, sample count `16`
- row `339` -> kind `39`, sample count `45`
- row `516` -> kind `32`, sample count `70`
- row `606` -> kind `42`, sample count `66`
- row `1229` -> kind `45`, sample count `52`

The same run also confirmed a useful live split in vertical behavior:

- many families begin with `offset_y = 0` and an output `y` close to the ordinary player ride height
- kinds `34`, `35`, `39`, and `45` clearly start with positive `offset_y` and elevated output `y`, which makes them good first targets when reconstructing vertical path motion in Zig

Operational caveat:

- that evening capture still used the older grid-cell summarizer, so `player_update` and `floor_sample` cell rows are not trustworthy there
- the attachment template and follow-state summaries themselves are still useful, and the local Frida script now fixes the gameplay-grid versus row-cell split for the next recapture

## Practical Read

This is the current high-confidence static evidence that:

- `Path=<name>` affects gameplay movement, not only visuals
- `P/p` rows install attachment corridors onto the generated runtime track
- the player update can transition from normal floor-following into a path-follow state backed by hardcoded sampled geometry

## Current Unknowns

Still missing:

- the exact initialization path from the hardcoded `51`-name table to concrete runtime template slots
- the detailed semantics of each path-template constructor beyond the current family grouping
- the exact constructor body for the named `WARP` slot, even though runtime kind `42` is now the best candidate for that family
- the exact tile-id semantics around attachment entry, exit, and special-case movement reactions
- the exact installer that sets row-cell flag `0x40`, row-cell `+0xa4`, and the installed-owner/source-row chain

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
