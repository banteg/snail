# Track-cell entry anchor, outer loop and segment ownership

`populate_runtime_track_cells_from_segments @ 0x435eb0`
(`cRSubGame::BuildLevel`) improves from **85.88149232% to 86.13245518%**.
The retained source has **1,243/1,246 instructions**, the existing **76-instruction
prefix**, **165 clean references**, and the unchanged **68-byte frame**.
The previous source had 1,244 instructions. This function remains partial.

The [complete receipt](trackcell-entry-guard-segment-owners-20260911.json)
contains five source/byte snapshots, all source controls and their results,
native/mobile witnesses, selected positional encoded proofs, typed-owner
neutrality checks, and final public evidence binding. Compiler, flags, headers,
ABI, matcher policy and function extent are unchanged.

## Source recovery

The entry-tile branch resets X before evaluating its row Z anchor. VC6 now stores
the float anchor with `fst` while retaining the x87 value for the following
subtraction. Previously it emitted `fstp` and reloaded the rounded float with
`fld`. Windows explicitly retains the value through that subtraction. The
half-integer anchors for valid row indices 0 through 3199 are exactly
representable; the recovery also restores the native intermediate lifetime.
There is no extra load, temporary dependency or register constraint.

The existing early return for a nonpositive row count now guards a `do` outer
loop. The loop still tests the current count after processing a segment and
retains every inner row/segment limit check. This restores native's EAX load/test
of the initial row count. No work moves across a callback or outside its guard.

The selected segment is now a borrowed `SubSegment*`. First, last, sequential,
random and scratch segments are selected through their owning arrays and fields.
Row metadata, visited state, source names, heading angle and authored flags use
the established segment fields. The angle uses the existing union's float view;
the glyph and payload traversals retain their byte cursors where required.
There is no layout or storage-ownership change.

Typing is byte-neutral: the complete candidate byte array and every instruction
record equal the untyped recovered parent. Two compiler-generated local table
names change, so their reference-aware fingerprints are intentionally different.
The proof maps those names using identical literal remap contents and ordered
jump destinations, with the same native table identities. It does not mistake
equal scores for equal bytes.

| Independent reversal | Agreement | Candidate instructions |
| --- | ---: | ---: |
| Previous entry reset/anchor order | 86.0278% | 1,244 |
| Previous outer `while` loop | 85.9861% | 1,243 |
| Previous raw segment and flag access | 86.1325% | 1,243 |
| Complete baseline | 85.8815% | 1,244 |

All four reversals retain 165 clean references. The full reversal restores the
baseline function fingerprint. The neutral typing reversal is explained by the
complete-byte and table-identity proof above.

## Selected encoded proof

The native extent is `[0x435eb0,0x437270)`, **5,056 bytes**. The matcher compares
`[0,5042)` and excludes only **14 terminal padding bytes**. The comparison
includes the 112-byte jump table, 94-byte glyph remap and internal alignment;
there are no unexplained target ranges.

These local certificates verify instruction bytes after strict same-position
operand-slot, kind and reference-identity checks. Only audited relocation fields
are masked; ordinary instructions and SIB bytes remain visible. Offsets are
relative to the function start and intervals are half-open.

| Region | Native range | Candidate range | Instructions | References | Branches |
| --- | --- | --- | ---: | ---: | ---: |
| Existing prefix | `[0,247)` | `[0,247)` | 76 | 9 | 11 |
| Recovered initial row test | `[791,804)` | `[791,804)` | 3 | 0 | 0 |
| Recovered entry x87 lifetime | `[4281,4310)` | `[4295,4324)` | 5 | 3 | 0 |

These selected instruction regions cover **289 native bytes**. The 94 literal
lookup bytes also agree under the unchanged table-recognition policy. This is
not a claim that only those regions agree, nor a certification of the remaining
body. All remaining body bytes stay in the matcher comparison. The full
165-reference alignment is retained as a diagnostic for this partial function;
only the selected regions have local positional proof here. Public whole-function
exact and linked credit do not increase.

## Controls and validation

The receipt preserves **80 forward observations**: **78 distinct successful
formal sources** and two malformed typed controls. An unsigned reference to a
signed field and an angle union used without its float member fail compilation;
their complete sources and errors are retained outside the formal recipe.
Corrected controls compile. Seven controls introduce reference debt and are
rejected, with complete audits retained.

A lane bit-decomposition diagnostic scores **86.1527%**, above the retained
source, but adds non-native masking/reassembly instructions. A low-byte alias
adds a stack round trip. A vector-constructor control grows the frame from
68 to 80 bytes. None is retained merely for its score. These bounded results
do not establish a compiler limit; lane setup, attachment stamping, position
ownership, stack-slot allocation and other remaining differences stay open.

All **1,104 tests** and **785 scratch checks** pass, with zero type findings.
The strict ledger has **2,518 records**, zero malformed/current errors and
**14/14 active specs runnable**, with no stale active specs. Full public refresh,
separate saved-evidence validation and `git diff --check` pass. The receipt binds
the canonical source/COFF to the public row and isolated byte proof. Core exact functions remain
**606/662**, while fuzzy agreement rounds **93.97% to 93.98%** and the rounded
residual gap falls **12,625 to 12,613 bytes**. The source-weighted gain is **12.6887 bytes**. Only this function's public ratio
changes; exact classifications, target ranges and measurement identities are
unchanged. No full builder execution harness is claimed.
