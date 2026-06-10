# Port Status

The old prose ledger on this page was retired because it mixed current facts,
stale "remaining gap" notes, and dated investigation summaries in one long
surface.

The current status source is now the packet manifest:

- packet data: [`../../analysis/packets/rewrite-packets.json`](../../analysis/packets/rewrite-packets.json)
- workflow notes: [packets.md](packets.md)
- detailed reference notes: [subsystem-status.md](subsystem-status.md)
- backlog: [remaining-work-checklist.md](remaining-work-checklist.md)

Use:

```bash
uv run snail packets --strict
```

Interpretation rule:

- packets are current status
- `analysis/decompile`, `analysis/symbols`, `analysis/headers`, and cited runtime notes are primary evidence
- old narrative docs are context unless the packet manifest points to them

Status values are intentionally conservative. A subsystem should stay `partial`
while any known native owner, runtime field, payload writer, or post-run handoff
is unresolved, even if the current Zig path looks close on screen.
