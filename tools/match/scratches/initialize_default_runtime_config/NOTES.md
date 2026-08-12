# `initialize_default_runtime_config` recovery notes

Target: `initialize_default_runtime_config @ 0x406c20` (`cdecl` startup
initializer).

The body has no independent code xrefs. The CRT initializer table at `0x4a1008`
points to a thunk at `0x406c10`, which tail-jumps over 11 bytes of alignment
padding to this body:

```asm
00406c10  jmp 0x406c20
00406c15  nop ... 00406c1f
```

The retained C source models the real initializer body: it seeds the saved
config blob, render flags, completion-score defaults, high-score state,
loading-screen budget values, and tutorial latch. Splitting the thunk and body
at the two aligned boundaries makes the initializer exact at 36/36
instructions with all 32 masked operands resolved; the one-instruction thunk is
tracked independently. The saved `SnailMail.cfg` blob slots have curated
references when their consumers are known, while fields with no recovered
consumer remain explicit reserved config offsets. The registration-key test at
`0x42f5b0` is recovered through its mobile symbol; this build ignores its
argument and returns true.

2026-07-11 ownership recovery: the persisted bytes are now represented by one
`RuntimeConfig` object whose asserted size is the `0xc4` passed to every load
and save call. Address spacing fixes the 64-byte name field at `+0x60`, followed
by the route limit, landscape selector, high-score bank, and loading budget at
`+0xa0` through `+0xac`. The render flags are a dword at `+0x1c`: low-byte
feature tests had produced misleading byte declarations, but the default
`0x5fe` store and the window code's `0x400` test require the full word. Moving
the initializer, blob save sites, and all three conflicted field families onto
the aggregate preserved every focused instruction stream and left this scratch
at the then-current 85.71% combined thunk/body result. The later boundary split
above proves the body itself exact without changing those field owners.

2026-07-11 consumer closure: all remaining volume, fullscreen, display-mode,
steering, completion-slider, route-limit, high-score-bank, loading-budget, and
tutorial users now address fields through `g_runtime_config`. The focused
metrics of all 25 affected scratches are unchanged, including every exact
consumer. Naming the landscape selector in the still-sparse world initializer
also converts one raw-symbol mismatch into a resolved operand: 74 clean and 17
expected mismatches, versus 73/18 before the ownership pass.

## 2026-07-14 render-feature flag ownership

Five bits in the persisted `RuntimeConfig::render_flags` word now have named,
independent consumers rather than scratch-local magic masks:

- `0x004` owns the complete `cRStarManager` open/update lifecycle;
- `0x010` gates fireworks, pickup bursts, ring showers, and Golb impacts;
- `0x020` owns runtime row attachments and generated track-fringe meshes;
- `0x100` enables the offset black front-end font-shadow pass; and
- `0x400` selects 32-bit rather than 16-bit Direct3D display setup.

The remaining bits keep their numeric spelling because current Windows
consumers do not justify stronger names. The ten affected callers retain their
pre-change focused results. In particular, the five exact star/particle
consumers remain exact, while `firework_shoot` (94.17%),
`spawn_golb_impact_sprite` (63.64%), `build_track_fringe_objects` (60.39%),
`populate_runtime_track_cells_from_segments` (29.67%),
`layout_frontend_widget` (84.18%), and
`initialize_game_window_and_input` (92.48%) preserve their honest residuals.
The exact 36/36 default initializer is unchanged.

## 2026-07-14 analysis ownership synchronization

The exact 0xc4-byte `RuntimeConfig` now has a dedicated shared analysis header,
narrow Binary Ninja/IDA replay lanes, and the primary `g_runtime_config` symbol
at `0x4df918`. Binary Ninja now types the full global data variable and its
`render_flags +0x1c` field with the proven enum. The matcher and all individual
interior symbol aliases remain byte-identical; reserved fields retain their
conservative offset-based names.

The replay also records the real function boundary: the CRT initializer-table
entry at `0x406c10` is a one-instruction thunk, while the 36-instruction default
initializer begins at `0x406c20`. Focused Binary Ninja exports now retire an
obsolete same-address artifact after a tracked function rename, matching the
existing IDA behavior without pruning unrelated exports.

## 2026-08-12 cross-port source provenance

The symbol-preserving iPhone v1.5 binary exposes `gConfig` in `Mac.o`. Its local
`__GLOBAL__I_MACAppPath` wrapper at `0x2d80` enters the static initializer at
`0x2c60`, which writes the same config offsets and defaults as this Windows
body through `+0xc0`. The Android ELF independently names its corresponding
initializer `_GLOBAL__I_Ad.cpp`; it preserves the same layout and values while
extending the mobile config beyond `+0xc0`.

The three platform defaults explain the real differences: mobile clears the
fullscreen and display-mode fields and uses render flags `0x1fe`, while
Windows enables fullscreen, selects display mode 1, and adds desktop render
bit `0x400` for `0x5fe`. The crosswalk therefore records the iOS STABS source
provenance `Mac.o` for the Windows initializer, not a claim that the Windows
platform unit shared either the `Mac` or `Ad` filename. The exact Windows
36/36 body is unchanged.

## 2026-08-12 registration config fields

The exact Android `gRegisterTestRegisterKey(char*)` identity resolves the
formerly generic config tail at `+0x20` as the 17-byte `registration_key` and
the adjacent byte at `+0x31` as `registration_key_valid`. The default
initializer clears the first key character and seeds validity to true before
the config overlay; startup then tests the loaded key and rewrites the flag.
Only names and the character element type change, so the exact 36/36 initializer
stream is preserved.
