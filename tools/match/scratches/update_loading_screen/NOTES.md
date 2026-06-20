# update_loading_screen @ 0x418e80

Draws the loading-screen background and the clipped `LoadingBarOn` fill quad
when the integer loader percentage advances by at least one point.

Shared owner layout, now declared in `tools/match/include/loading_screen.h`:

```cpp
struct LoadingScreen {
    int active;           // +0x00
    int previous_percent; // +0x04
    int last_loading_budget; // +0x08
};
```

`initialize_loading_screen` provides the global identities:

- `data_503288`: `Sprites/Loading.tga`, full background texture.
- `data_503280`: `Sprites/LoadingBarOn.tga`, progress-fill texture.
- `data_503284`: full-background quad vertex-buffer resource.
- `data_5032a4`: dynamic progress-fill quad vertex-buffer resource.

The progress bar geometry is a 20-byte `{x, y, z, u, v}` vertex, not the
24-byte object/sprite vertex with diffuse color. The fill quad is clipped from
`x=192` to `x=192 + percent * 0.92 * 2.56`, with `percent > 98` forcing the
displayed fill to 100%.

2026-06-20 progress-bar vertex pass: spelling the first `u_end` store as an
assignment expression (`vertices[1].u = u_end = ...`) recovers native's
single live-x87 store into both the stack local and vertex lane, removing the
extra candidate reload. Focused Wibo improves from `88.02%` to `90.20%`, with
instruction-count parity at `204/204` and 24 clean masked operands. A nearby
two-step `x_end` spelling was codegen-neutral at the same score but less clear,
so the direct `x_end = bar_percent * 2.5599999f + 192.0f` expression remains.
