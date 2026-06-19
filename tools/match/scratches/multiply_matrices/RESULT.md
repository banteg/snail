# `multiply_matrices` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 114 |
| Candidate instructions | 114 |
| Common prefix | 114 / 114 |
| Masked operands | none |

The retained source matches the native row-vector affine multiply exactly. It
keeps the compiler's operand order for each x87 multiply-add chain and returns
`rhs` to preserve the leftover `eax` register state used by the exact in-place
wrapper scratches.
