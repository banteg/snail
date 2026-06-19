# WIP — 79.80% score, 202/204 insns on standard flags

Now on the project-standard `msvc6.5 /O2 /G5 /W3` (the earlier `/Op`
experiment reached 205/204 instructions, but flag changes remain only
experiments). Current source-shape wins:

- `do { ... } while (--idx >= 0); return;` with `if (probe.y <= 0.001f)
  goto seed;` — reproduces the target layout (seed block after the plain
  return, fallthrough-free hot loop)
- copying `cell->anchor_position` into a `Vector3` first recovers the native
  `add eax, 0x10` anchor-load prologue and the `v19/v20/v21` stack slots
- explicit `sample_origin`, `hit_origin`, and `swept_position` vectors recover
  the native 0x64-byte frame and the stored world-y/z and swept-y/z lanes
- two-step y/z subtracts (`v23 = py; v23 -= v31`) recover the target `fsub`
  polarity on the first probe; world x lanes still stay FPU-resident
- `extern char* volatile g_game_base` reproduces the per-statement base
  reloads in the seed block (this also moved
  begin_track_attachment_follow_state from 85.19% to 88.89%)

Remaining residuals at 79.80%:

- sample pointer formation uses `eax` + `ecx` (`mov eax, [edi+0x5c]; mov ecx,
  ebp; add ecx, eax`) instead of target `mov ecx, [edi+0x5c]; add ecx, ebp`
- first probe z-copy scheduling has one integer move before the `fsub`
  where target schedules it after
- second-probe vector copy registers are swapped (`eax`/`edx`) around the
  `v25/v26/v27 -> probe` stores
- loop-exit branch polarity is still `jl return; jmp loop` versus target
  `jge loop; return` for the same seed-after-return layout
- seed stores for `progress` and `player.position.y` are integer moves; target
  uses `fld/fstp`. Plain casts and neutral arithmetic did not move codegen.

Semantics fully recovered (see also the seeding writes in scratch.cpp):

- scan template samples backward from `sample_count-1` (+0x44), stride
  0xa8 via base at +0x5c, skipping samples with +0x14 <= 0
- probe 1: position minus (cell anchor + sample offset), rotated into
  the sample local frame (`Vector3::rotate_vector_by_matrix`, thiscall)
- gates: `(float)(width_cells / -2) - 0.3f < x < (float)(width_cells / 2)
  + 0.3f` (signed INTEGER division — the 06-10 half-span finding),
  `y >= -0.2` (double constant), `z > 0.0f`, `z < sample depth limit
  (+0x8c)`
- probe 2: sweep-displaced position re-rotated; accept when rotated
  y <= 0.001f
- seeding: the FollowState at game+0x430100 — UNIFIED (2026-06-12): this
  is the Player's embedded 0x40-byte follow sub-struct at player+0x384,
  not a standalone global (0x42fd7c + 0x384 = 0x430100). The seed re-reads as:
  active=1, template, cell, sample index, progress = rotated z,
  vertical_offset = 0, player back-reference, orientation_a/_b
  (+0x18/+0x1c) reset, **attachment_exit_pending (player+0x41d) cleared,
  squidge.start_squidge_y(player.velocity.y) then velocity.y = 0** — the
  exit-lane squidge idiom in reverse — player position.y snapped to
  rotated local y, heading table write (61-dword row stride), then a
  validating `update_track_attachment_follow_state(player.velocity.z,
  &player.position, &player.velocity)` — thiscall, three args
