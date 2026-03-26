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
  - `begin_post_follow_carryover` seeds it from the cached follow carryover slot before the pending window starts

### `player + 0x430` / `post_follow_value_b`

- writer:
  - `end_track_attachment_follow_state`
- consumer:
  - unresolved in stable runtime evidence
- current read:
  - do not assign gameplay semantics yet
  - bounded static RE on `begin_post_follow_carryover`, `update_subgoldy`, and `update_cameraman` still does not show a direct post-handoff consumer outside the initial carryover write
  - the March 26 tracked-export sweep strengthens that negative result:
    - `begin_post_follow_carryover` writes `player + 0x430` from `player + 0x388 + 0x98` or zero
    - `update_subgoldy` does not directly read `player + 0x430` in the bounded retirement families
    - `update_cameraman` reads `player + 0x42c` while `attachment_exit_pending` is live, but does not read `player + 0x430`

### `player + 0x44c` / `attachment_exit_gate_a`

- writers:
  - active update-side threshold logic
- current read:
  - `update_subgoldy` arms it once `attachment_exit_progress > 0.7`
  - it marks progress into the longer pending window family and gates the first one-shot voice path

### `player + 0x44d` / `attachment_exit_gate_b`

- writers:
  - fall-threshold side path
- current read:
  - `update_subgoldy` arms it once `world_y < -7.0` during the pending window
  - still consistent with the negative-`world_y` fall-side interpretation

## Clear-Site Table

- `0x43ce75`
  - confirmed jetpack-only late clear
- `0x43bf6f`
  - bounded grounded snap clear inside `update_subgoldy`
  - requires no active follow, `world_y` in the narrow ground band, and a non-open cell family
- `0x43c06d`
  - bounded generic snap or in-place retirement inside `update_subgoldy`
  - sits on the no-hidden-roof or forced-floor lane that also zeroes vertical speed and resets `world_y` to the ground band
- `0x43c3ea`
  - bounded trampoline landing retirement inside `update_subgoldy`
  - tile family `22` bounce path; clears pending, seeds bounce vertical speed, and leaves the separate bounce marker armed

## Next Static RE Questions

- build the writer or consumer table for `0x42c`, `0x430`, `0x44c`, and `0x44d`
- map each clear site to one of the three locked runtime families
- determine whether `post_follow_value_b` is:
  - an unconsumed seed in the stable observed window
  - a rarer consumer outside the stable runtime profile
  - or a field that only matters in a still-unreached attachment family
- determine whether any helper outside the bounded `begin_post_follow_carryover` / `update_subgoldy` / `update_cameraman` set reads `post_follow_value_b` directly
- if no such helper surfaces, treat `post_follow_value_b` as a rarer-family or dormant carryover lane rather than assuming the common pending-exit path consumes it

## Hard Rule

No Zig attachment-exit semantic replacement in this batch.
Only evidence-backed naming or comment cleanup is allowed until `post_follow_value_b` or the remaining retirement winner closes statically.
