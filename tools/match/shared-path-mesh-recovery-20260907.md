# Shared path-mesh recovery, 2026-09-07

The repeated Windows mesh-generation body remains a major source-recovery
frontier. Its behavior is represented in the scratches: allocate a vertex bank
and paired quads, generate ordinary and terminal vertices, assign each side's
indices and texture, and publish the UV corners. An original common source
structure that reproduces this body across the family has not been established.

The current dashboard has 29 partial path builders with about 17.1k fuzzy-gap
bytes. That includes their individual path calculations; it is not a measurement
of the shared mesh tail alone. These builders remain within the existing
662-function core scope.

## Retained progress

| Builder | Before | Current | Candidate / native instructions | Prefix | Clean references |
| --- | ---: | ---: | ---: | ---: | ---: |
| Twister | 85.78% | 86.94% | 678 / 677 | 129 | 49 |
| Twister2 | 85.78% | 86.94% | 678 / 677 | 129 | 49 |
| Sweep | 84.66% | 85.58% | 652 / 652 | 32 | 37 |

All three recover the face counter's initialization before the width guard.
Twister's guarded inner loop additionally removes a redundant width test and
exit. Sweep already used a guarded do-loop; moving only its initialization
restores the native row-UV conversion temporary. Full assembly comparisons
localize these changes to their face preheaders, and reverse probes reproduce
the preceding results. Compiler profiles, reference rules, types, and shared
vector operators are unchanged.

S-bend remains 91.10%, with its first 443/579 instructions exact. Its remaining
differences are in face generation. That makes it a useful complete-function
control for mesh source changes, while its current body is not assumed to be
the original source of every sibling.

## Complete-operation controls

The native checkerboard tests retain separate branches even when both arms
use the same texture. A plausible source hypothesis is a general routine with
independent front-even, front-odd, back-even, and back-odd inputs, specialized
by these callers to two texture values. Earlier controls moved only the texture
selection operation. This batch tests the entire allocation/vertex/face body.

Nineteen variants cover the existing body with four texture inputs and one
complete S-bend body with either two or four inputs. A further 26 variants use
an inline `cRPath` member boundary with the same body choices and texture
contracts. Every variant compiles with a clean reference audit.

| Builder | Retained source | Common S-bend body | Result of adding four texture inputs or a member boundary |
| --- | ---: | ---: | --- |
| S-bend | 91.10% | control source | Same comparison metrics |
| Twister / Twister2 | 86.94% | 86.79% | Same corresponding metrics |
| Snake | 88.19% | 87.58% | Extracting the existing body also gives 87.58% |
| Slalom / SlalomBig | 80.66% | 75.02% | Same corresponding metrics |
| Sweep | 85.58% | 85.58% | Same corresponding metrics |

The common-body Sweep result initially improved 84.66%. Its separate 15-form
scope interaction sweep identified the single retained counter change above.
Nested terminal arithmetic, direct versus named-next column advancement, and
paired parity inversion add no gain. Equal metrics do not imply byte identity:
the parity forms can exchange `JE` and `JNE` while preserving both branches'
equal texture values.

The four-input and member forms do not recover the native cold checkerboard
continuations. The general-routine hypothesis remains unproven. The temporary
member name `RebuildStripMesh` is descriptive, not a recovered authored symbol.
No common helper or shared type/header change is promoted.

## What remains to recover

The face bodies still differ in branch-local address formation, texture-call
continuations, and UV value allocation. S-bend and Slalom also differ in where
native code places the quad's zero header store relative to the winding branch.
A common source may compile differently in each caller, so these observations
do not establish separate original implementations.

The full-body tests show that changes in this mesh code can affect earlier
caller allocation: the common Slalom form shortens the exact prefix from 48
to 42 and grows from 695 to 701 instructions against 696 native. Whole-function
and cross-builder checks remain necessary even when a local mesh region looks
better. The inspected S-bend mobile exports omit this Windows mesh phase and
therefore do not directly supply its original helper structure.

Reproducible recipes live in each of the seven scratch directories:
`whole-mesh-checkerboard-inputs-and-common-body-20260907.json` and
`whole-mesh-inline-member-ownership-20260907.json`. Sweep's minimal recovery is
isolated in `common-mesh-scope-interactions-20260907.json`. Their hash-bound
receipts and reverse controls are retained in the corresponding ledgers.
