# RE

This section is for deeper reverse-engineering work: hardcoded runtime behavior, Binary Ninja workflows, wrapper internals, and Windows tracing runbooks.

## Pages

- [Path system overview](path-system.md): current understanding of `Path=` handling and the segment-to-track runtime pipeline
- [Path templates](path-templates.md): hardcoded path names, slot layout, and constructor families
- [Track runtime](track-runtime.md): segment metadata, runtime flags, glyph dispatch, and render passes
- [Attachment follow state](attachment-follow.md): how authored `Path=` rows install live follow-state transitions
- [Runtime structures](runtime-structures.md): current high-confidence `Player`, `cRSubGame`, and attachment-template layouts
- [Object runtime](object-runtime.md): global object-list ownership, authored mesh loading, animation frames, render-buffer construction, and frame-time borrowing
- [Symbol workflow](symbols.md): how the curated Binary Ninja function manifest is maintained
- [Reflexive wrapper](reflexive-wrapper.md): bootstrap and wrapper-obfuscation notes
- [Frida runtime trace](frida-runtime-trace.md): the Windows tracing harness and capture strategy

Published docs stay here. Repo-only analysis artifacts, including the tracked symbol manifest JSON, live under `analysis/`.
