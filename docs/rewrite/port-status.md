# Port Status

The old prose ledger on this page was retired because it mixed current facts,
stale "remaining gap" notes, and dated investigation summaries in one long
surface.

Use these surfaces instead:

- detailed reference notes: [subsystem-status.md](subsystem-status.md)
- backlog and priority order: [remaining-work-checklist.md](remaining-work-checklist.md)
- dated parity audits and runtime findings: `../../analysis/runtime/*.md`

Interpretation rule:

- `analysis/decompile`, `analysis/symbols`, `analysis/headers`, and dated runtime notes are primary evidence
- old narrative docs are context unless a newer audit or checked-in implementation confirms the same claim

Status values are intentionally conservative. A subsystem should stay `partial`
while any known native owner, runtime field, payload writer, or post-run handoff
is unresolved, even if the current Zig path looks close on screen.
