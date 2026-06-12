# Dossier — scratch not yet written (673 insns, 2887 bytes)

cRSubGoldy::Collision() per cross-port symbols. target.asm committed.
The contact table, from the IDA export (line refs in 00444cf0-*.c):

| pool | walk | gate | effect |
|---|---|---|---|
| salt | 6080 bytes / stride 152 (40 x 0x98) | pre-gate < 1.0 then normalized dist < 0.98 | damage 0.15, damage_retrigger_timer seeded from retrigger_step when zero |
| sub-lazer | 3520 / 176 (20 x 0xb0) | < 1.0 then < 0.49 | damage 0.02 |
| garbage | (stride from loop) | < 1.0 then < 0.98 | velocity.x -= dir.x * vz * 0.18, velocity.z -= dir.z * vz * 0.1, direction byte from dir.x >= 0, score event 0, damage 0.04, random voice via next_math_random_value * -0.000061035156 |
| slugs | 1888 / 236 (8 x 0xec) | < 2.0 then < 1.5675001 | repeat hit: velocity.z = subgame_rate^2 * 0.004 * -8, damage 1.0; first hit: velocity = (0, tc*0.2, tc*-0.2), wobble lift_phase_step = 0, carryover/cutscene lanes |
| rings/pickups | 7000 / 140 (50 x 0x8c) | < 1.0 then < 1.24 | score event 3, ring ladder dispatch |

Validates the harvested checklist formulas (slug triplet, repeat-hit
knockback) and adds the garbage knockback pair and the ring 1.24 gate.
All damage flows through apply_damage_gauge_delta(state, amount, 0) —
the force parameter from the hit-flash harvest is visibly 0 here.

Verify-pass targets for the Zig port: salt/sub-lazer gates ported per
checklist; slug velocity lanes and garbage knockback are motion-slice
consumers (not yet portable); ring gate and score-event ids worth
diffing against the runner's pickup collision slots.

Match plan: five sequential pool loops with the shared
pre-gate-then-normalize idiom — start the scratch from the salt loop and
extend pool by pool; reuse the salt slot layout from the quartet.
