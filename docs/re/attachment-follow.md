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
