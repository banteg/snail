# Exact segment-loader catalog and cursor recovery

`load_segment_definitions @ 0x448160` (`cRSMTracks::Import`) now has
**normalized and relocation-audited encoded-body equality**. Agreement improves
from **68.43501326% to 100%**, with **571/571 instructions**, **1,937 compared
bytes** and **91 strict positional references**. The old candidate had 560
instructions. The **0x114e0 stack probe** and buffer sizes are unchanged.

The [complete receipt](segment-loader-catalog-row-cursor-owners-20260911.json)
contains native/candidate bytes, full sources, same-index references and branch
destinations, controls, decompiler witnesses and fresh corpus comparisons.
Compiler, flags, headers, ABI, extent and matcher are unchanged.

## Source recovery

Rows and row counts are accessed directly through `entries[segment_index]`.
This removes the manually carried row-count pointer and scoped metadata pointer.
VC6 recovers the native catalog-relative row base, including the separate ring
speed expression, without an artificial offset anchor.

One cursor walks the data line, glyphs and options. The row flags are initialized
before advancing past the first delimiter. Each glyph is assigned directly from
`*data_cursor++` into the indexed glyph column. After the closing glyph delimiter,
the row count advances and the suppression check uses `*++data_cursor`. The same
cursor then supplies the option copy and next-line call. All original writes,
checks and helper-call order remain.

The model flag is set after appending the suffix period and before appending
`x`. These source dependencies recover the native flag-register and store
schedule. The original display-name pointer copy is retained; an indexed-copy
intermediary helped identify the combination but is absent from the final source.
The existing unused fourth `sprintf` argument is preserved, as also witnessed
in the mobile parser.

These changes depend on one another. Direct row indexing, a shared cursor and
direct glyph assignment each regress on some earlier parents, yet together
recover the native register lifetimes and addressing. Seven independent reversals
measure their roles in the final exact source:

| Reversal | Normalized agreement | Candidate instructions |
| --- | ---: | ---: |
| Restore metadata-row pointer | 64.4307% | 562 |
| Restore carried row-count pointer | 70.3930% | 574 |
| Restore separate row-text cursors | 77.8265% | 570 |
| Restore separate glyph temporary | 77.9244% | 566 |
| Advance before row-flags initialization | 99.8249% | 571 |
| Restore separate option-cursor advance | 93.2633% | 572 |
| Set model flag before suffix period | 94.3958% | 571 |
| All seven | 68.4350%; baseline fingerprint restored | 560 |

All reversals retain 91 clean references. Formatting preserves the exact
reference-aware function fingerprint. Mobile confirms the parser/option graph,
but later ports allocate row and glyph arrays rather than owning the Windows
inline layout. Native Windows instructions establish the recovered addressing
and error tails. Original names and a unique authored spelling remain unproved.

## Full encoded proof

The native extent is **1,952 bytes**, `[0x448160,0x448900)`. The compared body
is **1,937 bytes**, `[0,1937)` or `[0x448160,0x4488f1)`, including every real
out-of-line error path after the ordinary return. Only fifteen recognized
terminal-padding bytes, `[1937,1952)`, are excluded. There are no unexplained
or inline data ranges.

All 571 instruction pairs have equal indices, offsets, sizes and normalized
instructions. All 91 references pass strict same-index operand kind/slot and
target-identity checks before their 91 external relocation fields are masked.
All **46 local branches** remain inside the mapped body, and their actual
encoded displacements agree. No ordinary instruction or SIB bytes are masked.

Concatenating the independently audited instruction bytes reproduces both
hashes in the complete encoded-body proof:

`43fdeaa8bdd20de71439ca167f41458c55549f8d8c2728e556cbc32fcb635729`

The baseline reference alignment remains diagnostic; the retained body has
strict positional proof. This certifies the compiled body under the recorded
build, not linked-game placement, arbitrary resource behavior or parser safety.

## Controls

The receipt preserves **68 forward observations / 67 distinct sources**, one
explicit source alias and **eight final reverse controls**. All formal sources
compile. Two rejected guarded-outer-loop controls duplicate five candidate-only
file-load/ID references each. They retain 91 aligned references but carry five
unaudited entries; their full audits are preserved and they receive no credit.
All other controls and the retained source have 91 clean references.

Controls cover direct catalog/row access, borrowed entries, name and file
cursors, glyph and option traversal, initialization order, model suffix stores,
loop forms and counter scopes. A script-import marker error stopped before any
compiler invocation or ledger recording and was corrected separately from the
measured controls. Finite results establish no compiler limit.

## Original-code execution

The existing [loader corpus harness](loaders-native-corpus-20260909.md) is
rerun against this exact source in both modes. All **133 shipped segment files**
and **53 level files** pass: two object-fill patterns and two galaxy-metadata
states produce **212 level executions per executable**. The synthetic segment
and three synthetic levels extend coverage to **224 executions per executable**.

Each mode runs four executables: recovered source, then controls substituting
the original segment importer, level loader or slot copier. Complete catalog,
level and galaxy-owner bytes, ordered resource requests and diagnostics agree.
The one-byte catalog corruption control is detected without unrelated byte or
log changes. The receipts bind the current source/config/dependency hashes,
original-code verification, linked source bytes and fixture identities.

Execution uses Wibo and harness file/resource callbacks. The deterministic zero
tail, resource identifiers and selected malformed cases remain the explicit
limits described by the original harness report. These comparisons neither
validate arbitrary parser inputs nor add linked-game credit; new instruction
credit comes from the separate full-body proof above.

## Validation and credit

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,510 records**, zero malformed/current errors, and **13/13 active specs
runnable** with no stale active specs. Full public refresh, separate saved-report
validation and `git diff --check` pass. The two complete corpus receipts above
are bound to the retained source and its complete extracted object bytes.

Core normalized-exact functions rise **604 to 605 out of 662**, fuzzy agreement
rises **93.50% to 93.70%**, and the rounded residual gap falls **14,059 to 13,443
bytes**. Public normalized credit rises **716 to 717 functions**, **169,077 to
171,014 bytes**. Public encoded-body credit rises **704 to 705 functions**,
**151,717 to 153,654 bytes**. Both gain **1,937 exact body bytes**, excluding
padding. Linked credit remains zero.

Only this function gains exact classification. All other classifications,
target ranges and measurement identities remain unchanged, with zero regressed
public bytes. The receipt binds the actual post-refresh canonical COFF hash to
the public row; complete extracted bytes, reference-aware fingerprint and the
encoded-body proof agree with the independently compiled retained source.
