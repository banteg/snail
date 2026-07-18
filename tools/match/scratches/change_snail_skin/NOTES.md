# change_snail_skin @ 0x445fd0

Exact 100.00% match, 19/19 instructions, with three clean masked operands.

This is the Windows `SnailSkin::change_snail_skin`, authored as
`cRSnailSkin::Change(int, float)`. It arms the selected material slot, clears
progress, and either applies an immediate change when duration is zero or
derives `progress_step` as `1 / (duration_seconds * 60)`.

Android exports the same authored signature and exact field/formula family.
Damage-gauge and invincible-shell callsites therefore share this real owner
instead of per-scratch transition API shims.

## 2026-07-18 durable lifecycle replay

The focused Snail-presentation lane now verifies the exact 0x20-byte owner and
replays the authored `Change(int, float)` ABI beside `Init` and `AI`. Paired
tracked decompiles expose the selected material slot, active/progress state,
and the exact 60 Hz duration formula under `SnailSkin`; strict health checks
reject the stale synthetic state name and raw field accesses. Focused matching
remains exact at 19/19 with all three operands clean.
