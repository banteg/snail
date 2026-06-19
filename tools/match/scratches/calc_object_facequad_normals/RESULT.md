# `calc_object_facequad_normals` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **17.13%** |
| Target instructions | 437 | 437 |
| Candidate instructions | 0 | 392 |
| Common prefix | 0 / 437 | **0 / 437** |
| Masked operands | none | **11 clean, 0 unresolved, 1 mismatched** |

This first pass turns the no-scratch target into a relationship-first normal
rebuild scratch. It pins the `Normal Tally` lifetime, weighted vertex-normal
accumulation, invalid-index check, final normalize/invert pass, and free.

## Remaining Work

Next useful work is compiler shape: preserve native nonvolatile ownership and
expand the accumulation sites closer to the raw-offset form emitted by the
target. The sibling `calc_object_facequad_normals_simple` scratch remains the
closest local reference for the face-normal construction prefix.
