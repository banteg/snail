# WIP — 39.79% score, 183/204 insns on standard flags

Now on the project-standard `msvc6.5 /O2 /G5 /W3` (the earlier `/Op`
experiment reached 205/204 instructions, which proves the dual-slot
float temps + integer-register copies are reachable — but per the
search_path_for_golb precedent the same pattern emerges from source
shape alone when the pre-rotation delta stays live after the copy, so
the open task is finding that source idiom, not flags). Verified source
shapes that got the structure right:

- `do { ... } while (--idx >= 0); return;` with `if (probe.y <= 0.001f)
  goto seed;` — reproduces the target layout (seed block after the plain
  return, fallthrough-free hot loop)
- world x lanes inline in the delta expressions (stay on the FPU; IDA's
  `double v13/v15` are FPU-resident temporaries — declaring real
  `double` locals forces an 8-aligned ebp frame the target lacks)
- `extern char* volatile g_game_base` reproduces the per-statement base
  reloads in the seed block (this also moved
  begin_track_attachment_follow_state from 85.19% to 88.89%)

Remaining: register-allocation alignment golf (declaration order /
usage-order experiments), second-probe CSE differences, seed-block
float copies (`fld/fstp` vs integer moves for progress / position.y).

Semantics fully recovered (see also the seeding writes in scratch.cpp):

- scan template samples backward from `sample_count-1` (+0x44), stride
  0xa8 via base at +0x5c, skipping samples with +0x14 <= 0
- probe 1: position minus (cell anchor + sample offset), rotated into
  the sample local frame (`Vector3::rotate_by_matrix`, thiscall)
- gates: `(float)(width_cells / -2) - 0.3f < x < (float)(width_cells / 2)
  + 0.3f` (signed INTEGER division — the 06-10 half-span finding),
  `y >= -0.2` (double constant), `z > 0.0f`, `z < sample depth limit
  (+0x8c)`
- probe 2: sweep-displaced position re-rotated; accept when rotated
  y <= 0.001f
- seeding: the global FollowState at game+0x430100 (active=1, template,
  cell, sample index, progress = rotated z, vertical_offset = 0,
  player = game+0x42fd7c, fields +0x18/+0x1c zeroed, live byte +0x99
  cleared, squidge scratch +0x90 consumed then zeroed), player
  position.y snapped to rotated local y, heading table write
  (61-dword row stride), then a validating
  `update_track_attachment_follow_state(rate at +0x94,
  &sample_index, &player.position)` — thiscall, three args
