# update_star_positions

`update_star_positions @ 0x434800` advances star-entry travel distances, respawns expired
sprites from the camera-facing game slice, mirrors entry velocity into the
sprite, offsets the respawned sprite by ten frames of travel, and writes alpha
from `(travel_distance - 2) * alpha_scale * fade / 87.5`.

Layout evidence shared with `initialize_star_field`:

- `StarManagerEntry` size is `0x2c`, proved by `open_star_field`.
- `active +0x00` is initialized and cleared by lifecycle functions.
- `position +0x04` and `velocity +0x10` are seeded by
  `initialize_star_field`; update copies velocity to the sprite.
- `sprite +0x1c`, `speed +0x20`, `travel_distance +0x24`, and
  `alpha_scale +0x28` are all read by this updater. The last two names follow
  behavior: travel advances by speed and wraps at 35, while alpha is computed
  directly from travel times the per-entry scale.

The apparent camera/origin view at `g_game_base +0x6d4/+0x6e4` is not a pair
of root-owned star fields. Those addresses are
`GameRoot::overlay_0.transform.basis_forward` and
`GameRoot::overlay_0.transform.position`: overlay 0 starts at root `+0x67c`
and its inherited transform starts at `+0x38`. Using the corrected shared
owner preserves the focused Wibo result.

## Source and ABI recovery

- The cross-port owner is `cRStarManager`, and `UpdateStars(float)` is a `void`
  method. Native's final sprite pointer merely remains in `eax` after the alpha
  store; modeling it as a returned pointer added synthetic result bookkeeping.
- Direct `entries[i]` ownership gives VC6 the native `ecx = manager`,
  `edx = entry byte offset`, and `edi = loop count` split without a retained
  entry pointer.
- Respawn position is the same by-value vector expression proven in
  `initialize_star_field`: camera forward times 50 plus camera position.
- Ten frames of travel are applied as
  `sprite.position += entry.velocity * 10`. The in-place `Vector3::operator+=`
  removes the extra result vector and recovers native's exact `0x24` frame.

Current focused result: 98.11%, 106/106 candidate/target instructions, prefix
44/106, and 11 masked operands clean. The only residuals are two independent
instruction-scheduling swaps: storing the final camera-position component
versus advancing the sprite-position pointer, and multiplying alpha by the
constant versus the borrowed fade argument.

Earlier rejected/source-shape probes:

- Direct per-component sprite writes compiled to 26.46% by eliminating native
  stack staging entirely.
- A local `Vector3 staged_position` plus `scaled_y/scaled_z` recovered some
  stack traffic but only reached 31.84%; VC6 still kept the entry pointer live
  and introduced an `ebx` zero register.
- Keeping `direction_scaled`, `staged_position`, and `velocity_scaled` locals
  allocated a `0x28` frame and lost native's `edx` byte-offset loop; the
  recovered operators explain those temporaries directly.
- Returning the incidental final sprite pointer reached 94.88% but emitted
  three extra result-reload instructions, contradicting the cross-port void
  method and the native tail.

## 2026-07-14 root owner and alpha lifetime

The camera transform now comes through the canonical `GameRoot* g_game`
owner rather than a raw base plus local cast. Naming the alpha before applying
the borrowed `fade_alpha` argument also recovers native's left-associated
constant-then-fade multiply order. Focused matching rises from 98.11% to
99.06%, remains 106/106 instructions with all 11 operands clean, and removes
the alpha-tail mismatch entirely. The sole residual is the independent
sprite-position pointer advance moving across the final temporary Z store;
named position and sprite locals compile identically, so no ordering barrier
is retained.
