# Cage2 curve and mesh vector recovery

`initialize_cage2_path_template_pair @ 0x42e720` improves from
**75.57603687% to 82.96067849%**. Candidate/native instruction counts change
from **654/648 to 649/648**, while the strict **10-instruction / 27-byte encoded
prefix**, native **0x54** stack allocation and **46 clean references** remain.
Both whole bodies are partial.

The [complete receipt](cage2-curve-mesh-vector-owners-20260911.json) preserves
native and candidate bytes, full sources, reference and range proofs, source
controls and four decompiler witnesses. Compiler, flags, headers, ABI, extent
and matcher are unchanged.

## Source recovery

The mesh lateral value remains live on the native x87 stack across the vertex
branch. A `double` local and vector multiplication recover that lifetime and
both lateral-offset expressions without the old float spill/reload sequence.
The existing point and endpoint constructors remain; their operator/copy
alternatives were measured but do not improve this source.

The interior loop carries an advancing `sizeof(AttachmentSample)` byte cursor
beside the logical sample index. Its bound and first-point test use that cursor,
as the Windows loop does. One converted Z value supplies both lanes. The
orientation branch emits the derived basis first and the initial identity case
second. These dependencies matter together: several isolated transfers regress,
but the complete retained combination improves agreement and reproduces the
native Z spill/reload and branch order.

The face column reuses the dead incoming width parameter's local lifetime,
matching its native argument-slot conversion home. The mesh and face column
roles remain separate. The delta pass uses a physical byte cursor and advances
its logical completed count after the secondary length assignment in source;
VC6 emits the native increment between Normalize and the final store. This
recovers the complete delta and allocation region.

All seven groups have independent reverse controls. Formatting preserves the
reference-aware function fingerprint. Native instructions support these local
control and value relationships; they do not establish original names or a
unique source spelling. Mobile uses 30 samples while Windows uses 22, and
mobile omits the Windows mesh and unused fourth argument. Those differences
remain explicit in the source witnesses.

| Independent reversal | Normalized agreement |
| --- | ---: |
| Extended lateral lifetime | 81.4758% |
| Both lateral vector multiplications | 82.0355% |
| Physical curve traversal and bounds | 70.8783% |
| Shared converted Z | 58.9052% |
| Derived-orientation-first branch | 73.9599% |
| Face column lifetime | 80.9561% |
| Physical delta traversal and schedule | 82.8065% |
| All seven | 75.5760%; baseline fingerprint restored |

## Positional encoded proof

The native extent is **2,432 bytes**, `[0x42e720,0x42f0a0)`. The compared body
is `[0,2422)`, including the real out-of-line post-return texture branch.
Only ten bytes of recognized terminal padding are excluded. There are no
unexplained or inline ranges.

Two separately audited regions have equal encoded bytes after external
relocation checks:

| Region | Native / candidate instruction ranges | Native / candidate body offsets | Bytes | Strict references |
| --- | --- | --- | ---: | ---: |
| After the mirror flag through curve scalar setup | `[11,101)` / `[11,101)` | `[31,421)` / `[30,420)` | 390 | 12 |
| Deltas and allocation | `[260,376)` / `[261,377)` | `[1093,1526)` / `[1082,1515)` | 433 | 4 |

Each paired instruction has equal size. The first region's candidate offset
is one byte earlier; the second is eleven bytes earlier. Both delta-region
branches land inside that region, and their actual displacements remain
compared. These mappings are explicit; they are not whole-function positional
equality. The 390-byte region includes already matching code, and neither
region is counted as new whole-function credit.

A separate **69-instruction / 282-byte** orientation block, native `[151,220)`
and candidate `[152,221)`, has seven strict references and equal normalized
instructions, but five raw SIB differences:

| Native / candidate offset | Native / candidate byte |
| --- | --- |
| 650 / 639 | `3a` / `17` |
| 654 / 643 | `3a` / `17` |
| 658 / 647 | `3a` / `17` |
| 719 / 708 | `3a` / `17` |
| 771 / 760 | `38` / `07` |

These bytes are preserved, not masked. This block is not encoded-exact. Other
matching-block proposals whose branches leave their proposed region are saved
as unproved diagnostics; they receive no region-equality claim. The complete
46-reference alignment remains diagnostic, separate from strict region audits.

## Controls and remaining work

The record preserves **95 observations / 94 distinct forward sources**, one
explicit alias, and **eight final reverse controls**. Fourteen forward
diagnostics add an unaudited `fld` from a zero constant when the logical
increment is moved in place. They are rejected and receive no matching credit.
All final reversals and the retained source have 46 clean references.

Controls cover curve bounds and branch order, shared Z, increment placement,
logical/physical delta traversal, mesh lateral and point values, endpoint
copies, direct face arrays, pointer offsets, and mesh/face column lifetimes.
The failed initial coupled-control generator stopped before compilation or
ledger recording and is documented separately from compiler results.

Remaining differences include the mirror-flag store encoding, curve zero and
address formation, orientation SIB bytes and store scheduling, mesh row/column
allocation, width-conversion homes, endpoint scheduling, and face addressing
and parity branches. The full bodies remain partial; no linked code, data,
final-image or runtime equality is claimed. These finite controls do not
establish source exhaustion or a compiler limit.

## Validation and progress

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,504 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh, separate saved-evidence validation
and `git diff --check` pass.

Cage2 gains **179.59 fuzzy-weighted bytes**, reducing its gap from
**593.99 to 414.40 bytes**. Core fuzzy rises **93.19% → 93.25%**;
normalized-exact count remains **603/662** and the rounded residual gap falls
**14,988 → 14,808 bytes**. Only Cage2's public ratio changes. Exact
classifications, target spans and measurement identities remain unchanged.

Public credit remains **715 functions / 167,649 normalized bytes** and
**703 / 150,289 encoded bytes**; linked-code credit stays zero. The receipt
reads the actual COFF from the completed public refresh, verifies its recorded
hash, and binds it to the isolated proof through the source hash, complete
extracted bytes and reference-aware function fingerprint.
