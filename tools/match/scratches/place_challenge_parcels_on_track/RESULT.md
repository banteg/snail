# `place_challenge_parcels_on_track` match result

## Score

| Metric | Value |
|---|---:|
| Match | **44.70%** |
| Target instructions | 171 |
| Candidate instructions | 178 |
| Common prefix | 0 / 171 |
| Masked operands | 19 clean, 0 unresolved, 0 mismatched |

First mismatch:

```text
target[0]    sub esp, 0x48
candidate[0] sub esp, 0x4c
```

The reset-loop end boundary is now spelled as the curated
`g_zero_parcel_bucket_count_lane_end` sentinel, so the masked audit is clean
without changing the score or hiding the remaining stack/register-shape debt.
