# P and Turnunder source recovery

Two existing path-builder scratches improve substantially. **Neither is exact**;
`body_byte_exact` remains false and the exact function totals are unchanged.

| Function | Before | After | Instructions before → after / native | Clean references |
| --- | ---: | ---: | --- | ---: |
| `initialize_p_path_template_pair` | 64.60% | 92.85% | 677 → 678 / 679 | 41 |
| `initialize_turnunder_path_template_pair` | 57.23% | 78.17% | 662 → 687 / 687 | 45 |

The combined curated-extent weighted fuzzy gap falls by **1,227.74 bytes**.
Overall core fuzzy progress increases from **89.13% to 89.54%**.

## P builder

The recovery retains the three kind-dependent curve formulas, endpoint centers,
absolute half-distance scale, and the Windows nine-argument `ret 0x24` ABI.
One logical curve counter owns angle generation and the next sample's Z;
a separate physical offset addresses the sample banks. The endpoint helper
borrows both banks and computes its offset from the logical endpoint index.
Previous-sample orientation uses direct vector subtraction and preserves bank
rereads across `Normalize`, `Cross`, and matrix calls. The delta loop keeps its
own independent counter and physical offset.

Branch-local mesh vectors recover the native temporary lifetimes. The face
loop computes row UVs inside the width guard and separates texture selection
from UV assignment. This recovers the native face tail, including the second
texture's alternate branch after the function return. The same source separation
is independently byte-verified in the S-bend scratch; transferring its entire
mesh instead of the relevant face portion was weaker for P.

The first six instructions match. Remaining differences concern prologue and
endpoint index allocation, the curve's secondary receiver, and resulting branch
displacements. The candidate is one instruction shorter than the native body.

## Turnunder builder

The six-sample lead, two-sample departure, opposite endpoint centers,
count-derived radius, negative full-turn angle, and nonlinear under-roll remain
intact. The departure loop uses a bound relative to its initial curve count,
as the native body does. A bank-reference helper retains primary/secondary
field rereads across identity calls.

The primary X expression nests the full-angle and half-angle sine calls in
the native evaluation context. Vector subtraction, physical delta traversal,
and branch-local mesh vectors recover more of the native scheduling. Both
checkerboard texture branches are present, including their equal-texture arms;
this is native control flow, not a new texture-selection policy. The curved
secondary lane still copies only the transform and then applies its up-vector
offset. Unused historical initializer helpers are removed.

The candidate now has the native instruction count and a 56-instruction exact
prefix. Many stack homes, receiver/address calculations, curve and face schedules,
and branch displacements still differ. Equal instruction count is not equality
of the body.

## Evidence boundary

Compiler profile `msvc6.5`, `/O2 /G5 /W3`, shared headers, ABI, and matcher rules
are unchanged. The helper signatures are valid reconstructed source forms,
not claims about unique original source. Earlier unsuccessful controls do not
establish source exhaustion.

All aligned masked-reference entries are clean, but **these are not positional
exact-reference proofs**. P has zero references at identical instruction or byte
positions. Turnunder has 10 of 45 at identical instruction indices and 8 at
identical byte offsets. The remaining references align across unequal code.
The [receipt](p-turnunder-source-recovery-20260911.json) preserves every entry
and these counts explicitly.

The P comparison covers `[0, 2482)` of its 2496-byte curated extent, including
its post-return continuation; only `[2482, 2496)` is recognized terminal
padding. Turnunder covers `[0, 2487)`, excluding only terminal padding at
`[2487, 2496)`. Neither comparison has unexplained target ranges.

The receipt includes complete before/after sources and hashes, the native-image
hash, compiler dependency and generated-code identities, comparison ranges,
reference audits, and complete remaining assembly diffs. Each promotion probe
is also recorded in its scratch's experiment ledger.

## Reproduce and validate

```sh
uv run snail match scratch initialize_p_path_template_pair
uv run snail match scratch initialize_turnunder_path_template_pair
uv run snail match status --check -j 8
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```

To replay either source, write its complete text from the receipt to a temporary
file, verify the recorded SHA-256, and run `snail match probe FUNCTION --source
FILE` with the unchanged compiler profile.

The full status refresh succeeds. Comparing all 785 function rows with the
preceding revision changes only these two scratches. Exact totals remain
572/662 core and 110/120 platform. All 1,016 tests pass without test changes.
The strict ledger and specification checks report zero errors; `git diff
--check` is clean.
