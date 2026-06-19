# `initialize_runtime_pools_and_path_template_bank` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **100.00%** |
| Target instructions | 227 | 227 |
| Candidate instructions | 0 | 227 |
| Common prefix | 0 / 227 | **227 / 227** |
| Masked operands | none | **72 clean, 0 unresolved, 0 mismatched** |

The scratch matches the runtime-pool constructor pass exactly, including the
three buffer color constructors, all array-constructor calls, counted pool
loops, and callback table installs.
