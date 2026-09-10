# cRSnail::ExtractHotSpots @ 0x445d50

## Current result: exact, 2026-09-10

The Wii reference at `0x80052a00` retains the missing source operation:
count matching faces, break after the first match, then normalize each component
by the reciprocal count. The canonical source now models that operation.
MSVC folds the successful count to one and emits exactly the six native copy
instructions that previously lacked a source explanation.

The Windows result is **74/74 instructions**, prefix **74**, and **7/7 positional
references**. All **208 bytes** are accounted for: 180 identical non-relocation
bytes and 28 bytes in audited relocations, with no unexplained bytes. The raw
unlinked body differs in relocation fields. No shared header or compiler profile
changed. See the [cross-port evidence and controls](../../hotspot-wii-normalization-20260910.md).

## Historical recovery and controls

The following notes describe the previous 91.55% source and its bounded negative
experiments; the normalization recovered above supersedes that residual.

Authored void `cRSnail::ExtractHotSpots()` over the exact 0x19b4-byte Snail
owner. Its sole Windows caller has just loaded `TurboHOTSPOTS.X` into the
Snail's hotspot body and passes the embedded `cRSnail` in ECX. Binary Ninja
confirms the no-argument `__thiscall`; Android and iOS each retain one
`cRSnail::ExtractHotSpots()` body in `SubGame.o`.

The method walks the 19-entry hotpoint texture-name table, resolves each name
through the texture bank, finds the matching model face, and copies that
face's first vertex into `snail_hotspots_local`. It then applies the authored
0.300000012 Y lift to `SNAIL_HOTSPOT_CAMERA_INTRO_TALK`. The exact neighboring
`cRSnail::BuildHotSpots()` transforms this local bank through the two owned
source matrices for cutscene and gameplay consumers.

The scratch exports `?ExtractHotSpots@cRSnail@@QAEXXZ`. It is
semantic-complete at 91.55%, 68/74 instructions, prefix 31, with all seven
references clean. Four recorded sweeps cover 39 variants (30 unique) and the
whole-image provenance check finds the target's redundant six-instruction
vector self-copy nowhere else. The remaining copy and one error-call register
choice remain unresolved source-shape differences; explicit self-assignment and aggregate operator
forms regress and are not retained.

## 2026-09-04 source-expression diagnostics

Four `hotspot-expression-mutations.json` probes against `94f05adb8` test
ordinary value addition in both operand orders, a named destination reference,
and a component constructor. They give 52.29% (79 instructions) or 30.97%
(81 instructions), without recovering the native redundant copy. No source
change is retained; the 91.55% baseline remains open.

## 2026-09-05 bounded animation-family probes

Three whole indexed-hotspot loop variants pair scalar accumulation, vector +=, and vector addition with the owned hotspot array. None improves 91.55%, and each loses the audited name-table sentinel. The six native copy instructions remain unexplained. No explicit self-copy or unsupported operator return-type change is retained.

## 2026-09-05 additional source-shape checks

Five diagnostic vector copy/assignment definitions are neutral at 91.55%. The shared header remains unchanged and the unexplained native self-copy remains open.

## 2026-09-07 vector addition result controls

The diagnostic shared-header overlays compare reference, value, and void results from unchanged vector `+=` arithmetic. Typed-cursor accumulation gives 68/74 instructions at 78.87%; direct vector access and the corrected block-scoped borrow give 75/74 at 73.83%. The first unscoped borrow crossed the existing error label and did not compile; its three invalid variants are explicitly audited, then rerun with the declaration inside a block. They are not negative matching evidence. The native six-instruction copy is not recovered by changing this inline return contract, and no header or canonical source is changed.
