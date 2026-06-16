# begin_post_follow_carryover @ 0x43af60

Exact match: `100%`, `20/20` instructions.

This is the producer for the post-follow camera exit lanes:

- if follow is active, player+0x42c receives `follow_orientation_b`
- player+0x430 receives the raw 32-bit value from `follow_template+0x98`
- follow is then deactivated, `attachment_exit_pending` is set, the exit
  anchor z is captured from `position.z`, and the exit gates/progress reset

2026-06-16 consolidation: the scratch now uses shared `player.h` follow-prefix
fields and `AttachmentPathTemplate::installed_heading_bits`. The same template
slot remains `installed_heading_delta` for float arithmetic in
`update_track_attachment_follow_state`; this helper proves the raw-bit view.
