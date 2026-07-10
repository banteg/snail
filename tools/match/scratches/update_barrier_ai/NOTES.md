# update_barrier_ai

Exact 5/5-instruction helper for the embedded tutorial `cRBarrier` actor at
`SubgameRuntime +0xff7bc4`.

The actor is a 0x3c-byte `BodBase` extension. Its only added field is a
borrowed `Player*` at `+0x38`; each update copies the player's live z position
from `Player +0x70` into the barrier BOD, fixes y to `0.4`, and returns the
borrowed pointer. `destroy_subgame` only unlinks this embedded actor from the
global BOD list; neither the list nor the player owns its storage.
