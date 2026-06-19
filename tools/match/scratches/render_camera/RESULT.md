# `render_camera` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.00% | **70.17%** |
| Target instructions | 180 | 180 |
| Candidate instructions | 0 | 182 |
| Common prefix | 0 / 180 | **0 / 180** |
| Masked operands | none | **34 clean, 0 unresolved, 1 mismatched** |

The remaining masked mismatch is in the viewport conversion prologue:

```text
target[8]    fmul dword [640.0f]
candidate[13] fmul dword [480.0f]
```

That alignment is tied to the retained `0xc4` frame versus the native `0xc8`
frame. The semantic source recovers the viewport, projection, view transform,
render-state, fog, and renderer-global behavior without dummy symbols, inline
assembly, volatile padding, or fake aliases.

## Added reference

`0x503218` is now named `g_render_camera_view_matrix`. Native `render_camera`
stores the seventh argument there immediately before clearing
`g_current_texture_ref` and returning the same pointer in `eax`.
