# cRBorder::MouseTest @ 0x404580

Current recovery: semantic-complete with an unresolved source-shape difference. Live Windows
analysis establishes an unsigned-byte `thiscall` member, while Android and iOS
independently retain `cRBorder::MouseTest()` in `Border.o`.

Ordinary widgets test the player-zero cursor against padded layout bounds.
Texture-backed widgets map the cursor into a borrowed `TgaImageView`, clamp the
sample coordinates, and accept a zero mask byte. The sprite manager getter,
cursor owner, TGA layout, and relevant `cRBorder` fields are independently
corroborated by exact siblings and both mobile bodies.

Focused VC6 result: **98.29%**, exact 117/117 instruction parity, prefix 73/117,
with all five relocation operands audited and clean. Native and candidate differ
only in which dead multiplicand register retains the final row product; 43
recorded natural source forms leave that isolated choice unchanged or regress.

The matcher source now uses the authored `MouseTest` method and exact VC6 symbol
`?MouseTest@cRBorder@@QAEEXZ`; `border_mouse_test` remains only the stable
scratch and Windows-address identity.

## 2026-09-05 bounded source-expression probes

Nineteen pixel-payload/dimension-width combinations and twenty-four clamp-expression combinations do not improve the 98.29% baseline. Direct payload access can be byte-neutral; the dead-register choice for the final row product remains unresolved.

The recorded specifications and experiment receipts preserve these negative
results. They do not establish source exhaustion or compiler provenance.

## 2026-09-05 additional source-shape checks

Twelve ordinary inline texel-clamp operations (return, reference and pointer forms, applied to either or both coordinates) do not improve 98.29%. The final row/width multiply allocation remains open.

Eight whole-function hit-result lifetimes (boolean, byte or integer locals, branch/expression publication, and direct mask returns) regress from 98.29%. The unsigned-byte public return declaration is unchanged.

## 2026-09-05 continued 590-match investigation

Four ordinary mask-sampling operations test image ownership or explicit row dimensions. Explicit dimensions are neutral at 98.29%; loading the width through the image regresses to 84.26%. All five references remain clean. No helper is retained.

These receipts bound the tested forms and do not establish source exhaustion.


## 2026-09-05 diagnostic-export batch

Seven pixel-address forms consume width, use row pointers, separate the 18-byte header, or convert row/column coordinates to byte strides. All reproduce the baseline's raw extracted code and relocation identity, including the incorrect `imul eax, esi` destination. Rewriting only the final address calculation adds no new generated-code hypothesis.

Six inline clamp forms return the selected coordinate/bound by const reference, for X, Y, or both. They form three code groups and regress to 66.94–78.66%, with all five references clean. No helper is retained. The canonical 98.29% body and native `imul esi, eax` difference remain open.

The receipts bound these hypotheses only. No new exact match or unsupported ownership/return contract was inferred.


## 2026-09-07 five-function campaign evidence

Eighteen coordinate/dimension lifetime variants do not improve 98.29%.
They vary X/Y normalization and dimension availability while preserving getter
and conversion order. The native row-product destination remains unresolved;
no source or type change is retained.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.

## 2026-09-07 continuation: unchanged-source compiler comparison

Recorded msvc6.0 and msvc6.3 probes preserve the current extracted code and
comparison metrics. No compiler setting or source change is retained. See the
[profile controls](../rebuild_game_archive_if_needed/profile-controls-20260907.md)
for component provenance, exact neighbors, and the limits of this comparison.
