# cRSnail::SetWeapon @ 0x445920

Current recovery: semantic-complete (`analysis` residual). Live Windows
analysis establishes a void `cRSnail` member with one integer argument;
Android and iOS both retain `cRSnail::SetWeapon(int)` in `SubGame.o`.

The method maps the Goldy shooting flags onto target states for all three
embedded weapon channels, performs reverse/show/queued-idle/hide transitions
through `cRWeapon::SetAnimation`, publishes each selected state, and emits the
appropriate activation/deactivation sound feedback. The sparse movement lookup
and jump tables remain explicit curated references.

Focused VC6 result under scoring policy 5: **83.5386%**, 246/249 candidate/native
code instructions, prefix 1/249, with all 24 reference operands audited and
clean. The guarded remap is literal data, not code. Remaining state lifetimes,
register allocation, and transition scheduling require further analysis.

## 2026-09-11 lookup-aware lifetime replay

The current recipe records 38 initialization, channel-borrow, and chained
target-assignment controls. Two chains score 83.7626%, but merely reorder
assignments across the still-wrong state register allocation: native channel
targets use EDI/EBP, while those candidates retain EBP/EBX. They preserve the
same three missing instructions and do not recover the early input load or
the channel-zero address lifetime. No source is promoted from that score gain.

The other controls are neutral or regress; eager initialization also changes
the audited jump-table structure. The default path and uninitialized third
target remain as observed in the Windows body. These bounded results do not
close the mapping or transition work. The recipe and
[receipt](../../initializer-boundaries-20260911.json) preserve every current
result and the relevant native/candidate assembly differences. The September 5
measurements below used older source dependencies and scoring.

The matcher source now uses authored `SetWeapon` and exact VC6 symbol
`?SetWeapon@cRSnail@@QAEXH@Z`; `set_snail_weapon` remains only the stable scratch
and Windows-address identity.

## 2026-09-05 bounded animation-family probes

Three complete channel-lifetime variants remove the channel-0 borrow and/or separate selected-state and immediate locals for each channel. All regress from 73.02% with references still clean. The original state-dispatch and channel interactions remain open; local simplification alone is insufficient.

## 2026-09-05 continued source-shape investigation

Eleven change-gate lifetime forms regress from 73.02%. The undefined default-arm value remains as in the native body; no fabricated initialization is added.

## 2026-09-05 channel operation and target-array checks

Twelve `whole-channel-transition-operation-20260905-mutations.json` forms
factor the first two identical animation transitions, borrowing the channel
or indexing it through the Snail and returning/borrowing the changed flag.
All regress to 63.27%, with the 24 references still clean.

Fourteen `whole-case-channel-borrows-20260905-mutations.json` forms place the
channel borrow only inside the two-call target-state branches. Changing only
channels one/two is neutral at 73.02%; moving channel zero's borrow regresses
to 68.29%. Eight coupled target-state array forms in
`whole-target-channel-array-20260905-mutations.json` regress further to
58.42–59.02% and expose six unaudited operands. The undefined default-arm
third state is left uninitialized in every probe. No source is retained;
these results do not close the branch-lifetime or state-mapping source work.

## 2026-09-05 shared transition owner and feedback joins

Six whole-channel forms reuse a transition-channel pointer across the first,
first two, or all three channels, either at target-switch entry or inside its
two-call cases. All regress from 73.02%. Six additional forms join the third
channel's duplicated state/sound exits, with the original, direct, or later
channel-zero borrow and either a shared change gate or existing sound branch.
All regress as well. Every variant compiles with all 24 references clean; no
source change is retained. The native mapping/transition lifetimes remain open.

## 2026-09-25 undefined default targets

The first two channel targets are also unassigned in the default arm (the
third already was). Removing the two parameter copies moves both native
`[esp+0x18]` loads into place and improves the retained source from 83.54% to
**87.47%**, 247/249 instructions, prefix 14, with 24 clean references. The same
shape matches `SetJetPack` and `cRTrack::Change`.

Recorded lead `uniform-channel2-tail-no-channel-ref-20260925`: channel zero
without the `Weapon& channel` borrow, and channel two written like the Android
body (break, publish, set changed flag, shared `if (changed) Play(25)`), lines
up with native through all three tail-duplicated exits, including the
`mov [esi+0xf08], ebx` stores. What remains is a register swap: channel one's
target takes `ebx` and the channel-zero case pointer takes a shrink-wrapped
`ebp`, where native has the reverse. The differ also stops recognizing the
byte lookup table in that build (no alignment pad), so it reports 41%. It is
not retained; declaration order (the first 18 of 720 permutations) and
bool/int flag types are neutral or worse.

## 2026-09-25 byte constants 0 and 1 and the ebx penalty

No source change (still 87.47% / 93.29%). This is a traced mechanism with
bounded leads. Rules: the constant-candidate section of
[global-allocation.md](../../c2/global-allocation.md).

Traced on the recorded `uniform-channel2-tail-no-channel-ref` lead (all
three channels alike, no `Weapon&` borrow, shared `if (changed) Play(25)`):
- `target0` = edi and the `target2` ebx piece already match native.
- Channel zero's two-call case pointers (`lea r, [esi+0x64c]`, priority 36)
  pick ebp over ebx because ebx costs +700. That leaves `target1`
  (priority 8) with only ebx. Native has the reverse.
- The +700 comes from two constant candidates, 0 (benefit 5) and 1
  (benefit 2), at 100 × benefit each. VC6 keys constant symbols by value
  only, so each one gathers every use of that value in the function: target
  moves, `push 0/1` arguments, `mov cl, 1`, and the
  `transition_immediate = 0/1` stores. The byte-typed uses restrict the
  range to byte registers. Live across calls, that leaves only ebx.
- Almost all of the benefit is `transition_immediate` itself. Each of
  its six `= 0` stores and three `= 1` stores saves 1, and each range pays 1
  for its load. The mechanism (decoded by crimson-88, 2026-09-25) is in
  the 2026-09-25 entry below and in global-allocation.md, "Demoted stores
  count".

Diagnostics (not source candidates):
- Dropping the `transition_immediate = 0` stores takes both constants to
  benefit −1. The case pointers then take ebx and `target1` takes ebp,
  which is native's allocation.
- An `int` or `unsigned char` flag, or passing `transition_immediate != 0`,
  also gives native's registers. Those forms make the flag a register
  candidate, so its stores become register moves that save 0. They also
  change the flag's code (a register plus `setne`), which native does not
  have.

Still open: native has the same memory bool (byte stores, dword argument
load). So some source difference must keep those stores from counting, or
must add loads for the 0 and 1 ranges. Tried and unchanged: channel-scoped
bools (`bool transition_immediate = 1;` per channel) and `(bool)` on the
argument. In the lead the differ still loses the byte lookup table (it
reports 41%), so compare it with `globalregs.py`.

## 2026-09-25: constant-candidate mechanism decoded (crimson-88)

Generic rules: `../crimson/tools/match/c2/compiler/constant-candidates.md`.
Tracer (lists every counted store and every block-end demotion; `--il` dumps
the IL at the pass boundaries):

```sh
uv run tools/match/c2/run_tracer.py const_trace <scratch> --out <new-dir> [--il]
```

- **Why the stores count.** The bool is passed straight to a bool parameter:
  - The push legalizer widens it into a 4-byte container, with the flag as
    byte part +0. The push becomes
    `push [1:2004 #9 'transition_immediate' z4]`, and the stores stay
    `mov [1:2001 #8^9+0 z1], imm`.
  - The byte stores mark that container partially written. The byte part
    `#8` becomes its own candidate, never read at its own width: the pushes
    read `#9`.
  - Each of its dead defs is demoted to a memory store at block end. All
    nine `#8` stores and all six `#9` reloads in front of the pushes are
    demoted this way. So each `transition_immediate = 0/1` scores as
    `mov [mem], const` and saves 1.
  - Every tuple was promoted and none refused: every `push imm`, every
    `mov target, 0/1` into a candidate, every `mov flag, 0/1`, the switch's
    `sub eax, 0` and `cmp any_channel_changed, 0`.
- **Traced benefits** (first scoring pass, `uniform-channel2-tail-no-channel-ref`
  lead):

  | Value | Uses that save 1 | Loads | Queued benefit |
  |---|---|---|---|
  | 0 | 6 × `transition_immediate = 0` (`mov [2:#8], 0`) | 1, at the entry (`any_channel_changed = 0`) | 5 |
  | 1 | 3 × `transition_immediate = 1` | 1, at the mapping switch head | 2 |
  | 2, 3, 4, 8, −1 | none | 1 | −1 |

  Every other use of 0 and 1 saved 0: about 25 pushes, the target moves,
  `mov cl,1`, `sub eax,0` and the final `cmp any_channel_changed,0`. Both
  ranges were allowed only ebx (byte-only and live across calls), so every
  range that interferes with them is charged `100 × (5 + 2) = 700` on ebx.
- **Checks of the rule.**
  - The lead: predicted 5 and 2, observed 5 and 2.
  - SetJetPack (byte-exact) has the same `bool immediate` pattern with one
    `= 1` store and one `= 0` store. Predicted 1 − 1 = 0 for both values;
    observed 0 and 0, with both stores logged as demoted. Nothing competes
    for ebx there, so it matches.
  - A `char` flag (negative control): predicted −1 and −1, observed −1 and
    −1. The flag is in `al`, with `setne` at each push.
- **Where the lead differs.** The priority-36 channel-0 case pointers
  (lr 18/19) are coloured after `this`, target0 and the channel-1/2
  pointers, and before target1 (priority 8), with allowed {ebx, ebp} and
  costs ebx +700, ebp 0.
- **Diagnostic interventions** (not source candidates). Each patches
  allocator state inside the observer; the harness then reports
  "Observation changed the whole COFF object", and the observed object is
  scored with the snail matcher. The intervention scripts are not kept;
  `const_trace` reproduces what they patch.

  | Intervention | Result |
  |---|---|
  | none (lead) | 41.00% (the matcher also loses the byte lookup table) |
  | benefit of constants 0 and 1 set to −1 at the initial queue | **100%, body byte-exact**, lookup table included |
  | the same with 0 | **100%, byte-exact** |
  | the same with 1 | lead (unchanged) |
  | only constant 1 set to −1, or only constant 0 | lead (unchanged). Both must be ≤ 0, as the chooser rule predicts. |
  | clear the container's partial-write mark (`#9+5 &= 0x7f` before `0x10727bd3`) | constants go to −1 and −1, but the flag gets eax (34%) |
  | clear the mark and force the three flag webs to benefit −100 | **100%, byte-exact** |
  | set the flag part's class to 3 before promotion (so its writes do not mark the root) | same as clearing the mark: −1 and −1, flag in eax |

  So the lead is native's structure except for the positive benefit of
  constants 0 and 1. No other hidden allocator input differs. Native needs
  benefit(0) ≤ 0 and benefit(1) ≤ 0 when the case pointers are chosen, for
  example a flag that is a candidate whose writes are not marked partial
  and whose webs are unprofitable, so it stays in memory.
- **Source search, negative.** About 238 variants:
  - a 216-variant grid (`constant-candidates/gen.py`, not kept):
    `any_channel_changed` initialised at the top, at the declaration or
    after the switch; function-level or channel-scoped flag; reused, direct
    or scoped `selected_state`; switch or if/else for the reverse and target
    dispatch; shared or returning channel-2 tail; the reset before or
    inside the `if`;
  - about 22 targeted forms: the flag as `int`, `char` or `unsigned char`;
    `true`/`false`; `register`; `volatile`; a pointer or reference alias;
    the zero store before the reverse call; `Weapon&` borrows at six
    positions; three inline-helper factorings. The helper reached through
    `this` reproduces the lead exactly (40.54%): its inlined `bool` is
    class 4 like any local and is demoted the same way (traced 5 and 2).

  `int`, `char` and `unsigned char` reach native's registers only by making
  the flag a register with `setne`, which native does not have.
- **Open.** Which source gives constants 0 and 1 a non-positive benefit and
  still keeps the flag's code? Either the flag's stores are not memory at
  scoring, or it has no more counted stores than loads. If its stores are
  register moves, the flag webs (benefit 10 in the mark-cleared and class-3
  runs) must still end up in memory. A class-3 writer alone is not enough:
  the class-3 intervention puts the flag in eax, and inline-expanded locals
  are class 4 anyway. Untested: forms where a counted store is created
  only after allocation. Keep the retained 87.47% source until then.

## 2026-09-25: Codex source search on the benefit rule (negative)

Codex (gpt-6-astra, high) ran 39 probes aimed at bringing constants 0 and 1 to benefit ≤ 0. The overlays
are not kept.

- **Closest.** The flag is computed from both state comparisons (`cmp_bitand`). Both constants trace at
  −1/−1, and the allocation is native's, with the flag in memory. But `setne`/`and` adds 12 instructions:
  89.87%, 261/249.
- **Negative:** inline `cRSnail` bool parameters (still 5/2 and +700 on ebx), return helpers, scoped
  flags, conditional expressions, and show/idle wrappers.

The retained source is unchanged.
