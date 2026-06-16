# Ring halo render parity - 2026-06-12

Targeted re-check of the runtime ring effect (the ten-sprite halo for
`Ring=*` rows) against `SnailMail_unwrapped.exe.bndb`, prompted by the halo
looking wrong in the port. The native owner chain is
`spawn_track_ring_or_special_effect` @ 0x43df10 →
`initialize_ring_or_special_effect_particles` @ 0x43e470 →
`update_ring_or_special_effect_parent` @ 0x43e830 →
`update_ring_or_special_effect_particle` @ 0x43e780 →
`emit_ring_star_shower` @ 0x43e690.

## Recovered native behavior

- Per-child orbit: each of the ten children stores its own phase lane
  (`child + 0x14`), seeded to exactly `i * tau/10` — no random offset. Every
  child's spin lane (`child + 0x18`) is `subgame_rate * 0.10471976`
  (`tau/60`), sampled from the subgame pointer the slot holds at `+0x1d0`
  (installed by `reset_subgame` @ 0x437b10). The spin is always positive and
  the child update freezes it when the parent kind (`+0x88`) is `3`.
- The parent's random lanes at `+0x1e0`/`+0x1e4` (random start angle, the
  ramp-cycle-derived step with a random sign flip) are only consumed inside
  `update_ring_or_special_effect_parent` behind the byte flag at `+0x1dc`. No instruction
  in the binary writes that flag (checked via MLIL scan plus a raw disp32
  byte-pattern sweep; the slot constructors and `reset_subgame` never touch
  it, and the 19 MB `cRGame` allocation comes from fresh zeroed pages). The
  sine X-drift branch is dead native code: an active ring's X stays wherever
  the spawn randomizer put it.
- Children update in every live state (1 active, 3 collect-follow, 5
  miss-expand all run the ten-child loop), so the halo keeps orbiting while
  it collapses onto the player or expands after a miss.
- The collect lerp multiplies each child's orbit radius lane
  (`child + 0x1c`, spawn value 1.2) by 0.94 per tick; the miss path
  multiplies it by 1.1. The sprite size lanes (`sprite + 0x60/0x64`, 0.72
  half extents) are never rescaled.
- Sprite roll: `initialize_ring_or_special_effect_particles` seeds
  `sprite + 0x7c` to the child's base phase and `sprite + 0x80` (roll
  velocity, integrated by `update_sprite` @ 0x44df30) to minus the orbit
  spin, so the quads counter-rotate against the orbit. Kinds 3 and 6 zero
  the roll velocity instead.
- Star shower: every parent update increments the cadence lane (`+0x1e8`,
  wraps at 3), and `update_ring_or_special_effect_particle` calls
  `emit_ring_star_shower` for each child whenever the lane reads zero —
  once at spawn (the init pass runs the children with the lane still zero)
  and every third tick after. Each star is the family's small sprite
  (refs 0x88/0x84/0x86 → `ParticleRing/Explode/Slow-small.tga`, registered
  in `initialize_game_assets_and_world` @ 0x40acf0) spawned at the child's
  position with velocity `(sin/cos)(child_phase + pi/3) * radius * 0.3`,
  no gravity, half extents interpolating `0.4 → 0.2` over a 9-tick
  lifetime, alpha fading with sprite progress, default blend preset 0
  (`SRCALPHA/INVSRCALPHA`). The gate `config & 0x10` is set in the default
  config (`initialize_default_runtime_config` writes `0x5fe`).

## Port divergences fixed

| # | Divergence | Fix |
| --- | --- | --- |
| 1 | Halo orbit reused the parent's random phase lanes: random start angle, ring-speed-derived step, random direction, frozen outside the active state | `RingEffect.child_orbit_phase(_step)` accumulates `subgame_rate * tau/60` per tick in every live state, frozen for kind 3; children render at `i * tau/10 + accum` |
| 2 | Active rings drifted in X via `sin(active_phase) * 3` | Removed; the `+0x1dc` gate is never set natively. The spawn RNG draws stay for RNG-stream parity |
| 3 | Child sprite roll co-rotated with the orbit phase | Roll renders as `base_phase - accum` (counter-rotation), held at `base_phase` for kinds 3/6 |
| 4 | Collect/miss scale shrank/grew the sprite quads along with the radius | `presentation_scale` now only scales the orbit radius; sprite size stays at the 0.72 half extent |
| 5 | Star shower missing entirely (cadence lane existed but nothing consumed it) | `effects.Controller.spawnRingStarShowers` emits the native ten-star burst on spawn and on every cadence wrap, rendered as `ring_star`/`explode_star`/`slow_star` effects with the native size/velocity/fade lanes |

Halo sprite refs, sizes, color (alpha 0.8), blend presets (9 additive for
ring, 13 `SRCALPHA/SRCCOLOR` for explode/slow), and the world-XY quad
orientation were checked and already matched.
