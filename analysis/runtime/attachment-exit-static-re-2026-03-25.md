# Attachment Exit Static RE Packet 2026-03-25

This packet is evidence-capped and static-RE only.

Do not replace attachment-exit gameplay semantics from this packet alone.
Wide Windows capture is suspended on this host due to system hangs on broader probe sets.

## Boundary

- phase: `re`
- classification: evidence-capped static RE only
- owner boundary: attachment-exit carryover and retirement only
- safe-to-code boundary: none for gameplay semantics

## Locked Runtime Families

Keep these as separate families in notes and code:

### 1. Terminal detach with no pending-exit path

- clean `HalfPipe` terminal detach
- no `attachment_end`
- no `attachment_exit_pending`
- no nonzero `post_follow_value_a` or `post_follow_value_b`

### 2. Short in-place pending clears

- pending window starts
- player remains in attachment-family flow
- pending clears in place without a fresh `attachment_begin`
- observed on shorter kind-`45` and kind-`16` windows

### 3. Long pending windows retired by next reattach

- pending window survives detached skim time
- first reattached frame after fresh `attachment_begin` clears pending
- observed across `HalfPipe` and Challenge attachment families

## Field Table

### `player + 0x42c` / `post_follow_value_a`

- writer:
  - `end_track_attachment_follow_state`
- confirmed consumer:
  - `update_cameraman`
- current read:
  - real camera carryover input while `attachment_exit_pending` is live

### `player + 0x430` / `post_follow_value_b`

- writer:
  - `end_track_attachment_follow_state`
- consumer:
  - unresolved in stable runtime evidence
- current read:
  - do not assign gameplay semantics yet

### `player + 0x44c` / `attachment_exit_gate_a`

- writers:
  - active update-side threshold logic
- current read:
  - marks progress into the longer pending window family

### `player + 0x44d` / `attachment_exit_gate_b`

- writers:
  - fall-threshold side path
- current read:
  - still consistent with the negative-`world_y` fall-side interpretation

## Clear-Site Table

- `0x43ce75`
  - confirmed jetpack-only late clear
- `0x43bf6f`
  - bounded static clear candidate for grounded snap or in-place retirement
- `0x43c06d`
  - bounded static clear candidate for grounded snap or in-place retirement
- `0x43c3ea`
  - bounded static clear candidate for trampoline or landing retirement

## Next Static RE Questions

- build the writer or consumer table for `0x42c`, `0x430`, `0x44c`, and `0x44d`
- map each clear site to one of the three locked runtime families
- determine whether `post_follow_value_b` is:
  - an unconsumed seed in the stable observed window
  - a rarer consumer outside the stable runtime profile
  - or a field that only matters in a still-unreached attachment family

## Hard Rule

No Zig attachment-exit semantic replacement in this batch.
Only evidence-backed naming or comment cleanup is allowed until `post_follow_value_b` or the remaining retirement winner closes statically.
