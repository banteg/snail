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
  - evidence: current forward-pass goal, not original UI parity yet
  - implementation: [`main.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/main.zig)
  - replace when: title flow, menu assets, and real actions are ported
- runtime floor-height sampling and tile `0x16` floor slot: `verified`
  - evidence: [`docs/re/track-runtime.md`](/Users/banteg/dev/banteg/snail-mail/docs/re/track-runtime.md)
  - implementation: [`track.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/track.zig)
- common gameplay build preset `0x00f5cfff`: `partial`
  - evidence: March 8 Frida captures plus track-runtime notes
  - implementation: [`track.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/track.zig)
  - replace when: per-mode or per-level build-flag normalization is fully ported
- ambient garbage and salt candidate overlay: `fallback`
  - evidence: trace-confirmed fallback tile families on `0x01`, `0x0f`, and `0x15`
  - implementation: [`track.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/track.zig), [`main.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/main.zig)
  - replace when: `populate_track_runtime_entities` spawn timing and windowing are ported
- debug asset browser and smoke path: `debug`
  - implementation: [`main.zig`](/Users/banteg/dev/banteg/snail-mail/zig/src/main.zig)
