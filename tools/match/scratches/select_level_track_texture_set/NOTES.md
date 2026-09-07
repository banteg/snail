# select_level_track_texture_set

Small level texture-set mutator at `0x410730`. The iOS symbol inventory
preserves the authored owner and method as `cRTrack::Change(int)` in `Game.o`;
the Android port independently retains the same class method. The Windows root
subobject is therefore modeled primarily as `cRTrack`; `Track` remains only a
compatibility alias for older analysis consumers.

- `cRTrack +0x00` and `+0x10` are the four-entry track and slide texture banks.
- `+0x20` stores the active texture-set index.
- Argument `5` selects a random set in `[0, 4)`.
- A changed set rewrites both texture banks through
  `replace_object_list_texture_refs` on `g_object_list`.

The native caller ignores the return register, and the changed path only leaves
whatever the texture-replacement helper leaves in `eax`, so this is modeled as a
`void` mutator rather than a meaningful `int`-returning getter.

## 2026-06-20 object texture-family audit

Two source-plausible selector forms were codegen-neutral at `76.19%`: reusing
the `texture_set` parameter as the selected value, and initializing
`int selected = texture_set` before a no-op default case. Neither recovers the
native pre-save `mov eax, [esp+4]` switch selector, so the remaining residual
was dispatch/local lifetime rather than texture-bank semantics.

## 2026-06-20 switch default reload fix

The exact native shape needs the default case to reload `texture_set` from the
stack after the jump table. A plain `selected = texture_set` lets VC6 pre-load
the argument into `edi` and reuse it as both the selector and selected value,
dropping to `76.19%`. Reading the default through a volatile parameter view
keeps the switch selector in `eax`, copies only the default value into `edi`,
and matches exactly: `100.00%`, `43/43` instructions, `43/43` prefix, with the
curated `select_level_track_texture_set_jump_table` mask audited cleanly.

2026-07-13 no-fakematch audit: the volatile parameter reload was solely
coercing switch-register ownership and is removed. The direct default
assignment keeps the real five-bank selector semantics at the honest 76.19%,
41/43 object with six clean operands; the native pre-save selector load and
separate default reload remain visible layout debt.

## 2026-07-15 authored Track owner replay

The symbol-preserving iOS builds place `cRTrack::Change(int)` in `Game.o`, and
the Android port independently calls `cRTrack::Change` from its level setup.
That paired provenance replaces the synthetic `TextureSetSelector` owner with
the exact 0x24-byte `Track` root subobject: four track texture refs, four slide
texture refs, and the active set index.

The Windows caller discards EAX, while both ports leave path-dependent helper
or receiver values there. The method therefore retains a void contract. Binary
Ninja and the guarded IDA frame-owner replay now carry `Track*` on the receiver,
and the root field is `GameRoot::track` at `+0xb24` in both databases.

A distinct source-level `requested_texture_set` local was also tested as a
natural explanation for the native selector/default lifetimes. VC6 coalesced
it back to the same 41-instruction candidate, so it was removed. The method
remains honestly at 76.19% with all six operands audited; no volatile reload or
other register-allocation coercion was restored.

## 2026-07-28 primary cRTrack ownership

The newly tracked Android and iOS bodies independently expose the exact
`cRTrack::Change(int)` symbol and a void mutator contract. They also make the
port boundary explicit: both mobile owners are 0x388 bytes, carry seven
platform texture sets, and use selector 8 for random choice. None of those
offsets, counts, or selectors transfer to Windows.

Windows machine code and the sole root callsite independently retain the exact
0x24-byte owner at `GameRoot +0xb24`, four track/slide pairs, and selector 5.
The matcher, Binary Ninja, and IDA therefore now use `cRTrack` as the primary
type while keeping `Track` only as a compatibility alias. The source-shape
rename leaves the honest 76.19% machine-code score unchanged.

## 2026-07-29 selector/default lifetime boundary

Three recorded sweeps cover the ordinary source shapes that could keep the
signed parameter selector distinct from the selected texture-bank index.
Zero, minus-one, and parameter initializers are byte-identical to the baseline.
Separate signed, unsigned, and const selector locals in both declaration orders
are also neutral, alone and with a scoped default copy or a fallthrough default
assignment. Adding an explicit `case 4` produces the target instruction count
but regresses to 74.42% because it emits a constant case body rather than the
native out-of-range/default reload.

Signed and unsigned 32-bit selected-index spellings are likewise neutral. The
`DWORD` spelling does not compile because this scratch intentionally does not
import a Windows typedef header; it contributes no match result. Across the 25
compilable variants, none improve: 20 are byte-identical and 5 regress.

The experiment ledger records this lane at **76.19%**
(`41/43`, prefix 0, six clean references). Both unaudited operands are the same
jump-table relationship displaced by the opening register schedule: native
indexes it through `eax`, while the candidate indexes its candidate-local table
through `edi`. Native alone preloads the selector before the saved registers
and later reloads the default value into `edi`; VC6 coalesces those lifetimes in
every ordinary form tested.

Do not restore the formerly exact volatile parameter view, take the parameter's
address, or add another register-allocation coercion. The mobile bodies confirm
the owner and algorithm but use different texture-set counts and cannot prove
the Windows source lifetime. These results rule out the recorded forms, not
other native-backed source shapes.

## 2026-07-30 exact-offset jump-table audit

The audit now pairs a native curated jump table with a compiler-local table
when both computed jumps remain at the exact same function offset and expose
the same entry count. Pairing alone grants no proof: the existing ordered
destination verifier still accepts or rejects the table contents.

Here the `eax` and `edi` dispatches both remain at `+0xd`, but the table is
correctly rejected. Five entries are identical; native's default entry lands
at `+0x45` to reload the parameter into `edi`, while the candidate entry lands
at `+0x43` because that value is already live. The former two one-sided entries
are now one explicit jump-table mismatch. Source, score, and the measured
lifetime boundary remain unchanged at 76.19%, 41/43 instructions, and
prefix 0/43.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and both
verified mobile bodies agree on the `cRTrack::Change(int)` owner, selector
dispatch, random-selection case, current-set guard, texture replacement, and
state update. The Windows-specific four-bank layout and selector value remain
grounded in its native body rather than borrowed from the seven-bank ports.

The sole reference mismatch is the local jump table's default destination:
native reloads the parameter after dispatch, while VC6 coalesces the same value
into the switch register in the candidate. That is a compiler/reference-layout
residual, not a missing case or owner.

## 2026-09-05 additional source-shape checks

Three inline state-mapping operations and three parameter-remapping lifetimes do not improve 76.19%. Existing reference debt remains visible; no helper is retained.

## 2026-09-05 additional coupled source controls

Four selector-mapping operations test const/reference inputs and returned/output selections. All are neutral at 76.19%, retaining the same jump-table mismatch. No helper or source change is retained.

## 2026-09-06 case-owned guard and update experiment

Re-read the native body and both verified mobile bodies rather than repeating
the selector-local/helper sweeps. Both mobile decompiles expose an early
current-set equality return within each explicit selector case. Windows instead
has one common current-set load at `0x410779`, comparison at `0x41077c`, and
branch at `0x41077e`, reached after case-local assignments and a distinct
default argument reload at `0x410775`. This motivates testing whether VC6
tail-merges source-level case-owned guards or full guarded texture updates into
the Windows common tail; it does not transfer mobile counts or offsets.

`case-owned-update-20260906-mutations.json` records two bounded alternatives,
both compiled with standard `msvc6.5 /O2 /G5 /W3`:

| Source shape | Match | Candidate/target instructions | Prefix | References ok/unresolved/mismatch/unaudited |
| --- | ---: | ---: | ---: | --- |
| Retained common guard | 76.19% | 41/43 | 0/43 | 6/0/1/0 |
| Case-local early returns, common update | 64.00% | 57/43 | 0/43 | 6/0/1/0 |
| Complete guarded update in each case | 25.00% | 133/43 | 0/43 | 6/0/0/22 |

The full exported diffs reject both hypotheses, not just their scores. The
first emits separate current-set loads/comparisons in the cases, although its
final 14-instruction update block remains exact. The second constant-folds
texture indexes and duplicates the two-call updates and return tails instead
of merging them. Both still keep the dispatch argument in `edi`; neither
recovers the native pre-save `eax` selector load or default reload. They
produce two distinct byte-and-relocation identities, neither the baseline.

The six paired ordinary references remain explained in both candidates:
`RAND` at native `0x410764` resolves to `0x44dc90`, `ftol` at `0x41076c` to
`0x48b380`, `g_object_list` at `0x410788`/`0x41079f` to `0x4b7648`, and
`ReTextureObjects` at `0x41078d`/`0x4107a4` to `0x430d90`. The duplicated-update
candidate's 22 unaudited references comprise the two unpaired dispatches and
20 extra candidate global/call operands; its zero mismatches is not cleaner
reference proof.

No source is promoted. Baseline and final remain **76.19%, 41/43 instructions,
prefix 0/43, references 6/0/1/0**. The only retained mismatch is native
`0x41073d`'s displacement to the already-curated six-entry table at `0x4107b4`
versus compiler-local relocation `$L1232`. Native ordered destination offsets
are `0x14, 0x18, 0x1f, 0x26, 0x45, 0x2d`; default slot 4 reaches the native
reload at `+0x45`, whereas the retained candidate goes straight to its common
tail at `+0x43`. There is no missing shared symbol to curate. Source/default
lifetime remains the technical residual; the failed mobile-inspired guard
transfer does not establish that all standard-profile source forms are ruled
out. Scratch configuration and semantic-complete classification are unchanged.

## 2026-09-07 version-verified VC6 controls

Unchanged-source probes under the coherent `msvc6.0` and `msvc6.3` component
sets preserve this function's current normalized instructions and reference
state. The seven-function batch pairs the selector/search residuals with four
exact neighboring controls. No compiler override or source change follows
from this comparison. Component versions, hashes, measured results and the
separate mislabeled VC7-archive check are recorded in
[the compiler-control report](../../compiler-profile-controls-20260907.md).
