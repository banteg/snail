# Rewrite Docs Index

Status ledgers and plans for the Zig rewrite. Read the active one for the
current work surface; treat the rest as reference.

Active:

- [remaining-work-checklist.md](remaining-work-checklist.md) — action-oriented backlog and blind spots
- [port-status.md](port-status.md) — short status ledger by feature or subsystem
- [subsystem-status.md](subsystem-status.md) — detailed subsystem notes
- [code-structure.md](code-structure.md) — Zig subsystem split plan and completed extractions
- [invalidation-ledger.md](invalidation-ledger.md) — overturned models, dated so old workarounds do not stay sticky

Primary-evidence sources (prefer these over any narrative doc):

- `analysis/symbols/gameplay-functions.json` — tracked Binary Ninja function manifest
- `analysis/headers/*.h` — checked-in Binary Ninja struct layouts
- `analysis/decompile/binja/functions/*.c` — re-exported decompiles
- `analysis/decompile/health_checks.json` — canary checks that gate decompile typing regressions
- `analysis/runtime/*.md` — dated runtime-RE packets cited by `invalidation-ledger.md`

Rules for using this directory:

- do not reread the whole directory by default
- do not treat old narrative docs as stronger than primary evidence
- preserve evidence-backed notes, but demote stale interpretation out of the default context
