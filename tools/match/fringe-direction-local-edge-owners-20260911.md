# Exact directional fringe selector recovery

`build_track_fringe_objects @ 0x434be0` (`cRSubGame::FringeEdgeTrack`) now has
**normalized and relocation-audited encoded-body equality**. Agreement improves
from **64.45115811% to 100%**, candidate/native instruction counts change from
**498/495 to 495/495**, and the candidate stack allocation shrinks from **0x54
to the native 0x50**. All **53 references** pass strict positional checks.

The [complete receipt](fringe-direction-local-edge-owners-20260911.json)
preserves native and candidate bytes, full sources, same-index references and
branch destinations, source controls, four decompiler witnesses, and validation.
Compiler, flags, headers, ABI, extent and matcher are unchanged.

## Source recovery

Each direction now declares its own `edge_a` selector inside its allocation
block. The diagonal-neighbor branch assigns the existing 1-or-2 expression;
its alternate branch explicitly assigns zero. The old function-wide selector
and four post-color resets are removed. No other source expression or formatting
changes.

The previous carried selector began at zero and was reset after every allocating
block. Consequently, the explicit zero branch preserves its value contract.
The new lifetime lets VC6 reuse the native receiver register for the second edge
selector and restore it after the color call. It also recovers the native zero
register, prologue, stack homes and color-copy schedule. The complete byte proof
confirms these effects together; no register hints or artificial dependencies
are introduced.

Android and iOS preserve the directional neighbor-selection graph and local zero
cases. Their layouts and render handling differ from Windows; Windows native
instructions establish the position/color copies and explicit helper-result
branches retained here. Equality proves the compiled body under the recorded
build, not original variable names or a unique source spelling.

| Reverse control | Normalized agreement | Candidate instructions |
| --- | ---: | ---: |
| Front selector uses old carried lifetime | 70.6949% | 498 |
| Right selector uses old carried lifetime | 70.6949% | 498 |
| Left selector uses old carried lifetime | 85.5992% | 498 |
| Back selector uses old carried lifetime | 85.5992% | 498 |
| All four | 64.4512%; baseline fingerprint restored | 498 |

Every reversal loses both forms of exactness while preserving 53 clean
references. The nearby declaration-initializer form (`int edge_a = 0` with no
alternate assignment) reaches **82.2335%, 490 instructions** and remains a
rejected control. Scope and control spelling matter together.

## Complete encoded proof

The native extent is **1,440 bytes**, `[0x434be0,0x435180)`. The compared body
is **1,428 bytes**, `[0,1428)` or `[0x434be0,0x435174)`. Only twelve recognized
terminal-padding bytes, `[1428,1440)`, are excluded. No unexplained or inline
data ranges remain. Public body credit uses the 1,428 compared bytes.

All **495 instruction pairs** have identical indices, offsets, sizes and
normalized instructions. The strict positional audit checks all **53 reference
entries**, including operand kind/slot and target identity. External relocation
fields are compared only after those checks; **51 encoded relocation ranges**
are masked. No ordinary instruction bytes, SIB bytes or local branch
displacements are masked to obtain equality.

All **52 local branches** land inside the same mapped body. Their actual encoded
displacements agree. Concatenating the independently audited instruction bytes
reproduces both hashes from the matcher's complete encoded-body proof:

`b0bb8c3fe3b924049eba157a56121b4ebff5c36ffe20c36eac1fa2174ca86356`

The baseline's reference alignment remains a partial-body diagnostic; the
retained body's audit is same-index positional proof. No linked-image, data
placement or runtime equality is claimed.

## Bounded controls

The record preserves **24 forward observations / 23 distinct sources**, one
explicit alias, and **five final reverse controls**. All compile successfully
with 53 clean references and no reference debt. Controls cover color-copy/reset
placement, direct color assignment, cell and row cursors, selector scope and
zero-branch spelling, and edge-selection order. None of the unrelated cursor
or color changes is retained.

An initial source-generator pattern assertion stopped before compilation or
ledger recording; the corrected formal controls all compiled. These bounded
observations do not establish a compiler limit or exhaust unrelated functions.

## Validation and credit

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,508 records**, zero malformed/current errors, and **13/13 active specs
runnable** with no stale active specs. Full public refresh, separate saved-report
validation and `git diff --check` pass.

Core normalized-exact functions rise **603 to 604 out of 662**. Core fuzzy
agreement rises **93.33% to 93.50%**, and the rounded residual gap falls
**14,571 to 14,059 bytes**. Public normalized credit rises **715 to 716 functions**
and **167,649 to 169,077 bytes**. Public encoded-body credit rises **703 to 704
functions** and **150,289 to 151,717 bytes**: **1,428 new exact body bytes** in
both categories. Linked credit remains zero.

Only this function gains exact classification. All other classifications,
target ranges and measurement identities remain unchanged, with zero regressed
public bytes. The receipt binds the canonical source and actual post-refresh
COFF hash to the public row; complete extracted unlinked bytes, reference-aware
fingerprint and encoded-body proof equal the isolated retained proof.
