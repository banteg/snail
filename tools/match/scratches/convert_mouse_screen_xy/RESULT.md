# convert_mouse_screen_xy match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 74.46% | **100.00%** |
| Target instructions | 115 | 115 |
| Candidate instructions | 116 | 115 |
| Common prefix | 3 / 115 | **115 / 115** |
| Masked operands | 32 clean | **35 clean** |

There are no unresolved or mismatched masked operands. The exact source
recovers the windowed-captured direct cursor read, captured/fullscreen delta
path, uncaptured sensitivity-scaled delta path, failed `GetCursorPos` zeroing,
and active-window recentering through `SetCursorPos`.

## Accepted source-shape and ownership changes

- Recovered the helper as side-effect-only `void`; its sole caller ignores the
  result and native leaves mutually incompatible incidental values in `eax`.
- Expressed each failed cursor read as `*y = *x = 0.0f`, yielding the native
  x-then-y zero stores without artificial lifetimes.
- Promoted the local cursor pair to the shared, size-proved eight-byte Win32
  `Point` owner and shared the helper declaration with `update_mouse`.

## Measured progression

| Trial | Match | Candidate instructions | Outcome |
|---|---:|---:|---|
| Initial semantic scratch | 74.46% | 116 | Superseded |
| Separate y-then-x zero stores | 77.06% | 116 | Superseded |
| Void ABI plus chained zero owner | **100.00%** | **115** | Final retained result |
