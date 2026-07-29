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

Three recorded sweeps exhaust the ordinary source shapes that could keep the
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

The experiment ledger therefore formally stalls this lane at **76.19%**
(`41/43`, prefix 0, six clean references). Both unaudited operands are the same
jump-table relationship displaced by the opening register schedule: native
indexes it through `eax`, while the candidate indexes its candidate-local table
through `edi`. Native alone preloads the selector before the saved registers
and later reloads the default value into `edi`; VC6 coalesces those lifetimes in
every ordinary form tested.

Do not restore the formerly exact volatile parameter view, take the parameter's
address, or add another register-allocation coercion. The mobile bodies confirm
the owner and algorithm but use different texture-set counts and cannot prove
the Windows source lifetime. Further progress needs original Windows source or
compiler provenance, neither of which is currently available.
