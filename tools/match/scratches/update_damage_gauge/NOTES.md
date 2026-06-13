# Dossier — gates decoded via the campaign layout work (2026-06-12)

update_damage_gauge @ 0x440fd0. The audit's "unresolved writer" globals
are now interpretable with the recovered region layouts:

- suspend byte Game+0x74621: the global pause gate (checklist item)
- warning-start blockers: **Game+0x430199 is FollowState.live_flag**
  (+0x99 of the shared follow block — the swept entry clears it; the
  warning cannot start while an attachment entry is live) and
  Game+0x4301bc (follow-region byte +0xbc, writer still unknown but now
  localized to the follow block; also forces the drain transition)
- drain transition gate: **Game+0x42fde8 == 0.49f is
  player.position.y == rest height** — the state-2 drain logic keys on
  the player being grounded
- state-2 drain refreshes change_snail_skin(1, 0.2) per tick (matches
  the Zig controller's state-2 skin refresh)
- state-2 exit gates 0x4301c0/0x42fe08/0x434064: 0x42fe08 = player+0x8c
  (player-region field), 0x4301c0 = follow-region +0xc0 — next session
  can name them from their consumers the same way

Zig verify: gameplay/damage.zig models these as opaque UpdateContext
bools (warning_start_blocked, accelerated_drain_gate, suspended) — the
correct seam shape; they can now be WIRED to their real sources
(follow.live_flag, the grounded check) when cluster-5 routes.

## Scratch status

Promoted to a matcher scratch on 2026-06-13. Current result: 65.92%,
266/268 instructions. The first scratch is structure-first and covers:

- suspend gate `Game+0x74621`
- display-fill smoothing and hit-flash progress wrap
- state 0 warning start gates at `Game+0x430199` and `Game+0x4301bc`
- state 1 transition to drain on `Game+0x42fde8 == 0.49f`
- state 2 skin refresh, forced/unforced drain deltas, warning stop/sample
  stop exit conditions
- HUD mask/fill/flash quads with the native 560/70/64/396 geometry and one
  reused stack color

Remaining diff is mostly block placement and x87/local scheduling: native lays
out the state-2 body before the state-1/state-0 blocks and uses stack slots
`esp+4`/`esp+8`/`esp+0xc` for alpha, mask height, and color. Do not use fake
labels or volatile locals just to coerce that layout.
