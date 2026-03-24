# Invalidation Ledger

Use this ledger only when new RE or runtime evidence overturns a previously trusted model.

Why this exists:
- prevent old workaround narratives from becoming sticky repo memory
- surface which assumptions are no longer safe to port against
- point the next dossier at the exact model that needs replacement

Add entries only when one of these happens:
- a previous owner or writer claim is disproved
- a field meaning changes materially
- a controller boundary moves
- a parity test is demoted from `parity` to `scaffold`

Keep entries short:
- date
- subsystem
- invalidated claim
- replacement evidence
- immediate port consequence

Template:

## YYYY-MM-DD - Subsystem

- invalidated claim:
- replacement evidence:
- port consequence:

## 2026-03-25 - Outer bridge

- invalidated claim: ordinary respawn rebuild should stay modeled as a saved-owner bridge opcode lane
- replacement evidence: March 24 Windows capture shows ordinary respawn rebuilding through direct owner `0x1c`, not `0x1a/0x1b`
- port consequence: respawn bridge state in Zig must store the direct selector as authoritative and stop using the request dispatcher as the conceptual center

## 2026-03-25 - Runtime capture policy

- invalidated claim: broader Windows capture is still the default next step for bridge and attachment work
- replacement evidence: the stable March 24 packets closed the practical bridge handoff lanes, while broader probe sets caused host hangs
- port consequence: outer bridge is unblocked for replacement from the locked capture baseline; attachment exit stays static-RE only until a narrower stable proof exists
