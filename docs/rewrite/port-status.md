# Port Status

This page is the short ledger for what the Zig runtime currently treats as verified, partial, fallback, scaffold, or debug-only.

Code-level convention:

- `PORT(verified)`: backed by static RE or runtime captures strongly enough to treat as ported behavior
- `PORT(partial)`: on the right path, but still missing some semantics or coverage
- `PORT(fallback)`: deliberate approximation or candidate layer, not the original runtime behavior yet
- `PORT(scaffold)`: temporary shell or structural placeholder to support forward-pass work
- `PORT(debug)`: intentionally non-shipping tooling or inspection code

Current high-signal entries:

- boot and main-menu shell: `scaffold`
  - evidence: original splash art and recovered main-menu labels are now wired, but the overall front-end flow and most handlers are still not at original parity
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: title flow, menu assets, menu actions, and front-end copy are ported
- top-level menu labels plus recovered `New Game` submenu: `partial`
  - evidence: Binary Ninja decompile of `sub_419b50` and `sub_417bc0`
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: high-score routing, option handlers, and later front-end progression flow are ported
- background script parsing plus split `_A` / `_B` menu or splash layouts: `partial`
  - evidence: shipped `BACKGROUNDS/*.TXT` scripts and matching TGA assets
  - implementation: [`background.zig`](../../zig/src/background.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: `Landscape` and any remaining background motion or distortion semantics are ported
- intro and credits text-screen flow: `partial`
  - evidence: shipped `INTRO/INTRO.TXT`, `INTRO/CREDITS.TXT`, and Binary Ninja decompile of `sub_4191e0` / `sub_4199e0`
  - implementation: [`intro.zig`](../../zig/src/intro.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: intro-script image directives, text transforms, and any remaining transition semantics are ported
- active segment `Sample=` / `Message=` routing in the default level path: `partial`
  - evidence: authored level metadata and current tutorial-level behavior
  - implementation: [`main.zig`](../../zig/src/main.zig)
  - replace when: full front-end voice mixing, timing, and segment-transition behavior are ported
- runtime floor-height sampling and tile `0x16` floor slot: `verified`
  - evidence: [`docs/re/track-runtime.md`](../re/track-runtime.md)
  - implementation: [`track.zig`](../../zig/src/track.zig)
- common gameplay build preset `0x00f5cfff`: `partial`
  - evidence: March 8 Frida captures plus track-runtime notes
  - implementation: [`track.zig`](../../zig/src/track.zig)
  - replace when: per-mode or per-level build-flag normalization is fully ported
- ambient garbage and salt candidate overlay: `fallback`
  - evidence: trace-confirmed fallback tile families on `0x01`, `0x0f`, and `0x15`
  - implementation: [`track.zig`](../../zig/src/track.zig), [`main.zig`](../../zig/src/main.zig)
  - replace when: `populate_track_runtime_entities` spawn timing and windowing are ported
- debug asset browser and smoke path: `debug`
  - implementation: [`main.zig`](../../zig/src/main.zig)
