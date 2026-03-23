# Binary Comparison Findings

Systematic comparison of the Zig port against the Windows binary (primary target) with Android/iOS cross-reference.
Analysis date: 2026-03-23.

---

## Critical: Incorrect Score Values

### 1. Health pickups award 250 points — should be 0

**Zig** (`gameplay.zig:1047`):
```zig
self.recordScore(&self.score.health_collect, 250);
```

**Windows** (`handle_subgoldy_collisions` at `0x4454f3`): health pickup calls `play_sound_effect(0xe)`, `sub_43a010` (particle effect only), and `apply_damage_gauge_delta(-0.5, 0)`. There is **no** call to `add_subgoldy_score`. Decompiling `sub_43a010` confirms it only spawns 8 visual particles — no scoring.

**Android** (`cRSubGoldy::Collision`): Android *does* call `cRSubGoldy::ScoreAdd(6)` for health, and type 6 = 250 in Android's score table. The Zig value matches Android but not Windows.

**Impact**: Every health pickup inflates score by 250 points vs the Windows original.

### 2. Historical parcel double-score (resolved)

**Windows** (`handle_subgoldy_collisions` at `0x4452e0`): `add_subgoldy_score(player, 3, 0)` — type 3 = 100 points. Then the parcel enters a **flight object** (`sub_414820`) that tracks it to a delivery point, calling `add_subgoldy_score(0, 0)` (10 points) on arrival. Additional row-event scores may follow via `flush_row_event_display`.

**Zig** (`gameplay.zig:596`, `gameplay.zig:2418`): parcel pickup still awards 100 immediately, but the register lane is now the recovered `+10` delayed delivery score via `parcel_delivery_register_score`.

**Remaining gap**: the port still uses the row-event delivery controller instead of the native standalone parcel-flight owner, so the broad score shape is now right while the exact visual/runtime owner is still approximate.

### 3. Slow/velocity rings (types 3, 7) incorrectly scored

**Zig** (`gameplay.zig:1132-1134`):
```zig
if (ring_kind != .none) {
    self.recordScore(&self.score.ring_collect, 100);
}
```
All non-none rings get 100 points, including `.slow` and `.explode` kinds.

**Windows** (`handle_subgoldy_collisions` ring loop): ring types 1, 2, 4, 5, 6, 8 all call `add_subgoldy_score(2, 0)` = 100 points. Ring types **3 and 7** only set `player->velocity.z = -0.1` and play a sound — they **never** call `add_subgoldy_score`.

**Android** (`cRSubGoldy::Collision` ring loop): same pattern — types 3 and 7 skip `ScoreAdd`.

**Impact**: If Zig ring kinds `.slow` or `.explode` map to binary types 3/7, those rings incorrectly inflate score by 100 per collection.

---

## Structural: Collision Model Mismatch

### 4. Grid-cell collision vs 3D distance collision

**Windows**: Every tick, iterates all active runtime object pools (rings, garbage, slugs, parcels, health, jetpack, salt/Wall2). For each active object, computes a 3D distance vector `(dx, dy, dz)` from the player's world position, normalizes it, and compares the magnitude against per-type thresholds:

| Object | Distance threshold | Z threshold | Extra checks |
|--------|-------------------|-------------|--------------|
| Garbage | 0.98 | < 1.0 | — |
| Salt/Wall2 | 0.49 | < 1.0 | — |
| Slug | 1.5675 | < 2.0 | First-hit latch |
| Parcel | 1.24 | < 1.0 | — |
| Health | 0.98 | < 1.0 | abs(dy) < 0.4, player.y >= 0.49 |
| Jetpack | 3.0 | < 1.0 | — |
| Ring | 0.98 | < 1.0 | — |

**Zig**: Processes each row as the player crosses it, checking the grid cell at the resolved lane index. Collision is binary — if the player's integer row matches and the cell type matches, the event fires.

**Impact**: The binary's continuous distance checks allow collection/collision from any angle within a radius. The Zig's discrete row checks mean objects can only be hit when the player's row index crosses theirs. This particularly affects jetpack (radius 3.0 = can be collected from 3 rows away in the binary) and slug (radius 1.5675, Z threshold 2.0 = detected from 2 rows ahead).

---

## Significant: Damage Gauge Oversimplified

### 5. Damage warning state machine missing gates and faster drain

**Zig** (`gameplay.zig:1212-1229`): Three states — `idle → filling → draining`. Transition from idle to filling triggers when `damage_gauge >= 1.0`. Drain uses a single rate of `-0.00166667` per tick.

**Windows** (`update_damage_gauge` at `0x440fd0`):
- **Entering filling (state 0→1)**: requires `damage_gauge >= 1.0` AND two additional game flags at `+0x430199` and `+0x4301bc` both equal to 0. If either flag is set, the warning doesn't trigger.
- **Entering drain (state 1→2)**: requires a game value at `+0x42fde8` equals `0.49` (probably track center validity). Without this, the state sits in filling.
- **Drain (state 2)**: base drain is `-0.00166667`, but when flag `+0x4301bc` is set, an additional `-0.00666667` (4× faster) drain is also applied each tick.
- **Exiting drain (state 2→0)**: has multiple OR conditions involving game flags (fill reaching 0, track state, hover state, and a combat flag), not just `gauge <= 0`.

**Impact**: The simplified state machine will trigger warnings when it shouldn't (missing flag gates), drain too slowly in some situations (missing 4× accelerated drain), and exit at the wrong time.

---

## Historical: Camera Findings (Resolved)

### 6. Dynamic FOV now matches the recovered 110°–160° lane

**Windows** (`initialize_cameraman` at `0x4461ba`): initializes FOV to `110.0` (hex `0x42dc0000`). During gameplay (`update_cameraman` at `0x446671`), FOV ranges from 110 to 160 based on attachment state, lerped at 0.3 per tick.

**Zig** (`gameplay.zig:2901`, `main.zig:12268`): the live gameplay camera now publishes the runner-owned dynamic FOV instead of the old fixed frontend value.

### 7. Speed-driven cameraman lift and pitch are now ported

**Windows** (`update_cameraman`): applies a complex vertical offset based on player speed (blending between `speed * 0.35` and `speed * 1.15` based on row progress), speed-dependent pitch (`(-2.0 - (speed - 0.49) * 5.0) * 0.01745` radians, clamped to ±1.2215 rad), and separate attachment-driven camera tilt from fields at `+0x354` and `+0x358`.

**Zig** (`gameplay.zig:1164`, `gameplay.zig:1172`, `gameplay.zig:3159`): the cameraman now uses the recovered speed-driven vertical lift and pitch formulas, and multiplies the attachment or launch lift envelope by the same live speed owner like the Windows branch.

### 8. Z deadzone follow is now ported

**Windows**: maintains a deadzone where the camera follows in Z only when the player-to-camera distance exits the range [1.7, 3.0]:
```
if (player_z - camera_z > 3.0): camera_z = player_z - 3.0
if (player_z - camera_z < 1.7): camera_z = player_z - 1.7
```

**Zig** (`gameplay.zig:1180`, `gameplay.zig:3222`): the live cameraman now clamps the previous desired matrix Z against the recovered `[1.7, 3.0]` player delta before interpolation, matching the Windows controller shape.

### 9. Lateral eye terms now match the recovered matrix writes

**Windows** (`update_cameraman`): seeds the desired matrix with `player_x * 0.4` and then adds a second `player_x * 0.33333334` write before the matrix blend.

**Zig** (`gameplay.zig:3184`, `gameplay.zig:3190`): the live cameraman now mirrors those recovered lateral matrix writes instead of the earlier single-term chase-eye approximation.

---

## Significant: Physics Model Differences

### 10. Garbage impact still uses a partial forward-motion owner

**Windows** (`handle_subgoldy_collisions` garbage):
```
velocity.x -= (dx_normalized) * velocity.z * 0.18
velocity.z -= (dz_normalized) * velocity.z * 0.10
```
with both writes skipped entirely while invincible, followed by grounded-track `velocity.x *= 1 - track_center_x * 0.1` damping in `update_subgoldy`.

**Zig** (`gameplay.zig`):
```zig
speed_rows_per_second -= dz_normalized * speed_rows_per_second * 0.10
native_velocity_x_per_tick -= dx_normalized * (speed_rows_per_second / 60.0) * 0.18
```
The port now matches the native direction-vector sign, the invincible motion guard, and the decaying
track-mode lateral `velocity.x` lane. The remaining gap is the forward owner: `velocity.z` still hands
back into the high-level `speed_rows_per_second` scaffold instead of the full native velocity block at
`player + 0x410` / `player + 0x418`.

**Impact**: lateral garbage kick is now much closer to native, but the broader forward-speed recovery after the hit is still not literal.

### 11. Speed model fundamentally different

**Windows** (`build_subgame_level`/`sub_437e80`): game-level speed is stored at `game+0x30` as a scalar in range ~0.2–1.1, computed per-mode from level metadata:
```
if (level_speed < 1.0): game_speed = level_speed * 0.9 + 0.2
else: game_speed = 1.1
```
The player's actual velocity (`player+0x410`) is a float that feeds through the movement controller.

**Zig**: Uses a flat `speed_rows_per_second: f32 = 12.0` default with direct rows/second semantics.

The relationship between the binary's speed scalar and the Zig's rows/second isn't established. The binary's player velocity at `+0x410` is a world-space float, not a row count.

---

## Minor: Platform Score Table Divergence

### 12. Windows and Android ScoreAdd type tables differ

| Type | Windows | Android |
|------|---------|---------|
| 0 | 10 | 10 |
| 1 | 500 | 500 |
| 2 | 100 | — |
| 3 | 100 | — |
| 4 | 100 | 100 |
| 5 | custom | — |
| 6 | — | 250 |

The Zig code should target the Windows table. Currently, the health scoring (250) follows the Android table.

---

## Summary Priority

| # | Finding | Severity | Fix Effort |
|---|---------|----------|------------|
| 1 | Health pickup scores 250 instead of 0 | High | Trivial — remove `recordScore` call |
| 2 | Historical parcel double-score | Resolved | The score split is now 100 pickup + 10 register; remaining gap is the exact flight owner |
| 3 | Slow/velocity rings score 100 instead of 0 | Medium | Exclude `.slow` (and possibly `.explode`) from scoring |
| 4 | Grid-cell vs 3D distance collision | High (structural) | Requires new collision system |
| 5 | Damage gauge missing gates/faster drain | Medium | Add flag checks and secondary drain rate |
| 6 | Historical fixed-FOV camera | Resolved | Live gameplay now uses the recovered runner-owned dynamic FOV |
| 7 | Historical missing speed-dependent camera | Resolved | Speed-driven lift and pitch are now ported |
| 8 | Historical missing Z deadzone follow | Resolved | Deadzone clamp now mirrors the recovered cameraman lane |
| 9 | Historical lateral eye mismatch | Resolved | The cameraman now matches the recovered two-write X translation |
| 10 | Garbage still uses the wrong motion owner | Medium | Port the native player velocity lanes |
| 11 | Speed model not mapped | High (structural) | Map binary speed scalar to Zig rows/second |
| 12 | Android score table leaking in | Low | Reference Windows table only |
