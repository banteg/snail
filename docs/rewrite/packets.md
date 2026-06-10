# Rewrite Packets

This page describes the current packet workflow. The machine-readable source of
truth is [`../../analysis/packets/rewrite-packets.json`](../../analysis/packets/rewrite-packets.json).

Packets are TU-like subsystem dossiers. They are not claims about original MSVC
translation units. They are stable work packets that group:

- native functions and decompile selectors
- Zig implementation paths
- evidence notes and runtime captures
- current parity status
- next grounded actions

Use the packet manifest before reading older narrative status pages. Long-form
docs remain useful as evidence history, but they are not the current status
ledger unless the packet points to them.

## Commands

Summarize packet status:

```bash
uv run snail packets
```

Validate path references strictly:

```bash
uv run snail packets --strict
```

Write a normalized copy:

```bash
uv run snail packets --write /tmp/rewrite-packets.json
```

## Status Discipline

- `verified` means the current port behavior is strongly backed by static RE,
  runtime captures, or shipped assets.
- `partial` means the implementation is useful and on the right architecture,
  but known parity gaps remain.
- Old prose that says "now", "current", or "remaining" is stale-prone. If it is
  not reflected in the packet manifest, treat it as historical context.
- Visual similarity is not enough to promote a packet. The owning native
  controller or runtime lane must be identified too.
