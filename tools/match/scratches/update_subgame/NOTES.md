# `update_subgame` recovery notes

Target: `update_subgame @ 0x438b90` (`thiscall`, 3748 bytes, 1033 instructions).

This scratch reconstructs the outer gameplay state machine and the state-2 runtime update path rather than using a minimal placeholder. The source was shaped against both decompile exports and repeatedly measured with the VC6.5 `/O2 /G5 /W3` matcher toolchain.

## Recovered control flow

The front switch now models the principal native states:

- states `3` and `4`: pause-menu initialization followed by the intentional fallthrough into its first update;
- state `7`: selected-replay bootstrap and level-zero rebuild;
- state `0`: continuation/rebuild selector, persistent replay lane, star-field hide, and fallthrough to the setup dispatcher;
- state `1`: galaxy, challenge, and tutorial/setup dispatch, including destroy-and-handoff returns;
- state `2`: selected-level overlay, timer advance, tutorial and slug-voice updates, pause/resume gates, click-start suppression, runtime-row processing, HUD updates, and camera handoff.

The shared camera call is left at function tail, while native early-return paths retain direct camera calls where that source shape scores better.

## Runtime layout findings

The row scanner uses the following measured layouts:

- active runtime row stride: `0xf4` bytes;
- row flags: `+0x00`;
- primary intrusive `BodNode`: `+0x04`;
- parcel position: `+0x90`;
- attachment intrusive `BodNode`: `+0xb0`;
- attachment position: `+0xc0`;
- track cell stride: `0x54` bytes;
- four fringe-object pointers begin at the cell's `+0x44` lane.

`RuntimeCellSlotBase` deliberately preserves the indexed slot base and accesses the cell through its native `+0x3bfac8` displacement. A direct typed `TrackRowCell*` caused VC6 to fold that displacement too early and materially changed register allocation.

The runtime block includes plausible original insertion idioms for the two intrusive lists and semantic lanes for parcels, fringe objects, health pickups, speedups, jetpacks, garbage and salt hazards, slugs, and authored/ambient rings.

## Compiler-shape findings

Several source-level details were important rather than cosmetic:

- Reloading the fringe object after `get_track_skirt_color` removes an otherwise persistent pointer spill. This recovers the native `0x3c` frame, `ebp` row index, `edi` cell-offset base, and `ebx` zero value.
- The tile `29`/`30` path scores better as a nested block with an inner auxiliary-data test.
- The fringe selector is signed `cell_index % 8`; replacing it with `& 7` loses the target's signed modulus sequence.
- The four authored tile-35 ring variants converge on one shared last-ring-Z assignment.
- RNG calls are kept on the left side of comparisons where that produces the native operand ordering and clean call audits.
- Completion-source assignments intentionally retain the matcher-confirmed X/Y source ordering.
- Duplicating the challenge-setup `result == 1` build-zero path scores better than sharing the later case-7 label; the native places that build return before the challenge destroy path.
- `format_time_trial_string` is called as if it had an unused receiver at `game + 0xff25e0`. The callee itself is still the `ret 4` formatter, but this source shape recovers the native `ecx` setup at the HUD callsites.

These choices recover the exact native prologue through the state range test:

```asm
sub esp, 0x3c
push ebx
push ebp
push esi
push edi
mov esi, ecx
call calc_subgame_rate
mov eax, [esi+0x3c]
cmp eax, 7
```

## Remaining mismatches

Focused matcher result: 67.53%, 1046 candidate instructions versus 1033 target instructions, 9-instruction prefix, and 108 clean masked operands.

The first mismatch is the destination label of the range-check `ja`; its semantics agree, but later block sizes give the normalized target and candidate labels different identities. The two unresolved masked operands are switch jump-table addresses, not mismatched data or call targets.

The largest remaining source-shape opportunities are:

1. state-1 galaxy setup case ordering and shared build/destroy exits;
2. the early state-2 bridge/handoff scheduling;
3. projected and ambient ring shared exits;
4. the time-trial/HUD branches and final camera-return topology.

Rejected continuation trials:

- moving the selected-level handoff to a tail `goto` label still emitted the same measured layout;
- spelling the pause-state setup with raw offsets did not change the prologue mismatch;
- materializing a time-trial `record` base local improved one address sequence but regressed the surrounding HUD/camera tail.
