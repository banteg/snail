# `place_challenge_parcels_on_track` match result

## Score

| Metric | Value |
|---|---:|
| Match | **44.70%** |
| Target instructions | 171 |
| Candidate instructions | 178 |
| Common prefix | 0 / 171 |
| Masked operands | 18 clean, 1 unresolved, 0 mismatched |

First mismatch:

```text
target[0]    sub esp, 0x48
candidate[0] sub esp, 0x4c
```

The unresolved masked operand is the reset-loop end sentinel:

```text
target    0x643390 = zero-bucket count-lane end
candidate g_zero_parcel_buckets + 0x106200
```

No dummy symbol was added for that boundary. The retained source is semantic and leaves the remaining stack/register-shape debt visible.
