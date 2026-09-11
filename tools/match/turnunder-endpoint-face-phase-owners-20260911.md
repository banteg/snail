# Turnunder endpoint, face and phase recovery

`initialize_turnunder_path_template_pair` improves from **78.45705968% to
95.84850692%**, with **686/687** candidate/native instructions instead of
**687/687**. All **45 aligned references** remain resolved. The function
remains partial, but its encoded prefix grows from **56 instructions / 213
bytes** to **80 / 309 bytes**, and a **330-instruction / 1,117-byte suffix**
passes a fresh relocation-audited encoded comparison.

## Source recovery

- Give the departure endpoint a shared `endpoint_index`. The two departure
  samples start there, and the curve interpolates toward the same seeded
  endpoint. VC6 now retains its offset instead of recomputing it at curve entry.
- Use an integer `face_offset` for face-array expressions. The old face pointer
  was prepared before branch dispatch and held across the texture call.
- Store each face header inside its topology branch. Coupled with indexed face
  expressions, this recovers native address and register ownership.
- Keep the final V coordinate in each UV branch, alongside the other seven
  UV components. Together these changes recover the native mesh/face suffix.
- Reuse `sample_step` across the entrance Z and curve phase calculations.
- Express curve iteration with its existing positive guard and a `for` loop.
  This recovers the native count load before the curve condition; its remaining
  preheader store ordering is still different.

The native sample/control graph and endpoint interpolation are also supported
by the preserved Android/iOS witnesses. The source forms do not identify
original local names or a unique authored spelling. The source retains its
six-argument Windows ABI, compiler flags, shared headers, reference mappings,
function extent and matcher. Existing force-inline helpers are unchanged
except for the face body. `sample_step` naming and the wrapped face-index
expression are separately proven neutral in the complete reference-aware
function fingerprint.

## Byte and positional proof

The receipt retains complete native bytes, raw unlinked candidate function
bytes, separate full instruction arrays, source/configuration/COFF identities,
all 45 alignment diagnostics, and strict positional region audits. External
relocation fields are masked only after proving operand positions, kinds and
reference identities. Local branch displacements are retained after proving
paired instruction destinations inside each audited region.

The baseline prefix is native **[0x427fe0, 0x4280b5)**, candidate **[0, 213)**,
with **seven references**. The retained prefix is native
**[0x427fe0, 0x428115)**, candidate **[0, 309)**, with **eight references**.
Neither has hidden encoded differences. The contiguous prefix grows by
**96 bytes**; this is not a claim that all 96 were previously unequal in
smaller matching islands.

The encoded-equal suffix is native **[0x42853a, 0x428997)**, candidate
**[1368, 2485)**. Native instruction indices **[357, 687)** map to candidate
**[356, 686)**: **330 instructions / 1,117 bytes**, with **13 strict positional
references** and **19 verified local branches**. It includes terminal delta
stores, mesh allocation and vertices, face construction, `CalcLengthZ`, the
return, and the reachable texture-call block after the return. That post-return
block remains compared. This is region-relative correspondence, not equality
of whole-function instruction indices or offsets.

The larger suffix beginning with the delta loop, native
**[0x428461, 0x428997)** and candidate **[1151, 2485)**, has **388 instructions /
1,334 bytes** and 15 clean positional references. Its normalized instructions
agree, but **ten SIB bytes differ** in delta-loop addressing. Their native
instruction indices are **306, 307, 308, 324, 327, 329, 330, 331, 347 and 351**.
The complete instructions, raw bytes and exact differing-byte positions are
preserved in JSON. Those bytes are not excluded or normalized away. The larger
region is not encoded-exact. A typed-array delta control has identical full
function bytes and fingerprint, including those same ten differences.

The native extent is **2,496 bytes**, **[0x427fe0, 0x4289a0)**. Comparison
covers **[0, 2487)**; **[2487, 2496)** is recognized terminal padding. There
are no unexplained or inline-data ranges. Before and after use the native
**0x54-byte** frame. Full-function normalized/encoded exactness, linked code,
data, final-image identity and runtime equivalence are not claimed.

## Remaining differences and bounded controls

The first difference is at instruction **80**: the candidate stores the updated
entrance phase counter before the last secondary delta-length store. Native
performs those stores in the opposite order. Departure Identity receiver setup,
curve preheader ordering, the up-vector temporary copy, and delta-loop SIB
encodings also remain open. No compiler limit follows from these controls.

The forward recipe retains **71 distinct full sources from 72 observations**.
There are eight endpoint controls, 12 face-loop controls, nine face-pointer
controls, eight lifetime controls, 12 coupled controls, 11 native-schedule
controls, six final source controls, four encoded-address controls, and two
retained/formatting observations. The unformatted retained observation repeats
the earlier curve-for source and is recorded as an alias.

All formal controls compile. Three nonretained controls carry reference debt:
fully repeating the face-index expression in the separate/merged dispatch
variants gives **45 clean plus two unaudited references** each; advancing the
entrance Z counter inside the cast gives **44 clean plus three unaudited**.
They remain bounded rejected controls. The other 68 distinct sources have
45 clean references. Separate face counters, physical entrance cursors,
secondary vector accumulation, alternate roll constructors and helper shapes
remain available with their measured results. Equal scores are not treated
as proof of equal bytes.

Each of six independent reversals regresses from the retained source:

| Reversed source change | Match |
|---|---:|
| Shared endpoint index | 76.32150615% |
| Indexed face expressions | 81.14035088% |
| Branch-local face header | 78.21637427% |
| Complete UV branches | 85.92268417% |
| Shared sample phase | 95.48104956% |
| Curve `for` loop | 95.77259475% |
| All six together | 78.45705968% |

The all-reverse control restores the baseline function fingerprint exactly.
The recipes contain the full source at each designated parent and each
variant, so the observations remain replayable after later source changes.

## Validation and progress

All **785 scratch checks** pass with zero type findings. The strict ledger
has **2,496 records**, zero malformed/current strict errors and **13 active
recipes, all runnable**. Full public refresh, separate saved-evidence
validation and `git diff --check` pass.

Turnunder gains **434.09 fuzzy-weighted bytes**, reducing its gap from **537.71 to
103.62 bytes**. Core fuzzy rises **92.55% → 92.69%** and its rounded residual
gap decreases **16,914 → 16,480 bytes**. Exact count stays **602/662**.
Only Turnunder's public ratio changes; all exact classifications, target spans and
measurement identities remain unchanged. Public exact credit stays
**714 functions / 165,216 normalized bytes** and **703 / 150,289 encoded
bytes**; linked-code credit remains zero.

The receipt reads the actual COFF object from the completed public refresh,
checks its recorded hash, and binds it to the isolated proof through the
canonical source hash, complete extracted bytes and reference-aware function
fingerprint. Different COFF container hashes are preserved explicitly.
