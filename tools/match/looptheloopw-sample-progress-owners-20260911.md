# LooptheloopW sample progress and mesh recovery

`initialize_looptheloopw_path_template_pair` improves from **74.39353100% to
92.71255061%** on the unchanged **2,736-byte** native span, gaining **501.2084
fuzzy-weighted bytes**. Its normalized prefix grows from **10 to 118
instructions**, all **55 references** remain clean, and the native **0x60**
stack allocation is preserved. The candidate has **737/745 instructions**,
versus **739/745** before: the instruction-count deficit grows from six to eight.
The function remains partial and receives no new exact credit.

## Retained source

The selected skeleton variant is materialized as a local ordinary method.
Fresh raw COFF function bytes prove that materialization alone is neutral.
The W-specific roll calculation and both local-Z rotations remain part of the
curved sample pass, with the same call order and primary/secondary owners.

A shared `sample_f` local holds the converted logical sample index in the
approach and curved passes. This recovers the native early scalar stack homes:
approach/sample progress at **0x10**, wiggle at **0x14**, and curve count at
**0x18**. The approach uses `loop_wiggle * (sample_f / 7.0f)`, producing the
native reciprocal multiplication before the wiggle multiplication. Both the
shared lifetime and the expression grouping have measured reverse controls.

The delta index is initialized before its positive-count guard. Mesh generation
uses direct sample arrays, double lateral arithmetic, ordinary vector scaling
and position addition. The terminal endpoint adds a one-unit forward vector to
the previous sample position, recovering the native Y word copy and terminal
arithmetic. Face generation initializes the winding index before U coordinates
and separates topology/texture dispatch from UV dispatch. All winding indices,
field writes, and both checkerboard texture-call paths remain present.

These are local source changes. Shared headers, compiler flags, reference maps,
target spans and matcher rules are unchanged. The adjacent plain Looptheloop
scratch is unchanged.

## Normalized prefix versus encoded prefix

The first **118 instructions** match the canonical normalized comparison.
The first **109 instructions / 432 bytes** additionally pass a separate
positional, relocation-audited encoded comparison: native
**0x41bb40..0x41bcf0**, candidate **[0, 432)**, with exclusive upper bounds.
All **13 references** in that interval resolve at the same instruction indices
and operand fields; the receipt records every raw and audited instruction.

The longer normalized prefix contains five different SIB encodings at indices
**109, 111, 113, 115 and 117**. These swap the base/index roles in equivalent
scale-one addresses, but their bytes differ. For example, instruction 109's
native `d99c0790000000` becomes candidate `d99c3890000000`. The 118-instruction
region is therefore not claimed encoded-exact. Both the successful shorter
proof and the longer encoding diagnostic are preserved.

The first normalized mismatch is target instruction **118**, offset **483**,
in the departure Identity address preparation. Additional departure/curve
address preparations and call scheduling account for remaining differences.
Mesh vertex and width stack slots **0x28 and 0x78** are exchanged, and two
checkerboard branches have opposite conditions. Later local branch destinations
also shift. These remain open source questions, not a compiler-limit claim.

The full native comparison covers **[0, 2725)**. Recognized terminal padding
**[2725, 2736)** is excluded, with no unexplained target ranges. The full-body
reference audit remains the partial alignment diagnostic; only the separately
asserted 109-instruction prefix is a positional encoded proof. No exact suffix,
whole body, linked image, or runtime identity is claimed.

## Coupled controls and tradeoffs

The forward record contains **66 observations / 63 distinct full sources**,
with three duplicate-source labels mapped explicitly. It includes all 31
nonempty combinations of approach, departure, delta, mesh and face changes;
shared sample-float controls; natural division and half-angle expressions; and
all seven combinations of three shared integer-counter sites. Every group's
fixed source and complete results are retained.

Mesh and face transfers alone reach 80.03% and 83.52%; their combination reaches
89.77%. The shared sample float then restores the early native stack homes.
Extending that float into the departure pass does not provide the same prefix
on the measured departure-owner source. Merely naming the half-angle or
inlining the curved sample conversion is neutral for the examined baselines.
These controls establish local observations, not an exhaustive source search.

| Independent reversal on the retained source | Match | Instructions | Prefix |
|---|---:|---:|---:|
| Old approach multiplication order | 94.21265141% | 741 | 44 |
| Separate sample float locals | 88.39406208% | 737 | 10 |
| Delta index inside guard | 92.57759784% | 737 | 118 |
| Original mesh owner block | 88.06473365% | 738 | 118 |
| Float lateral | 89.42760943% | 740 | 118 |
| Endpoint constructor | 90.66305819% | 733 | 118 |
| Joined topology and UV | 86.29304524% | 736 | 118 |
| Late face-index initialization | 81.02633356% | 736 | 118 |

The higher **94.21%** reversal changes the native arithmetic at instruction
44 by multiplying by the wiggle before the reciprocal. It is preserved as a
full diagnostic source and byte snapshot. Its higher aggregate score and
closer instruction count do not establish a more faithful body. The retained
92.71% source preserves the recovered native arithmetic and encoded prefix;
its larger instruction-count deficit is explicit.

The shared sample float and natural approach division were also tested in
three complete plain-Looptheloop controls. All retain 94.4444%, 719/721
instructions, prefix 159 and 49 clean references. Sharing the float retains
the same code hash; division spellings have different code hashes despite
equal normalized metrics. These controls do not receive encoded-equality
claims or change the plain sibling's source.

## Inspectable evidence

The [receipt](looptheloopw-sample-progress-owners-20260911.json) retains complete
baseline, materialized, retained and higher-score diagnostic sources; full
native and unlinked COFF bytes; separate addressed instruction arrays; reference,
range and stack diagnostics; both prefix checks; complete grouped forward and
reverse results; source aliases and recipe hashes; complete Windows IDA/Binary
Ninja and Android/iOS witnesses; and the proof scripts. Canonical recipes retain
all distinct source controls for review and replay.

## Validation and progress

All **785** scratch builds/status checks pass. The strict experiment ledger has
**2,482 records**, zero malformed or current strict errors, and all **13** active
recipes runnable. A full forced public source/evidence refresh and a separate
saved-evidence validation pass. `git diff --check` passes.

Core fuzzy matching rises **91.94% to 92.10%**; the residual fuzzy gap falls
**18,743 to 18,242 bytes**. Exact core functions remain **602/662**. Public
normalized credit remains **714 functions / 165,216 bytes**, and encoded credit
remains **703 / 150,289 bytes**. Only LooptheloopW's public ratio changes. There
are no exact gains or regressions, changed measurement identities, or changed
target spans. Linked-code credit remains zero; data and final-image identity
remain unmeasured.
