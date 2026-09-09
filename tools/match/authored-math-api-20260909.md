# Authored math calls, 2026-09-09

Thirty-six caller bodies now use `tMatrix::Identity()` and
`tVector::Cross(const tVector&, const tVector&)` through the shared declarations.
Their selected COFF instruction bytes are unchanged. The migration repairs
205 live call relocations that previously used a free fastcall identity shim
or a pointer-argument spelling of the cross-product method.

The recovered canonical callees already expose the authored methods. The
old identity shim passed the matrix in ECX, exactly where the member method
expects `this`; reference arguments retain the cross-product pointer ABI.
Changing the caller spelling repairs real linker names without changing the
generated call sequence. The obsolete shared declarations are removed,
including uses in the shared path-template skeleton.

## Evidence

The [verification receipt](authored-math-api-20260909.json) preserves source,
object, selected-function, header and frontier identities. Each caller has a
recorded native probe and a before/after object comparison. All 36 retain their
whole-function ratio, instruction count, exact prefix and positional reference
audit. Instruction bytes and relocation offsets/addends are identical; the
205 external targets change only to these authored names:

| Previous relocation | Authored relocation |
| --- | --- |
| `?set_matrix_identity@@YIXPAUtMatrix@@@Z` | `?Identity@tMatrix@@QAEXXZ` |
| `?cross_vectors@tVector@@QAEXPBU1@0@Z` | `?Cross@tVector@@QAEXABU1@0@Z` |

Some large callers renumber private `$L` table symbols after the source edit.
Those targets were checked recursively for identical section bytes, offsets,
relocation types, and referenced destinations. They were not accepted by simply
masking their names. The selected-function fingerprint intentionally changes
when an external relocation name changes; equal body bytes are a separate fact.

The complete 785-object frontier changes from 4,423 to **4,628 exact external
definitions**, and from 610 to **405 possible function-name mismatches**.
The 11 explicit function-name mismatches and 2,980 missing storage references
remain. These are reference counts, not additional exact functions or proof
that the complete game links.

After removing the compatibility declarations, the linked RMath control still
passes 23 assertions and its corruption control fails exactly one assertion.
The full Python suite passed 889 tests at this checkpoint; native status,
strict experiment/spec checks, and the shared-declaration ownership test pass.
The port board remains **593/662 exact functions**, with 69 partials.

## Reproduction

The source baseline is commit `26a60b689`. Per-caller before/after sources,
objects, probes and detailed verifications are retained locally under
`artifacts/match/authored-math-api-20260909/`; the tracked receipt records their
hashes and the native metrics. Use the link-frontier command documented in
[README](README.md), and run the RMath control with
`uv run tools/match/link_path_math.py --group rmath --run --runtime-library
<VC6-MSVCRT.LIB>`. Neither operation awards native matching credit.
