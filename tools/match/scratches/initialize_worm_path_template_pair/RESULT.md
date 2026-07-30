# initialize_worm_path_template_pair match result

Measured with:

```sh
tools/match/match.sh \
  tools/match/scratches/initialize_worm_path_template_pair \
  --regions --max-regions 20 --region-context 6
```

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.27% | **72.81%** |
| Target instructions | 736 | 736 |
| Candidate instructions | 2 | **728** |
| Common prefix | 0 / 736 | **0 / 736** |
| Masked operands | none | **37 ok, 0 unresolved, 0 mismatch** |

Net improvement: **+72.01 percentage points**.

The first mismatch remains the local-frame reservation:

```text
target[0]    sub esp, 0x80
candidate[0] sub esp, 0x68
```

This is left visible rather than padded. Despite the zero whole-function
prefix, localized regions are strong: the constructor setup is 85.71%, several
sample/delta regions are 86-93%, and every normalized-equal masked operand
resolves to the correct native reference.

## Accepted source-shape changes

- Added native-offset overlays for `Path`, the `0xa8` sample,
  and the `0x30` facequad.
- Reconstructed all constructor fields, both sample banks, basis generation,
  delta normalization, terminal delta state, mesh allocation, tube vertices,
  colours, double-sided facequads, UVs, texture references, and finalization.
- Used the native-shaped zero-based middle counter and first-iteration branch.
- Kept direct array indexing and repeated source expressions where they recover
  target register allocation.
- Used scalar-left vector arithmetic with real intermediate vectors in the
  trigonometric vertex loop.
- Kept the valid sample row as fallthrough and terminal extrapolation in the
  alternate branch.
- Kept the two-sided face loop and its `side == 0` winding/UV branch.
- Preserved the recovered void finalizer semantics; no synthetic return value is
  introduced solely because a decompiler prototype labels EAX.

## Rejected or neutral trials

- Passing the scalar-left vector operand by value recovered the target `0x80`
  frame but scored only 66.85%, emitted 739 instructions, and caused a masked
  call-alignment mismatch.
- By-value `operator+`, local-return-vector variants, and extra copy temporaries
  disrupted the better register/x87 schedule and scored lower.
- Duplicating the texture lookup behind an explicit parity branch scored
  62.27%. The target branch passes the same single texture argument on both
  sides, so forcing it would be byte-shaped rather than semantically supported.
- Sample/face pointer aliases, alternate `for` loop spellings, direct narrow
  casts, and reordered face pointer arithmetic were neutral or regressive.
- No artificial frame padding, volatile barriers, dummy externs, inline
  assembly, or normalizer gaming was used.

## Bounded mesh-tail experiments

The Windows sibling constructors establish that the checkerboard texture
branch is authored shared-generator behavior even when both arms receive the
same texture argument. Restoring that branch in isolation is not yet
retainable: direct duplicated-call forms fall to 58.38-58.42%, while a
selected-path form reaches only 68.35%. The latter emits 730 instructions but
still inherits the wrong frame and broad stack-colour changes.

Seven natural tube-vector staging variants produce no improvement. Explicit
right-radius/right-component temporaries are byte-identical to the retained
source; component, copied-position, in-place, and shared-angle forms regress.
Five sibling-backed 16-bit face-index spellings are also byte-identical.

The experiment ledger therefore closes 18 unique variants at zero better, six
neutral, and twelve worse, with no repeats or tradeoffs. Three consecutive
non-improving sweeps mark the mesh-tail region stalled.

## Remaining dependency

The face/UV tail remains `target[556:736]` versus `candidate[551:728]`, but the
checkerboard branch cannot be recovered independently of the earlier native
`0x80` vector/x87 frame. Resume only with new evidence for a natural
mesh-vector lifetime that fixes that frame; then retest the now-proven sibling
parity idiom as a combination. Artificial stack padding, volatile copies, or
branch-only byte shaping remain out of scope.

That combination has now been tested exhaustively. An instruction-backed
11-variant sweep combines the correct-frame by-value scalar ABI, full-expression
and component-result lifetimes, and checkerboard selection. Every combination
regresses; the closest loses one weighted byte, while the correct-frame form
loses 153. Resume Worm only with new operator/source provenance.
