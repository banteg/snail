# begin_post_follow_carryover @ 0x43af60

Exact match: `100%`, `20/20` instructions.

This is the producer for the post-follow camera exit lanes:

- if follow is active, player+0x42c receives `follow_state.orientation_b`
- player+0x430 receives the raw 32-bit value from
  `follow_state.template_record+0x98`
- follow is then deactivated, `attachment_exit_pending` is set, the exit
  anchor z is captured from `position.z`, and the exit gates/progress reset

2026-07-14 consolidation: the scratch now uses shared `player.h`'s embedded
`FollowState` and `Path::installed_heading_bits`. The same template
slot remains `installed_heading_delta` for float arithmetic in
`update_track_attachment_follow_state`; this helper proves the raw-bit view.

2026-06-18 naming sync: `player+0x42c` is now `post_follow_exit_roll`, matching
the only confirmed consumer in `update_cameraman`. `player+0x430` is
`post_follow_heading_carryover`: this helper copies the raw dword from the
template's installed-heading lane, but no direct consumer is currently closed.
The live Binary Ninja `Path+0x98` field intentionally remains the float
`installed_heading_delta` view because the arithmetic attachment helpers use it
that way.

2026-07-18 ownership replay: the exact scratch and its 100% match were left
unchanged. The focused and broad Player lifecycle replays now persist
`void __thiscall begin_post_follow_carryover(Player*)` in both databases. Binary
Ninja still held an incidental `int32_t` return and rendered `return 0`; replay
changed that to the matched void tail. IDA already held the corrected ABI but
its checked-in artifact was stale, so the refresh now exposes the full Player
owner instead of `sub_43AF60(int this)`. Both decompilers resolve the captured z
through `Player::body.transform.position.z`, and IDA preserves the raw-bit read
with `LODWORD(Path::installed_heading_delta)` rather than inventing a second
Path field or owner.
