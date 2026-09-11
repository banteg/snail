# Supertramp count, radius and mesh recovery

`initialize_supertramp_path_template_pair @ 0x423f10` improves from
**79.74452555% to 92.01451906%**. Candidate/native instruction counts change
from **544/552 to 550/552**. The strict encoded prefix grows from
**16 instructions / 51 bytes to 37 instructions / 125 bytes**. The native
**0x2c** stack allocation and all **36 clean references** remain. Both whole
bodies are partial.

The [complete receipt](supertramp-count-radius-mesh-owners-20260911.json)
preserves native and candidate bytes, full sources, positional reference and
range proofs, all controls, scripts and four decompiler witnesses. Compiler,
flags, headers, ABI, extent and matcher are unchanged.

## Source recovery

The front/back UV writes now follow the separate topology/texture dispatch.
Both complete UV blocks remain, recovering the native cap and texture branch
layout. Allocation uses `last_segment_index = curve_segments + 7` and derives
its count from that predecessor, reproducing the native add-seven/increment
sequence. The logical curve index is initialized before its guard.

The quantized radius is assigned back into the incoming length parameter after
its input has been consumed. The native stores this radius at the incoming
parameter home, and the mobile witnesses support the same quantization formula.
This recovers that value's native stack home and the adjacent curve-index home.
Original names and a unique spelling remain unproved.

The mesh reads fields directly from `path->primary_samples[row]`, removing the
separate physical sample offset and scoped pointer. This recovers four address
and row-spill instructions. The face column reuses the mesh column's local
lifetime, while the face row retains its separate role; this recovers the
native UV conversion homes. Helpers, scalar orientation writes and typed delta
arrays remain. Whole-source formatting preserves the function fingerprint.

The mobile builders have an extra float center-offset where Windows uses zero,
and their ABI differs. Their sample/control graph supports recovery; the native
Windows `ret 0x1c` establishes the existing seven explicit stack arguments and
Windows instructions establish the mesh tail and stack homes.

| Independent reversal | Normalized agreement |
| --- | ---: |
| Separate UV dispatch | 84.4687% |
| Count predecessor | 91.4701% |
| Curve-index scope | 91.3715% |
| Radius parameter home | 85.1180% |
| Direct mesh arrays | 91.0747% |
| Shared mesh/face column | 89.1107% |
| All six | 79.7445%; baseline fingerprint restored |

Every independent reversal lowers agreement, and all controls retain 36 clean
references. These are dependencies of the final combination: the radius change
alone slightly lowers the score on an earlier direct-array parent but improves
the final source and its native prefix.

## Positional encoded proof

The native extent is **1,936 bytes**, `[0x423f10,0x4246a0)`. The compared body
is `[0,1935)`, including the real post-return out-of-line texture branch.
Only one byte of recognized terminal padding is excluded. There are no
unexplained ranges.

The **45-instruction / 165-byte normalized prefix is not encoded-exact**.
It contains four unmasked SIB differences at equal native/candidate offsets:

| Offset | Native / candidate byte |
| --- | --- |
| 127 | `0f` / `39` |
| 137 | `17` / `3a` |
| 147 | `07` / `38` |
| 157 | `0f` / `39` |

The strict encoded prefix stops before these differences, at **37 instructions,
125 bytes and four positional references**. Baseline had 16 instructions,
51 bytes and two positional references.

The arc, delta and allocation region is separately encoded-equal after strict
external relocation auditing:

| Native / candidate instruction range | Native / candidate body offsets | Bytes | Strict references |
| --- | --- | ---: | ---: |
| `[83,299)` / `[81,297)` | `[315,1116)` / `[311,1112)` | 801 | 20 |

All 216 paired instructions have equal size. The candidate is four bytes and
two instructions earlier, following the lead-in receiver differences. All five
local branches land inside this region; their actual displacements remain
compared. The explicit position mapping does not imply whole-function equality
or 801 newly recovered bytes. No whole-function exact credit is added.

Six other discovered matching blocks have branches leaving their proposed
region. They are saved as unproved diagnostics. The full 36-reference alignment
is also diagnostic, separate from the strict prefix and region audits.

## Controls and remaining work

The record preserves **91 forward observations / 89 distinct full sources**,
two explicit source aliases and **seven final reverse controls**. All compile
successfully with 36 clean references and no reference debt. Controls cover
count and radius expressions, input/local homes, curve scope and traversal,
lead-in addressing, mesh vector lifetimes, direct sample arrays, helper
flattening, row and column lifetimes, UV layout and face loop forms.

Physical delta traversal ties the retained **92.01451906%** normalized score but
adds **ten raw SIB differences** inside the otherwise exact 801-byte region.
Its complete source, bytes and audits are retained as a rejected diagnostic;
the canonical source keeps typed delta arrays. This is additional to the four
prefix SIB differences. Score-neutral loop forms and helper flattening are not
retained. A corrected generator assertion occurred before compilation or ledger
recording and is documented separately from measured compiler results.

Remaining differences include four lead-in scalar SIB bytes, two lead-in
Identity receiver instructions, mesh row/sample-offset stack homes, face UV
preheader scheduling and temporaries, parity operand orientation and JE/JNE
branches. The body remains partial. No linked-code, data, final-image or runtime
equality is claimed. Finite controls establish no source exhaustion or compiler
limit.

## Validation

All **785** scratch checks pass, with **zero type findings**. The strict ledger
has **2,506 records**, zero malformed/current errors, and **13/13 active specs
runnable** with no stale active specs. Full public refresh and separate saved
report validation pass. `git diff --check` passes.

Core fuzzy agreement moves **93.25% to 93.33%**; the rounded residual gap moves
**14,808 to 14,571 bytes**. This function contributes **237.5471 fuzzy-weighted
bytes**, a similarity metric rather than exact-byte credit. Core normalized
exactness remains **603/662**. Public normalized credit remains **715 functions /
167,649 bytes**, encoded-body credit **703 / 150,289 bytes**, and linked credit
zero. Only Supertramp's ratio changes; exact classifications, ranges and
measurement identities remain unchanged.

The receipt binds the canonical source hash and actual post-refresh COFF hash
to the public row. Complete extracted unlinked bytes and the reference-aware
function fingerprint equal the isolated retained proof, independently of COFF
container identity.
