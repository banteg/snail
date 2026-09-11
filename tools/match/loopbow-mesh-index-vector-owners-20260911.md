# Loopbow mesh index and vector recovery

`initialize_loopbow_path_template_pair @ 0x42ba80` improves from
**84.25692695% to 93.07304786%**. Candidate/native instruction counts remain
**792/796**, both stack allocations remain **0x9c**, and all **63 references**
are clean. The strict encoded prefix grows from **10 instructions / 27 bytes**
to **22 / 79**. Both the normalized and encoded whole bodies remain partial.

The [complete receipt](loopbow-mesh-index-vector-owners-20260911.json) preserves
the sources, native and candidate bytes, separate instruction arrays, positional
region proofs, full source controls, reverse measurements and source witnesses.
Compiler, flags, shared headers, ABI, native extent and matcher remain unchanged.

## Source recovery

The mesh column loop reuses the existing sample index `i`, while the face pass
keeps its separate counter. This recovers the native integer/float conversion
home used by both sample construction and mesh columns. Combining the face
counter into that same source local regresses the current candidate.

The ordinary row scales its right vector with the authored vector multiplication
operator. Both row branches build their point with vector addition: lateral
offset plus sample position for ordinary rows, endpoint plus lateral offset for
the terminal row. The native terminal calculation loads the endpoint components
as the left-hand vector. The recovered source captures the vertex buffer before
the face buffer, which produces the native buffer-load order after allocation.

All five changes have independent reverse controls. Formatting only the changed
mesh block preserves the reference-aware function fingerprint. The old endpoint
constructor, double lateral value, two mesh branches and face topology/UV
dispatch remain intact. This source evidence does not establish unique original
variable names or spelling.

| Independent reversal | Normalized agreement |
| --- | ---: |
| Ordinary lateral-vector multiplication | 92.5693% |
| Ordinary point-vector addition | 92.9471% |
| Terminal point-vector addition | 92.9471% |
| Mesh column reuses sample index | 85.0126% |
| Vertex buffer captured before face buffer | 92.5693% |
| All five changes | 84.2569%; baseline fingerprint restored |

## Encoded regions

The native extent is **2,944 bytes**, `[0x42ba80, 0x42c600)`. The compared body
is `[0,2939)`; only five bytes of recognized terminal padding are excluded.
There are no inline or unexplained ranges.

Three additional regions agree instruction-for-instruction at the same native
and candidate offsets, including their encoded bytes after strict external
relocation audit:

| Region | Instruction range | Body offsets | Bytes | Strict references |
| --- | --- | --- | ---: | ---: |
| Curve orientation | `[220,336)` | `[932,1347)` | 415 | 18 |
| Rotation and secondary offset | `[343,399)` | `[1369,1565)` | 196 | 8 |
| Deltas and mesh allocation | `[400,524)` | `[1571,2027)` | 456 | 4 |

All local branch targets in these regions are paired inside their region.
Their actual encoded displacements remain compared. No SIB or other hidden
encoding differences are omitted. These are separate region proofs; they do
not claim the intervening instructions agree, or that every byte in the regions
is newly recovered. The full reference alignment for the partial body remains
diagnostic, separate from the strict positional region audits.

## Remaining work

The total-count and floating curve-count stack homes still differ. The adjacent
pivot Z stores have a different schedule. The terminal mesh copy still uses
floating Y transfer where native uses an integer transfer, and some mesh/face
counter and receiver details remain different. No whole-body exact credit,
linked code, data, final image, or runtime claim is made.

The controls cover vector constructors/operators, mesh and face counter reuse,
buffer order, endpoint fields/copies/scopes, and endpoint/curve address owners.
The forward record contains **63 observations / 59 distinct full sources**,
with four explicit aliases; the reverse recipe has **six full sources**.
All recorded sources compile with 63 clean references. Earlier notes describing
a closed scalar or mesh neighborhood are historical finite observations;
they do not establish source exhaustion or a compiler limit.

## Validation and progress

All **785 scratch checks** pass with **zero type findings**. The strict ledger
has **2,500 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh, separate saved-evidence validation
and `git diff --check` pass.

Loopbow gains **259.55 fuzzy-weighted bytes**, reducing its gap from
**463.48 to 203.93 bytes**. Core fuzzy rises **92.87% → 92.96%**;
normalized-exact count remains **603/662** and the rounded residual gap falls
**15,944 → 15,685 bytes**. Only Loopbow's public ratio changes. Exact
classifications, target spans and measurement identities remain unchanged.

Public credit remains **715 functions / 167,649 normalized bytes** and
**703 / 150,289 encoded bytes**; linked-code credit stays zero. The receipt
reads the actual COFF from the completed public refresh, verifies its recorded
hash, and binds it to the isolated proof through the source hash, complete
extracted bytes and reference-aware function fingerprint.
