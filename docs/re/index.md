# RE

This section is for deeper reverse-engineering work: hardcoded runtime behavior, Binary Ninja workflows, wrapper internals, and Windows tracing runbooks.

## Pages

- [Path system overview](path-system.md): current understanding of `Path=` handling and the segment-to-track runtime pipeline
- [Path templates](path-templates.md): hardcoded path names, slot layout, and constructor families
- [Track runtime](track-runtime.md): segment metadata, runtime flags, glyph dispatch, and render passes
- [Attachment follow state](attachment-follow.md): how authored `Path=` rows install live follow-state transitions
- [Background light streaks](background-light-streaks.md): the separate star-field sprite pass layered on top of the Distort backdrop warp
- [Runtime structures](runtime-structures.md): current high-confidence `Player`, `Game`, and attachment-template layouts
- [Audio callsite map](audio-callsite-map.md): whole-game `play_sound_effect` / `play_voice_manager` inventory grouped by owning gameplay system
- [Symbol workflow](symbols.md): how the curated Binary Ninja function manifest is maintained
- [Reflexive wrapper](reflexive-wrapper.md): bootstrap and wrapper-obfuscation notes
- [Frida runtime trace](frida-runtime-trace.md): the Windows tracing harness and capture strategy
- [Windows Frida handoff](windows-frida-handoff.md): operator-oriented runbook for collecting traces
- [Windows debugging wants](windows-debugging-wants.md): prioritized runtime-debug targets for the remaining camera and handoff gaps
- [Windows CDB session (2026-03-15)](windows-cdb-session-2026-03-15.md): live `cdb` setup, breakpoint targets, and findings from the first Windows debugger session

Published docs stay here. Repo-only analysis artifacts, including the tracked symbol manifest JSON, live under `analysis/`.
