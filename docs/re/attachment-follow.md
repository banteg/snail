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

This is the first strong static point where named `Path=` rows clearly affect generated track attachments rather than just parser metadata. The remaining unknowns are the exact `P/p` glyph-to-runtime-tile semantics and the fine details of which installed half is chosen in the `P/p` installer branch, not the overall authored-name bridge itself.

## How Attachments Reach The Player

The strong static chain from this bundle is:

- authored `Path=` name -> `find_segment_path_index_by_name` returns one of `51` hardcoded name-table indices
- `load_segment_definitions` stores that resolved public index on the parsed segment-row record at `+0x8bc`
- `populate_runtime_track_cells_from_segments` later reads that stored index and selects an installed attachment pair as `path_index * 336 + (game + 0xff2914 / 0xff29bc)`
- in that same installer branch, uppercase `P` becomes runtime tile `30` and lowercase `p` becomes runtime tile `29`, but the installed-bank root itself is chosen by a separate builder-state byte at `this + 2`, not directly by glyph case
- the generated row cells carry attachment flag bit `0x40` plus an owner pointer at `+0xa4`
- projection and entry then walk from the current row cell to that installed owner record and into the live template record at owner `+56`

Later, `update_subgoldy` can enter `try_enter_track_attachment_from_swept_motion`, but the entry test is against installed sampled geometry, not against row glyph metadata alone.

Recovered `update_subgoldy` entry split:

- when `player + 0x41d == 0`, the current-cell branch checks runtime tile `29` or `30` and calls `begin_track_attachment_follow_state` directly from that live row cell
- when `player + 0x41d != 0`, the same function instead probes installed entry through `try_enter_track_attachment_from_swept_motion`
- that swept probe is driven from the live current cell's installed-owner flags, not from a broader visited-row event pass
- the swept helper is therefore a separate re-entry path, not the generic current-row begin path

Recovered installed-entry behavior from `try_enter_track_attachment_from_swept_motion`:

- scans the installed sample array from tail to head instead of limiting the test to a source-row progress window
- rejects candidate samples whose world-up Y component (`sample + 0x14`) is negative
- applies the raw local sweep thresholds against the candidate pose:
  - `x` within `width / 2 +/- 0.3`
  - start `y >= -0.2`
  - start `z` within `[0, delta_length]`
  - end `y <= 0.001`

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
- `player + 0x44c` / `+0x44d` -> `attachment_exit_gate_a` / `attachment_exit_gate_b`

Current practical read of the thresholds in `update_subgoldy`:

- `attachment_exit_progress > 0.7` arms `attachment_exit_gate_a` and plays the first one-shot voice
- if `player + 0x2d8 == 0`, that same first gate also dispatches cutscene animation `5` once `world_y < -6`
- `attachment_exit_gate_b` is the deeper one-shot voice gate at `world_y < -7`
- the actual death selector remains the separate `world_y < -7 && death_active == 0` path that calls `initialize_subgoldy_death`

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
- kind `42` is the special nonlinear family used by both projection and live follow

That distinction matters because path-table slot `30` is the authored `WARP` name, path-table slot `42` is the authored `HALFPIPE` name, and runtime kind `42` is a separate field used by at least part of that live family. The constructor sweep still strongly matches `sub_429b20` to one kind-`42` constructor branch, but kind `42` is no longer safely describable as `WARP`-only. Android now tightens that further: its named `cRPath::BuildHalfPipe` and `cRPath::HalfPipePos` are strong structural matches for the Windows kind-`42` constructor and transform helper.

Android also shows that the nonlinear family is not monolithic there: `cRGame::LoadPaths` directly maps public slot `57` (`HALFPIPE`) to `cRPath::BuildHalfPipe` and slot `58` (`HALFPOLE`) to `cRPath::BuildHalfPole`, while `cRPathFollowGoldy::Traverse` has dedicated `HalfPipePos` and `HalfPolePos` branches. `WARP` is a separate public slot `37` in the same Android path registry, and it does not show up as the same builder family in the recovered `LoadPaths` body. That does not prove the exact Windows public-name mapping yet, but it does strongly argue that Windows public `HALFPIPE` and public `WARP` should not be collapsed into one authored family.

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

## First Path-Oracle Capture

The first focused path-oracle run from March 12, 2026 was useful even though it did not close the `HALFPIPE` gap yet.

What it did confirm:

- startup path resolution really does parse the live public table entries for both `HALFPIPE` and `WARP`
  - `HALFPIPE` was observed at public path index `42`
  - `WARP` was observed at public path index `30`
- the live installed owner record itself carries the template fields we care about for runtime capture
  - kind
  - sample count
  - primary/secondary sample-array pointers
- the builder-state byte at `this + 2` really matters in practice
  - level `26` was captured once with `bank_selector_byte = 1` and once with `bank_selector_byte = 0`
  - those two runs produced different installed attachment sets
- live attachment-follow in that capture hit these recovered families:
  - `START` -> kind `36`
  - `LOOPTHELOOP` -> kind `0`
  - `WIBBLE` -> kind `40`
  - `SLALOMBIG` -> kind `23`

What it did **not** show:

- no live attachment install or follow event for public path `HALFPIPE`
- no live attachment template with runtime kind `42`
- no live `WARP` follow despite the shared kind-`42` transform helper firing during startup or constructor-side work

So the current strongest read is:

- `HALFPIPE` is definitely parsed from shipped content at runtime
- this specific capture did not drive the player through a live installed `HALFPIPE` section
- kind `42` remained a runtime family that still needed a targeted live capture rather than more inference from this first pass

## Second Path-Oracle Capture

The second focused path-oracle run on March 12, 2026 closed the `HALFPIPE` gap.

High-confidence dynamic facts from [`snailmail-path-oracle-20260312-031147-9596.ndjson`](../../artifacts/frida/snailmail-path-oracle-20260312-031147-9596.ndjson):

- runtime level mode arg `7` (`ARCADE007`, `To Infinity!`) was active during the observed follow events
- `HALFPIPE` was installed live in both runtime installed-bank roots:
  - `ff2914`
  - `ff29bc`
- the installed `HALFPIPE` owner records in that run had:
  - runtime kind `42`
  - sample count `66`
  - owner row `165`
  - tile type `30` on the installed attachment rows
- live follow also began on `HALFPIPE` in both roots and produced `277` sampled `attachment_update` events per root

That capture materially changes the strongest current read:

- public path `HALFPIPE` definitely installs into the live nonlinear kind-`42` family
- runtime kind `42` is therefore not safely `WARP`-only
- `sub_429b20` still looks like one constructor for the kind-`42` family, but Android now makes it safer to describe that as a `HALFPIPE` / `HALFPOLE`-style nonlinear branch while leaving public `WARP` unresolved

What is still missing even after this capture:

- a clean live `attachment_end` interpretation for `HALFPIPE`
  - the local oracle now emits `follow_state_summary` on `attachment_end` from the pre-teardown snapshot so the next capture can answer this directly
- the exact authored-name-to-constructor split inside the kind-`42` family
- whether public `WARP` and public `HALFPIPE` are separate constructors producing the same runtime kind, or aliases into one constructor branch with different installer/bank choices

## Third Path-Oracle Capture

The next focused path-oracle run on March 12, 2026 did not add a new `HALFPIPE` or `WARP` family result, but it did validate the repaired `attachment_end` hook and gave one clean natural-end sample for `LOOPBOW`.

High-confidence facts from [`snailmail-path-oracle-20260312-033520-6240.ndjson`](../../artifacts/frida/snailmail-path-oracle-20260312-033520-6240.ndjson):

- two postal levels were observed:
  - `ARCADE007` / `To Infinity!` (`level_mode_arg = 7`, `bank_selector_byte = 1`)
  - `ARCADE009` / `Slugfest!` (`level_mode_arg = 9`, `bank_selector_byte = 0`)
- `HALFPIPE` again installed and followed live as runtime kind `42`
  - in this run it appeared on the `ff29bc` installed-bank root
  - it still used `66` samples
- `LOOPBOW` followed live as runtime kind `0` on the `ff2914` root
- `attachment_end` is now trustworthy enough to inspect pre-teardown follow state
  - all four observed end events in this capture were `LOOPBOW`
  - they exited with:
    - runtime kind `0`
    - sample index `51`
    - progress `0`
    - return value `0`

That `LOOPBOW` sample is the first clean dynamic evidence we have for a natural-end style attachment exit from the repaired oracle. It matches the static expectation that ordinary loop families run until the sample index reaches the template end, then fall into the natural-exit path rather than a side-exit branch.

What this capture still did **not** answer:

- no clean `attachment_end` for `HALFPIPE`
- no live public `WARP` follow
- no direct live mapping yet from public `WARP` to any specific nonlinear runtime branch

## Practical Read

This is the current high-confidence static evidence that:

- `Path=<name>` affects gameplay movement, not only visuals
- `P/p` rows install attachment corridors onto the generated runtime track
- the player update can transition from normal floor-following into a path-follow state backed by hardcoded sampled geometry

## Current Unknowns

Still missing:

- the detailed semantics of each path-template constructor beyond the current family grouping
- the exact constructor body for the named `HALFPIPE` slot
- the exact tile-id semantics around attachment entry, exit, and special-case movement reactions
- the remaining installer details around row-cell flag `0x40`, row-cell `+0xa4`, and the installed-owner/source-row chain

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

## Current Zig Port State

The current Zig port now goes materially farther than the old “row hint only” fallback:

- [`attachment_builders.zig`](../../zig/src/attachment_builders.zig) mirrors the public `51`-name `Path=` table and builds Zig-side templates for every public family
- the `Segments` view renders those built families directly, including the current nonlinear kind-`42` branch
- gameplay now consumes built templates for live attachment progression, world pose, camera forward/up, natural-end exit pose, a first width-based side-exit rule, and the dedicated `SUPERTRAMP` launch exit
- the current nonlinear kind-`42` path in both gameplay and the segment viewer now uses a decompile-backed local transform model derived from `compute_kind42_attachment_transform`, instead of the older circle-height approximation
- entry no longer keys only off raw authored row tags; the preview now derives a first installed attachment-row map from the runtime attachment tiles, current-row gameplay begin now stays on the direct `29/30` cell path, and swept installed re-entry only probes the live current row while `attachment_exit_pending` is set

That is still not the full Windows model.

Current Zig gaps that remain clearly open:

- the real installed runtime bank and owner-record chain
- the full swept local-frame entry test used by Windows
- the exact family-specific semantics inside the nonlinear kind-`42` family
- the exact installed-bank split between public names like `HALFPIPE` and `WARP`
