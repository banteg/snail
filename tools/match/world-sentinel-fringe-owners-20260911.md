# World initializer sentinel and fringe ownership

`initialize_game_assets_and_world @ 0x40acf0` improves from **83.74630178% to
84.02662230%**. The candidate grows from **5,405 to 5,407 instructions** against
**5,411 native**, and the exact prefix grows from **43 to 53 instructions**.
The **300-byte frame**, **1,880 clean references** and **two existing unaudited
vapour-stride entries** are unchanged. The function remains partial.

The [complete receipt](world-sentinel-fringe-owners-20260911.json) contains
five complete source/byte snapshots, 53 successful formal forward sources,
three reversals, native/mobile witnesses, selected positional encoded proofs,
and canonical source/COFF/public binding. Compiler, flags, headers, ABI,
matcher policy and function extent are unchanged.

## Recovered source owners

The inactive-list sentinel is now borrowed through its existing `BodNode`
base. The scratch clears that node's `list_next` and publishes the same pointer
to the free-list head. VC6 emits the native address calculation and indirect
store. The encoded prefix grows from **182 to 233 bytes**, with the same startup
state and operations.

The fringe builder now borrows each `BodBase` from the existing catalog using
its family, direction, row and column indices. This replaces the flat pointer
walk across multidimensional subarrays with access to the actual owned element.
The loops still visit all **8 × 4 × 3 × 3 = 288** slots in the same order,
with the same allocation, procedural arguments and blend-mode publication.
The compiler recovers the native object-field induction, direction-boundary
pointer carry and counter ownership. Android and iOS independently retain
nested indexing for this bank; their different BOD sizes are not transferred.

A local `BodBase&` keeps the source readable. Its complete reference-aware
function fingerprint, instruction records, frame diagnostic and full reference
audit equal those of the direct indexed expression. Equal scores alone are
not used to establish that equivalence.

| Independent reversal | Agreement | Candidate instructions | Exact prefix |
| --- | ---: | ---: | ---: |
| Previous flat fringe pointer | 83.8203% | 5,405 | 53 |
| Previous direct sentinel field access | 83.9527% | 5,407 | 43 |
| Complete baseline | 83.7463% | 5,405 | 43 |

All reversals retain the same two reference residuals. The complete reversal
reproduces the original reference-aware function fingerprint.

## Selected encoded proof

The native extent is `[0x40acf0,0x410710)`, **23,072 bytes**. The matcher compares
`[0,23070)` and excludes only **two terminal padding bytes**. Internal alignment
remains compared, there are no inline tables, and no native ranges are unexplained.

The selected regions below are equal after strict positional operand-slot,
kind and identity checks. Only audited external relocation fields are masked.
Ordinary instruction and addressing bytes remain visible. Offsets are relative
to function start; intervals are half-open.

| Region | Native range | Candidate range | Instructions | References |
| --- | --- | --- | ---: | ---: |
| Extended prefix | `[0,233)` | `[0,233)` | 53 | 12 |
| Fringe setup and allocation | `[21227,21268)` | `[21181,21222)` | 11 | 3 |
| Direction pointer carry and count | `[21338,21352)` | `[21290,21304)` | 5 | 0 |
| Family count | `[21354,21366)` | `[21306,21318)` | 4 | 0 |

These certificates cover **300 native instruction bytes**, including **118 bytes
beyond the previous prefix certificate**. They contain 15 positional references
and no local branches. This does not certify the remaining body or imply that
only these regions agree. All remaining body bytes stay compared; the full
reference alignment outside these regions is diagnostic. No whole-function
exact or linked credit is added, and no complete native execution is claimed.

## Remaining vapour and tail evidence

The native vapour loop reloads its object field after flag updates and calls.
It also reloads the first rocket object's field after each vapour initializer.
Both mobile `Init3` bodies support those per-iteration owners. They are evidence
for the remaining source recovery, not a reason to reuse mobile layout offsets.

Direct vapour-field access clears both unaudited entries (**1,881 clean**) but
reduces agreement to **81.7753%**. Adding the live rocket reload gives **81.4390%**.
The changed loop improves local agreement while altering the later register
cycle, including repeated color argument copies. The complete clean candidate's
source, bytes and reference audit are preserved in the receipt. These forms are
not claimed semantically disproven; they remain unpromoted matching tradeoffs.

Combining those live fields with the sentinel, indexed fringe and indexed input
owners reaches **81.8947%**, 5,398 instructions, prefix 53 and 1,881 clean
references. Indexed input access removes non-native cursor work but affects
later allocation. Named matrices, border traversal and list-flag lifetimes
provide additional bounded controls. None changes the retained matrix/frame
recovery or shared headers.

All **53 forward sources compile** and yield **17 distinct function
fingerprints**. The report preserves all source forms and results, plus three
independent/combined reversals. Twelve forward observations retain the existing
two reference residuals; none introduces an unresolved or mismatched reference.
Finite controls establish no compiler limit. The vapour reloads, input owner,
fringe argument schedule, overlay flags and later register allocation remain open.

## Validation

All **1,104 tests** and **785 scratch checks** pass, with zero type findings.
The strict ledger has **2,522 records**, zero malformed/current errors and
**14/14 active specs runnable**, with no stale active specs. Full public refresh,
separate saved-evidence validation and `git diff --check` pass. The receipt binds
the canonical source and COFF to the public row and isolated byte proof.

Only this function's public ratio changes. Core exact functions remain
**606/662**; fuzzy agreement rises **94.02% to 94.04%**, and the rounded residual
gap falls **12,494 to 12,429 bytes**. The source-weighted gain is
**64.6756 bytes**. Public totals remain
**718 normalized functions / 172,474 bytes** and **706 encoded functions /
155,114 bytes**. Exact classifications, target ranges and measurement identities
are unchanged.
