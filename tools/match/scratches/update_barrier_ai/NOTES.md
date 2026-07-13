# update_barrier_ai

Exact 5/5-instruction helper for the embedded tutorial `cRBarrier` actor at
`SubgameRuntime +0xff7bc4`.

The actor is a 0x3c-byte `BodBase` extension. Its only added field is a
borrowed `Player*` at `+0x38`; each update copies the player's live z position
from `Player +0x70` into the barrier BOD, fixes y to `0.4`, and returns the
borrowed pointer. `destroy_subgame` only unlinks this embedded actor from the
global BOD list; neither the list nor the player owns its storage.

2026-07-13 analysis propagation: the path-template runtime view now embeds
this exact `BarrierActor` directly after the 63 path pairs at `+0xff7bc4`.
Its 0x3c-byte extent ends exactly where the landscape manager begins at
`+0xff7c00`. Binary Ninja declaration preview verifies the boundary and
reverts; focused matching remains exact at 5/5 instructions.
