# Android -> Windows Symbol Matches (Sweep 6)

Sixth cross-reference pass covering the shared math-random helper family that sits immediately beside the camera and matrix helper block in Windows.

**Legend**: `NEW` = currently unnamed (`sub_XXXX`) in BN before this pass, `EXISTS` = already named

---

## Shared Math Random Helpers

Android exposes a small global random-helper family that lines up with the remaining Windows startup-era helpers around `0x44c8d0` to `0x44c970`:

| Android Symbol | Windows Addr | Current Name | Proposed Name | Status |
|---|---|---|---|---|
| `gRMathRand2Init()` | 0x44c8d0 | `sub_44c8d0` | `initialize_math_random_table` | NEW -- fills the shared `0x1fff`-entry table by repeatedly calling the underlying Windows LCG helper at `0x48bfe5`, then resets the ring index |
| `Rand()` / `gRMathRand2()` | 0x44c900 | `sub_44c900` | `next_math_random_value` | NEW -- modular table fetch used by `initialize_blink_random`, `shuffle_voice_set`, starfield setup, hazard scatter, and several gameplay particle paths |
| `RandSeed(int)` | 0x44c970 | `sub_44c970` | `set_math_random_seed` | NEW -- stores the caller-provided seed into the shared Windows LCG state just before randomized systems consume the table |

---

## Xref Notes

- `next_math_random_value` is the real shared gameplay random source, not a camera-local utility. Windows xrefs include:
  - `initialize_blink_random`
  - `shuffle_voice_set`
  - `initialize_star_field`
  - `spawn_track_garbage_hazard`
  - `spawn_slug_hazard`
  - `firework_shoot`
  - `release_snail_weapons`
  - `update_jetpack_visual`
- `set_math_random_seed` currently shows two clear Windows callsites:
  - `update_click_start`, seeded from `Game + 0x1047190`
  - `populate_runtime_track_cells_from_segments`, seeded from the current runtime build context
- `initialize_trigonometry_tables` already calls `initialize_math_random_table`, so the random-table bootstrap is part of the same one-time gameplay math startup lane.

---

## Practical Consequences

- The helper behind the game's many "random * 1/32768" patterns is now named and centralized.
- The Windows random-table path is structurally closer to the Android global math-rand family than to any per-subsystem RNG.
- The remaining unnamed helpers in this strip are now mostly local-only utilities:
  - the fixed-point conversion pair at `0x44c890` / `0x44c8b0`
  - the scale-matrix helper at `0x44cde0` and its thin wrapper at `0x44c880`

