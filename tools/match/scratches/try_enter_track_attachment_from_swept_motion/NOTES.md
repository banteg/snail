# Pre-match dossier — scratch not yet written (204 insns, ~12 globals)

@ 0x42c770, thiscall on the **path template** (not the player), 6 float
args (position xyz + sweep deltas xyz) + cell ptr, ret 0x1c.

Recovered semantics (IDA export + raw asm read, 2026-06-12):

- scan: walks template samples **backward** from `sample_count-1`
  (template +0x44), stride 0xa8, base ptr at template +0x5c; skips
  samples whose +0x14 float is <= 0
- candidate test: world delta = (pos + cell anchor[+0x10..0x18] +
  sample offset[+0x30..0x38]) rotated by the sample matrix (+0x40) via
  `Vector3::rotate_by_matrix` (thiscall on the vector, matrix pushed);
  the dual-slot temp+copy idiom from search_path_for_golb appears again
- half-span gate: `width_cells` (template +0x54, **int**) divided by
  ±2 with **signed integer division** (cdq/sar idiom confirmed) then
  ±0.3f — matches the 06-10 half-span truncation finding exactly
- vertical gates: rotated y >= -0.2, rotated z > 0, z < sample depth
  limit (+0x8c)
- second probe: sweep-displaced position re-rotated; accept when its
  rotated y <= 0.001
- on accept, seeds the **global FollowState instance at game+0x430100**
  (same layout matched in begin_track_attachment_follow_state):
  active=1, template=this, cell, sample_index, progress=rotated z,
  vertical_offset=0, then `*(game+0x42fde8) = rotated y` (the 0.49-gate
  global from the audit), squidge start, heading table write
  (61-dword/244-byte stride, same table), and a validating call to
  `update_track_attachment_follow_state(game+0x430100, ...)`
- confirmed: does NOT clear `player+0x41d` itself (caller's gate does)

To write the scratch: extend `track_attachment.h` AttachmentPathTemplate
with +0x44/+0x54/+0x5c fields and an AttachmentSample struct; model the
game-relative globals as `extern char g_*[]` symbols added to
`(int)g_game_base` like begin_track_attachment_follow_state does.
