# initialize_worm_path_template_pair match result

Measured with:

```sh
tools/match/match.sh \
  tools/match/scratches/initialize_worm_path_template_pair \
  --regions --max-regions 20 --region-context 6
```

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.27% | **72.28%** |
| Target instructions | 736 | 736 |
| Candidate instructions | 2 | **725** |
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

## Next region to attack

Start with the face/UV tail at `target[556:736]` versus
`candidate[549:725]` (45.51%). The next useful evidence would be a plausible
source construct that explains the target's duplicated texture-selection
control flow and longer-lived side/column float temporaries without spelling a
redundant branch by hand. After that, revisit the vertex arithmetic at
`target[461:525]` to recover the extra natural vector-copy lifetimes responsible
for the `0x80` native frame.
