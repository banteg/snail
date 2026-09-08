# Texture-call continuation ownership

S-bend remains **91.10%**, 578/579 instructions, prefix 443, with 39 clean
references. This pass retains no source, header, or compiler change. It expands
the native evidence and records rejected compiler reductions and full controls.

## Native comparison

The hash-pinned Windows image contains the recognized alternate-argument path
in **28 path builders, 55 occurrences**. All except SuperTramp have two.

The recognizer follows a forward conditional branch to `mov register, argument;
push register; jmp receiver`, verifies that the pushed register was just loaded,
and follows the backward jump to the ECX load immediately before a texture
registration call. It does not require a particular parity-test encoding.

The scan completely decodes 748 of 785 manifest spans; 41 decoded spans contain
texture registration calls. The other 37 spans include undecoded bytes and are
listed in the receipt. Positive extents are checked against the normal matcher.
These are positive structural observations, not a claim about all executable
control flow or every source-level equivalent of this pattern.

| Native builder | Instructions | Continuations |
| --- | ---: | ---: |
| `looptheloop` | 721 | 2 |
| `looptheloopw` | 745 | 2 |
| `loopout` | 718 | 2 |
| `hump` | 685 | 2 |
| `dump` | 690 | 2 |
| `dip` | 655 | 2 |
| `screw` | 685 | 2 |
| `slalom` | 696 | 2 |
| `slalombig` | 696 | 2 |
| `sweep` | 652 | 2 |
| `snake` | 652 | 2 |
| `supertramp` | 552 | 1 |
| `slalomdouble` | 683 | 2 |
| `p` | 679 | 2 |
| `start` | 610 | 2 |
| `turnover` | 671 | 2 |
| `turnoverdouble` | 680 | 2 |
| `turnunder` | 687 | 2 |
| `wibble` | 608 | 2 |
| `invert` | 600 | 2 |
| `halfpipe` | 707 | 2 |
| `twister` | 677 | 2 |
| `twister2` | 677 | 2 |
| `loopbow` | 796 | 2 |
| `toad` | 663 | 2 |
| `hill_valley` | 668 | 2 |
| `sbend` | 579 | 2 |
| `cage2` | 648 | 2 |

This extends the earlier six-function comparison. It supports investigating a
shared mesh/face operation across the path family, but neither identifies an
original helper interface nor establishes a different compiler profile.

## Compiler reductions

The reproducible tool compiles **83 cases** with the unchanged canonical VC6
profile: 39 complete functions (baseline plus 38 controls), their 39 reduced
face-loop counterparts, and five standalone helpers with independent inputs.
Reduced and generic cases intentionally do not implement complete S-bend behavior.

The controls test:

- Duplication of the first one through eight UV stores inside both texture
  branches, with the remaining stores common. Counts 1, 2, 4 and 8 also replay
  earlier controls; this is not a claim that every case is a new hypothesis.
- A second parity branch publishing the last one through eight UV stores after
  the texture-call join. Each execution still performs the eight stores once.
- Staggered scopes: one texture arm publishes a prefix immediately, while a
  second complementary condition publishes that prefix for the other arm.
- Inline helpers with independent odd/even texture arguments, UV arguments,
  or both; value/reference formals; and a four-corner aggregate. Complete
  callers specialize the corresponding parity inputs to equal values.

**No case reproduces the recognized native continuation.** This was checked
with both the earlier local parity classifier and the branch-destination
recognizer, so register-based repeated-condition tests are not silently missed.

The reduced partial-publication results are discontinuous. Duplicating 2, 5,
or 8 initial stores eliminates the parity branches and gives 172 instructions;
other prefix lengths retain four texture call sites and give 194–220 instructions.
This is a compiler observation, not an identification of the responsible pass.
The full controls likewise either eliminate branches, duplicate calls, or retain
other joins. None preserves the native alternate argument block.

Five specialized texture/UV helper forms collapse to the same full code identity
as one another (577 instructions). The independent texture-only helper still
has one shared call, but both argument paths join before it. Independent UV
inputs keep two calls. Specializing all inputs at the caller removes the parity
branches. These cases do not reproduce the hypothesized late specialization.

## Complete-function validation

The 38 complete controls have 33 distinct conservative object-code identities.
The [mutation specification](scratches/initialize_sbend_path_template_pair/texture-continuation-publication-20260908.json)
tests one representative of each through the ordinary matcher. Source hashes
connect all 33 recorded results to the diagnostic sources; equal diagnostic
identities only group controls, and do not award native matching credit.

Every representative regresses: **30.11–78.94%**, with prefixes 0, 7 or 67,
against the baseline's 91.10% and prefix 443. All compile without errors.
Twelve retain fully clean reference audits. Eighteen add four unaudited
references and three add two, consistent with the duplicated call sites;
all still have 39 resolved, zero mismatched and zero unresolved references.
The extra references are recorded as debt, not masked away.

| Complete control | Match | Instructions | Prefix | Extra unaudited references |
| --- | ---: | ---: | ---: | ---: |
| Duplicate first UV store | 78.94% | 589 | 7 | 4 |
| Duplicate first two UV stores | 74.43% | 571 | 7 | 0 |
| Duplicate first five UV stores | 75.43% | 577 | 67 | 0 |
| Specialized texture/UV helper | 75.43% | 577 | 67 | 0 |
| Four-corner aggregate helper | 30.11% | 610 | 0 | 0 |
| Odd arm first-store publication, complementary second scope | 51.99% | 602 | 0 | 4 |

No runtime test is credited to the reductions, and no complete control is
promoted. The previously validated canonical source remains unchanged.
This bounds the tested publication and specialization models; it does not
establish that source recovery or VC6 continuation recovery is exhausted.

## Reproduce

```sh
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run tools/match/probe_texture_continuations.py
UV_CACHE_DIR=/private/tmp/snail-decomp-uv uv run snail match mutate initialize_sbend_path_template_pair --spec tools/match/scratches/initialize_sbend_path_template_pair/texture-continuation-publication-20260908.json --max-variants 33 --top 33
```

The [tracked receipt](texture-continuation-ownership-20260908/receipt.json) binds
the canonical source, compiler and headers, launcher, runner, both diagnostic
tools, native image, symbol manifest, and every generated source/code identity.
It retains all positive native continuation windows and all local diagnostic
patterns. Full sources, objects, mixed listings, assembly and compiler logs stay
under ignored `artifacts/match/texture-continuation-ownership-20260908`.

Validation: all 83 diagnostics reproduce their initial compiled identities;
33 source-hash-linked matcher records cover every distinct complete control;
Ruff, native status checks, and the strict experiment/spec audit pass.
