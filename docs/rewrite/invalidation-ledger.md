# Invalidation Ledger

Use this ledger only when new RE or runtime evidence overturns a previously trusted model.

Why this exists:
- prevent old workaround narratives from becoming sticky repo memory
- surface which assumptions are no longer safe to port against
- point the next dossier at the exact model that needs replacement

Add entries only when one of these happens:
- a previous owner or writer claim is disproved
- a field meaning changes materially
- a controller boundary moves
- a parity test is demoted from `parity` to `scaffold`

Keep entries short:
- date
- subsystem
- invalidated claim
- replacement evidence
- immediate port consequence

Template:

## YYYY-MM-DD - Subsystem

- invalidated claim:
- replacement evidence:
- port consequence:

## 2026-03-25 - Outer bridge

- invalidated claim: ordinary respawn rebuild should stay modeled as a saved-owner bridge opcode lane
- replacement evidence: March 24 Windows capture shows ordinary respawn rebuilding through direct owner `0x1c`, not `0x1a/0x1b`
- port consequence: respawn bridge state in Zig must store the direct selector as authoritative and stop using the request dispatcher as the conceptual center

## 2026-03-25 - Runtime capture policy

- invalidated claim: broader Windows capture is still the default next step for bridge and attachment work
- replacement evidence: the stable March 24 packets closed the practical bridge handoff lanes, while broader probe sets caused host hangs
- port consequence: outer bridge is unblocked for replacement from the locked capture baseline; attachment exit stays static-RE only until a narrower stable proof exists

## 2026-03-26 - Ring runtime and Game fields

- invalidated claim: `game + 0x48` is `bonus_score`
- replacement evidence: `build_subgame_level` seeds `game + 0x48` from compact-record field `+0x48`, `calc_subgame_rate` uses it as the base gameplay rate, and `spawn_track_ring_or_special_effect` consumes it in the default ring `phase_step` formula
- port consequence: explicit ring timing should be modeled from authored `RingSpeed`, while default ramp-ring timing should be modeled from `base_subgame_rate`; future Zig ring-animation work must stop treating `game + 0x48` as a score lane

## 2026-03-26 - Player runtime slices

- invalidated claim: `player + 0x43c` is the persistent current track cell pointer
- replacement evidence: `initialize_subgoldy` seeds `+0x43c` from the per-player control-source globals, while `update_subgoldy` still gets the live current cell from the transient `get_track_grid_cell_at_world_position(...)` local
- port consequence: the shared `Player` typing and any Zig comments/docs must stop calling `+0x43c` `current_cell`; keep runtime-cell access transient and treat `+0x43c` as `control_source`

## 2026-03-26 - Squidge helper prototype

- invalidated claim: `start_squidge_z` returns `float`
- replacement evidence: the raw Windows helper only seeds `SquidgeState.z_phase` and `z_velocity`; on a fresh and current `.i64`, typing it as `void __thiscall start_squidge_z(SquidgeState*, float)` restores a clean high-level `update_subgoldy` decompile, while the float-return prototype alone forces Hex-Rays back into inline x87 asm
- port consequence: keep the checked-in BN/IDA type lane and any future helper signatures on `void`; do not infer helper return types from transient x87 stack residue when the call sites ignore the result
