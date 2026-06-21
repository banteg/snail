# initialize_loading_screen @ 0x418b50

Initializes the loading-screen renderer state:

- sets `g_last_loading_budget` to `1276`;
- loads `Sprites/Loading.tga` into `data_503288`, the background texture;
- loads `Sprites/LoadingBarOn.tga` into `data_503280`, the progress-fill
  texture;
- creates the background and progress-bar vertex-buffer resources with FVF
  `0x102`;
- seeds the background quad as 20-byte `{x, y, z, u, v}` vertices spanning
  `0,0` to `640,480`;
- enters overlay render state and resets the three-field `LoadingScreen`.

The native code locks `data_503284` for the background quad writes but calls the
`Unlock` vtable slot through `data_5032a4` after those writes. The scratch keeps
that observed call shape instead of normalizing it to the likely intended
resource.

`sub_4533c4`, `sub_453404`, and `sub_453467` are D3DX texture creation wrappers:
the in-memory archive path, file-path `...ExA` path, and simple debug fallback,
respectively.

2026-06-21 owner-register retry: naming `LoadingScreen* screen = this` for the
tail state stores, with and without `register`, is codegen-neutral at 83.00%.
VC6 still keeps `this` in `edi` and archive data in `ebx`, opposite native's
`ebx`/`edi` split. The mismatch is not fixed by a simple owner local.

2026-06-21 archive-register retry: hoisting `archive_base` out of the two
archive branches, marking the branch-local archive pointer `register`, and
rewriting the tail state stores through a raw `char* screen` are all
codegen-neutral at 83.00%. These forms keep the same inverted register split:
candidate `edi=this` / `ebx=archive_base`, native `ebx=this` /
`edi=archive_base`.
