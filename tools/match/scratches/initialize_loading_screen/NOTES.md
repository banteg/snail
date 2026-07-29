# initialize_loading_screen @ 0x418b50

Initializes the loading-screen renderer state:

- sets `RuntimeConfig::last_loading_budget` to `1276`;
- loads `Sprites/Loading.tga` into `g_loading_background_texture` at
  `0x503288`;
- loads `Sprites/LoadingBarOn.tga` into `g_loading_bar_on_texture` at `0x503280`,
  the progress-fill
  texture;
- creates the background and progress-bar vertex-buffer resources with FVF
  `0x102`;
- seeds the background quad as 20-byte `{x, y, z, u, v}` vertices spanning
  `0,0` to `640,480`;
- enters overlay render state and resets the three-field `LoadingBar`.

The native code locks `g_loading_background_vertex_buffer` at `0x503284` for
the background quad writes but calls the `Unlock` vtable slot through
`g_loading_bar_vertex_buffer` at `0x5032a4` after those writes. The scratch
keeps that observed call shape instead of normalizing it to the likely intended
resource.

`sub_4533c4`, `sub_453404`, and `sub_453467` are D3DX texture creation wrappers:
the in-memory archive path, file-path `...ExA` path, and simple debug fallback,
respectively.

2026-06-21 owner-register retry: naming `LoadingBar* screen = this` for the
tail state stores, with and without `register`, is codegen-neutral at 83.00%.
VC6 still keeps `this` in `edi` and archive data in `ebx`, opposite native's
`ebx`/`edi` split. The mismatch is not fixed by a simple owner local.

2026-06-21 archive-register retry: hoisting `archive_base` out of the two
archive branches, marking the branch-local archive pointer `register`, and
rewriting the tail state stores through a raw `char* screen` are all
codegen-neutral at 83.00%. These forms keep the same inverted register split:
candidate `edi=this` / `ebx=archive_base`, native `ebx=this` /
`edi=archive_base`.

2026-07-14 factory-owner closure: both loading-screen vertex resources use the
embedded `Direct3DRenderer::vertex_buffer_factory`. That complete `0x8ca4`
owner contains its count and 3000-entry vertex-wrapper pool; the renderer-state
and device fields remain at `+0xbb88/+0xbb94`. Focused output remains 83.00%,
253/253, with 47 clean operands and the same register-allocation residual.

2026-07-11 cRLoadingBar ownership: Android and iOS name this initializer
`cRLoadingBar::Init()` and preserve the `gLoadingBar` global. Promoting the
Windows 0x0c owner to `LoadingBar g_loading_bar` is codegen-neutral at the same
83.00% near-complete source shape.

2026-07-15 return-ownership closure: startup calls this member at `0x406f19`
and immediately continues through the next initialization call without reading
EAX. `cRLoadingBar::Init()` is therefore void; the old return was only the
residue of `begin_overlay_render_state`. Removing it preserves the honest
83.00%, 253/253 instruction result and all 47 clean operands.

Fresh IDA decompilation also proves the three linked D3DX 8 texture wrappers
use `__stdcall` cleanup: `sub_4533C4` returns with `0x3c`, `sub_453404` with
`0x38`, and `sub_453467` with `0x0c`. Persisting that exact arity prevents a
stale inferred callee type from breaking Hex-Rays call analysis when the caller
prototype is refreshed.

2026-07-24 resource-ownership closure: the native `Sprites/Loading.tga` and
`Sprites/LoadingBarOn.tga` arguments prove that Binary Ninja's inherited names
at `0x503280` and `0x503288` were reversed. IDA independently retained the
correct address-to-name mapping. Both database replays now type the texture
globals as `Direct3DTexture8*` and both vertex resources as
`ObjectRenderBuffers*`; Binary Ninja additionally types the initializer's
dedicated mapped storage as `LoadingVertex*`. This exposes the shared
`vertex_buffer`, `Lock`, `Unlock`, and COM `Release` ownership through Init,
AI, and UnInit. At that point AI's overlapping stack slot remained untyped
because the native function reuses it first as an integer percentage and later
as a mapped pointer. The matcher source and its honest 83.00%
register-scheduling residual are unchanged; `update_loading_screen` and
`destroy_loading_screen` remain exact at 204/204 and 15/15 instructions.

2026-07-25 mapped-quad lifetime closure: the initializer's
`Lock(..., 0x50, ...)` result is now represented in both analysis databases as a borrowed
`LoadingQuadVertexView` containing exactly four 0x14-byte `LoadingVertex`
records. The initializer's former first-vertex pointer now exposes all
`vertices[0..3].{x,y,z,u,v}` fields instead of 15 raw offsets. The updater
reuses its percentage stack slot as an implicit COM out-parameter, but neither
decompiler exposes a valid second local definition at the overwrite. Split
probes either fail readback or contaminate the earlier percentage expression,
so both updater views deliberately keep that physical slot untyped. The replay
does not recreate the rejected IDA split override. This view does not own
either Direct3D resource, and the matcher source remains the more plausible
authored `LoadingVertex*` array form at the honest 83.00% baseline.

## 2026-07-29 bounded archive and device owner audit

The two archive branches were swept against one shared `archive_base` lifetime
in each of three declaration positions. All 12 compilable combinations emit
the exact baseline bytes; the three partial assignment-only combinations are
expected compile failures because they omit the shared declaration. Replacing
each direct device access with the enclosing renderer's `device` field is also
byte-identical.

An explicit fastcall receiver diagnostic moves `this` into the desired native
register but regresses focused matching to 80.24%, 253/253, and increases the
reference debt. The retained 83.00%, 253/253, prefix-5 source therefore keeps
the verified void member ABI and direct device owner. Its inverse
`this`/archive saved-register assignment is backend allocation, not evidence
for a missing dependency or a forced calling convention.
