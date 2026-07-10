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

Focused matcher result: 71.32%, 1028 candidate instructions versus 1033 target instructions, 9-instruction prefix, 116 clean masked operands, and 2 jump-table mismatches.

The first mismatch is the destination label of the range-check `ja`; its semantics agree, but later block sizes give the normalized target and candidate labels different identities. Both switch jump-table operands are now content-audited and classified as real mismatches, not unresolved data or call targets.

The largest remaining source-shape opportunities are:

1. state-1 galaxy setup case ordering and shared build/destroy exits;
2. residual authored/ambient ring register scheduling;
3. residual HUD and handoff register scheduling;
4. residual jump-table target identities driven by the remaining block layout.

Rejected continuation trials:

- moving the selected-level handoff to a tail `goto` label still emitted the same measured layout;
- spelling the pause-state setup with raw offsets did not change the prologue mismatch;
- materializing a time-trial `record` base local improved one address sequence but regressed the surrounding HUD/camera tail.

2026-06-20 type cleanup: the shared `TimeTrialStringFormatter` header now owns
the method-only formatter receiver used here and by the challenge setup/HUD
callers. The broad `update_subgame` scratch stayed at 67.53%; no formatter
fields are promoted because only the member-call source shape is proven.

2026-06-21 receiver cleanup: the scratch now defines
`SubgameRuntime::update_subgame` directly and uses the shared
`SubgameRuntime` front-controller window for pause menu, challenge setup,
galaxy route, selected replay state, and rebuild selector fields. Focused Wibo
is unchanged at `67.53%`, `1046/1033`, prefix `9/1033`, with the same
`108 ok / 2 mismatch` masked audit. `spawn_track_speedup` remains a
member-style call surface on `SubgameRuntime` because this caller wants the
historical receiver lookup even though the standalone helper body is
`__stdcall`/receiver-free. `uv run snail match types --paths` still reports no
generic `Game` owner row.

2026-07-10 embedded-player ownership: `game + 0x3bb764` is the complete
embedded `Player`/`cRSubGoldy`, not a standalone score block. The measured
extent is exact: `0x3bb764 + sizeof(Player) (0x4364) == 0x3bfac8`, the first
runtime track cell. This unifies the previously flattened aliases for
`position.z +0x70`, `movement_state +0x120`, `cameraman +0x200`, score/timer
lanes `+0x2e4/+0x2e8`, `player_slot +0x380`, `velocity.z +0x418`,
`control_source +0x43c`, and `interaction_max_z +0x2980`. The shared runtime
header now exposes a typed-size `player_storage` union owner while retaining
the proven contextual aliases, and this scratch routes all player gates and
spawn arguments through it. Focused codegen remains `67.53%`, `1046/1033`,
with the same `108 ok / 2 jump-table mismatch` audit; exact
`calc_subgame_rate` and `update_subgame_camera` remain exact.

A named `Player*` kept across the pause/fade bridge measured `70.53%` and
reduced the candidate to `1037` instructions, but it displaced the native
`ebx` zero / `edi` state roles and made the operand audit pair the target
`spawn_track_speedup` call with candidate `spawn_track_health_pickup`. That
variant is rejected rather than retaining an attractive score with a new
semantic masked-operand mismatch.

2026-07-10 bridge-tail layout: expressing the selected-level handoff as the
cold side of an inverted state-2 bridge places it after the gameplay/HUD body,
matching the independent Windows and Android control-flow evidence. Duplicating
the current-to-previous application-state snapshot inside the persistent and
non-persistent arms recovers the exact native tail instructions. Together these
changes improve focused Wibo from `67.53%`, `1046/1033`, `108 ok` to `69.45%`,
`1049/1033`, `111 ok`, while preserving the same two jump-table mismatches and
introducing no call/data mismatch. Direct embedded-player owners now cover its
completion gate, stopwatch, interaction bound, total score, lives, and the
`last_ring_spawn_z +0x37c` lane initialized by `initialize_subgoldy`.

Retested neighbors on the new bridge layout: materializing the time-trial
record base regressed `68.94%` to `67.95%`; a shared ambient-ring speed local
grew the frame from `0x3c` to `0x40` and regressed to `61.11%`; a named control
source was codegen-neutral. None were retained.

2026-07-10 projected-ring address ownership: the projected cell at
`cell + 0xfc0` is a contextual address, not a long-lived local owner. Inlining
that address in the three projected-ring arms removes the invented `ebx`
lifetime and recovers the native repeated address formation plus shared
post-call last-Z store. Focused Wibo improves from `69.45%`, `1049/1033`,
`111 ok` to `70.97%`, `1027/1033`, `115 ok`, with the exact `0x3c` frame and
the same two jump-table mismatches. No call or data operand mismatch is added.

2026-07-10 time-trial record owner retest: after shortening the projected-cell
lifetime, the semantic `record = game + level_mode_arg * 0x1fac0` pointer no
longer perturbs the surrounding frame allocation. It now recovers the native
`add eax, esi` followed by in-place `+0x944158` reuse, improving focused Wibo
from `70.97%`, `1027/1033`, `115 ok` to `71.32%`, `1028/1033`, `116 ok` with
the same two jump-table mismatches and no unresolved or mismatched call/data
operand. The earlier record-local regressions remain useful allocation-history
evidence, but no longer describe the retained layout.
