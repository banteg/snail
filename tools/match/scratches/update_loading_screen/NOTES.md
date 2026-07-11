# update_loading_screen @ 0x418e80

Draws the loading-screen background and the clipped `LoadingBarOn` fill quad
when the integer loader percentage advances by at least one point.

Shared owner layout, now declared in `tools/match/include/loading_bar.h`:

```cpp
struct LoadingBar {
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

Both resources use the renderer's shared 0xc-byte `ObjectRenderBuffers`
wrapper shape; the loading path differs only in its 20-byte vertex payload.

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

2026-06-21 x-end scheduling pass: moving the `x_end` calculation below the
first vertex's constant stores lets VC6 start the x87 multiply after
`vertices[0].x`, matching native's progress-fill vertex setup. Focused Wibo
improves from `90.20%` to `91.67%`; instruction count remains `204/204`, and
masked operands improve from 24 to 26 clean references. An assignment-expression
variant (`vertices[1].x = x_end = ...`) tied the same score, so the clearer
delayed declaration is retained. The remaining visible mismatch is the early
register allocation (`this` in `edi`, clamped percent in `ebx` versus native's
opposite pairing), plus the matching final `previous_percent` store.

2026-06-21 clamped-percent owner pass: reusing `percent` for the bounded value
and then naming `clamped_percent` from that value recovers native's register
ownership (`this` in `ebx`, displayed percent in `edi`) and completes the
helper at `100.00%`, `204/204` instructions, with 26 clean masked operands.
Explicit receiver locals, `register` hints, and declaration-only shuffles were
codegen-neutral at 91.67%; the key source-shape change is shortening the
pre-render lifetime of the clamped value.

2026-07-11 renderer type closure: loading draw calls now share the complete
IDirect3DDevice8 view, and both global vertex resources use the same 0xc-byte
`ObjectRenderBuffers` owner created by the initializer. Focused matching stays
 exact at 204/204 with all 26 operands clean; the repository no longer needs
separate loading-only wrapper or device types.

2026-07-11 cRLoadingBar ownership: Android and iOS preserve this exact
lifecycle role as `cRLoadingBar::AI()` and export the global as `gLoadingBar`.
The Windows owner is now `LoadingBar g_loading_bar`; the 0x0c layout and exact
204/204 updater remain unchanged.
