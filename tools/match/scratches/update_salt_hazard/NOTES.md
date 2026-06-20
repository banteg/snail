# update_salt_hazard @ 0x441c10

First correctly named scratch for the salt runtime updater after the 2026-06-16
vtable correction. `initialize_salt_hazard_runtime` installs vtable
`data_497340`, and `data_497340` points at `0x441c10`.

Pinned at `62.96%`, `79/83` target instructions. Field offsets are aligned;
the remaining masked mismatch is the state-2 error-string tail merge (`List
remove` versus `List remove NEXTBOD`) in the candidate control-flow shape.

Recovered behavior:

- skips while `owner_game +0x09` `subgame_pause_gate` is set
- state `2` performs the standard live-list removal against `game +0x5a8`
- state `1` computes a fade fraction from `position.z`, clamps it to
  `[0, 1]`, writes alpha through `Color4f::set_color_alpha(0.9)`, and moves
  to state `2` once behind `owner_game +0x3be0e4`

This replaces the previous salt interpretation of `0x4417d0`; that function is
now correctly owned by the sub-lazer vtable.

2026-06-16 BOD/renderable consolidation: the shared `SaltHazardSlot` header now
uses the promoted `BodNode` prefix and `BodList` anchor, and records the
BodBase/renderable rows through `+0x77`. This updater now calls
`color.set_color_alpha(...)` through the promoted `Color4f color +0x28` field
instead of a raw cast, while spawn/initializer/collision prove the position
row at `+0x68`. Focused Wibo remains `62.96%`, `79/83`, with the same known
state-2 error-string tail merge mismatch.

2026-06-19 local game-base staging: spelling the state-2 free-list anchor
through a local `Game* game = g_game` improves the focused match from `62.96%`
to `75.78%` and clears the previous masked string mismatch (`10 ok / 0
unresolved / 0 mismatch`). The remaining state-2 residual is still real:
native materializes `game+0x5a8` as an anchor pointer in `ecx`, while the
candidate keeps the game base and folds anchor accesses to `+0x5ac/+0x5b0`;
the first error-report call also remains tail-merged in candidate code.

2026-06-20 volatile audit: direct `g_game` is now a normal external here too.
Focused Wibo improves from 75.78% to 81.48%, with 83 target / 79 candidate
instructions and 11 masked operands OK. This keeps the game-base lifetime
consistent with the damage/salt family and avoids stale volatile reloads; the
remaining residual is still state-2 control-flow/tail merging plus anchor
materialization.
