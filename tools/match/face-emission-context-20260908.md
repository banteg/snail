# Face-emission context and VC6 reductions

S-bend remains **91.10%**, 578/579 instructions, with its first 443
instructions exact and all 39 references clean. No source change is retained.

The investigation separates two previously conflated observations. The
unchanged face loop can produce branch-local stride calculation under VC6;
adding its vertex-generation context changes that decision. Reproducing that
one instruction-placement property does not reproduce the native texture-call
continuations or improve the complete function.

## Native controls

The six bodies were read from the live Binary Ninja database, then independently
decoded from the hash-pinned canonical executable by the diagnostic tool.

| Native function | Instructions | Face-stride placement | Cold texture argument continuations |
| --- | ---: | --- | ---: |
| S-bend | 579 | Separate calculations after winding branch at `0x42e566` | 2 |
| Sweep | 652 | Separate calculations after winding branch at `0x4233c6` | 2 |
| Turnunder | 687 | Separate calculations after winding branch at `0x4287e3` | 2 |
| Slalom | 696 | Common calculation and zero-header store before winding branch at `0x41ffdb` | 2 |
| BuildFringe | 318 | Separate fringe emission, no corresponding winding branch | 0 |
| BuildFringeSuperTramp | 421 | Separate fringe emission, no corresponding winding branch | 0 |

The two fringe controls remain exact with 23 and 25 clean references. They
provide established face/texture operations, but do not independently explain
the strip builders' checkerboard control flow.

All four strip builders' front-face parity branches skip 0x49 bytes. The skipped
region includes the ordinary texture argument, the common `Add` call and UV
stores. The alternate path loads and pushes the same texture argument, then
jumps backward to the common receiver load immediately before that call.
Each back-face alternate argument block occurs after the function's return.

For example, S-bend's front branch at `0x42e5cc` jumps to `0x42e617`, whose
three instructions return to `0x42e5d3`; the `Add` call is at `0x42e5d8`.
The back branch at `0x42e67e` jumps to `0x42e70a` and returns to `0x42e689`,
before the call at `0x42e68e`. The current source instead joins both argument
paths before the call in the forward instruction stream.

This repeated control flow is stronger comparative evidence than the stride
placement alone. It does not establish an original helper name or interface.
Slalom also proves that the native family need not place stride calculation
identically in every caller.

## Reduction results

The diagnostic compiles 40 cases, including controls and deliberately incomplete
functions. These are compiler experiments, not runnable game implementations
or source-matching candidates. Counts below refer to extracted instructions;
they do not award any recovery credit.

| Diagnostic | Instructions | Stride calculation | Texture parity paths |
| --- | ---: | --- | --- |
| Complete current S-bend | 578 | Hoisted before winding branch | Join before call |
| Face loops alone | 184 | Branch-local | Join before call |
| Face loops with original member signature | 184 | Branch-local | Join before call |
| Allocation and vertex/face mesh phases | 291 | Hoisted | Join before call |
| Complete S-bend with vertex loop removed | 489 | Branch-local | Join before call |
| Complete S-bend with delta phase removed | 479 | Hoisted | Join before call |
| Face loops with explicit branch-local pointers | 183 | Hoisted | Join before call |
| Complete S-bend with combined texture/UV helper | 577 | Branch-local | Parity branches eliminated |

Removing or adding finalization does not change the reduced address-placement
result. Allocation calls, one vertex copy, and the tested plain-position loops
also retain branch-local calculation. The original vertex loop, even when only
its generated X values are stored, produces the hoist in the mesh reduction.
This identifies a context dependency without claiming which backend pass or
single source lifetime is responsible.

Duplicating all UV publications into both parity arms has the same conservative
code identity as the combined texture/UV helper, both in the reduced face loop
and complete S-bend. It eliminates the parity branches. An inline four-texture
interface specialized to two textures is identical to the reduced baseline.
`else if` and a zero-case/default switch also reproduce the complete baseline's
identity; the other conditional forms add instructions without recovering the
native cold continuations.

Two optimization switches are diagnostic controls only. Disabling global
optimization grows the complete body to 997 instructions; preferring size
changes inlining and reduces it to 217 instructions with helper calls. Neither
supports an alternate production profile. No reduction produces the native
three-instruction cold argument continuation.

## Complete-function transfers

Seven [phase-boundary variants](scratches/initialize_sbend_path_template_pair/vertex-face-phase-boundaries-20260908.json)
test separately inlined vertex/face phases, separate row/column locals, a scoped
vertex loop, and later face-pointer or counter declarations. Moving only the
counter declaration retains the baseline metrics. Separating phases/counters
gives 90.23%, prefix 409; moving the face pointer load gives 82.48%, prefix 18.
All seven retain 39 clean references.

The combined texture/UV helper is also run through the ordinary full matcher
and exported under `artifacts/match/sbend-texture-uv-publication-control`.
It gives **75.43%**, 577/579 instructions, prefix 67, with 39 clean references.
Its local address-placement improvement is therefore rejected. The eight
complete-function controls are retained in the append-only experiment ledger.
No runtime equivalence claim is made for the deliberately reduced bodies.

## Reproduce and inspect

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/probe_face_emission_context.py
```

The [tracked receipt](face-emission-context-20260908/receipt.json) binds the source,
compiler components, transitive headers, launcher, runner, tool and target image.
It records native addresses, body hashes, local instruction windows, all 40
source/code fingerprints and flags. Generated sources, objects, compiler logs,
mixed listings and full assembly stay under ignored
`artifacts/match/face-emission-context-20260908`.

Pattern extraction is deliberately local: a missing recognized pattern is not
proof that no semantically equivalent control flow exists. The specific native
continuations were checked directly against disassembly. The tool does not
modify the canonical scratch or the matching denominator.

Validation: all 40 diagnostics compile, the six native controls evaluate, the
eight full transfers have clean reference audits, and the strict experiment/spec
audit passes. The new tool passes Ruff. The remaining work is source recovery,
with both native continuation shape and whole-function proof required.
