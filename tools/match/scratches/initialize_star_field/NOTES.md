# initialize_star_field

- Source-shaped initializer for the `cRStarManager` entries and backing
  `Sprite` objects. Windows owns the manager at `GameRoot +0x4f33c`; its first
  `0x38` bytes are the constructed `BodBase` prefix and the manager-specific
  state begins at `+0x38`.
- The final call is the first vtable slot on the star-field object; the scratch
  models that slot as `update_star_field_callback()` while the named
  `update_star_field()` body remains the concrete callback at `0x4346f0`.
  Because that installed callback and both direct initializer callsites are
  void-valued, `cRStarManager::Init()` and its inherited callback slot are now
  modeled as `void`; the tail call remains byte-identical.

## Recovered source shape

- `StarManagerEntry` is a real `0x2c` record. The initializer uses array
  indexing rather than retaining one entry pointer; this reproduces native's
  byte-offset loop and leaves `esi = this`, `edi = index * 0x2c`, and `ebp = 0`.
- Camera-relative spawn position is the by-value vector expression
  `overlay_0.transform.basis_forward * 50 + overlay_0.transform.position`.
  Together with the later vector multiply/divide/add expression, this recovers
  the native `0x60` frame and its vector temporaries instead of padding it.
- The initial direction is a temporary `Vector3(random_x, random_y, 0)` copied
  into the entry. VC6's right-to-left argument evaluation explains native's
  first-random-is-y call order and the three-dword temporary copy.
- Velocity scaling is the in-place `Vector3::operator*=` idiom. Promoting that
  semantic operator raises the scratch from 84.34% to 98.38% and exactly
  recovers the scale-once x87 sequence.
- `travel_distance +0x24` advances by `speed +0x20` and wraps after `35`; the
  per-entry `alpha_scale +0x28` feeds sprite alpha directly in
  `update_star_positions`. These replace the weaker `phase`/`twinkle` labels.

Current focused result after the shared vector-operator consolidation: 97.57%,
247/247 candidate/target instructions, a 126-instruction prefix, and 25 masked
operands clean. The six residual instruction-order differences are VC6
scheduling around the random travel store/color arguments and the corner-scale
sprite dereference; the candidate otherwise has the exact instruction count
and semantics. A retained tail-entry pointer probe regressed to 66.80% by
changing register ownership, so it was rejected rather than forcing the final
scheduling differences.

## 2026-07-11 cRStarManager ownership

Android and iOS preserve the complete `cRStarManager` lifecycle and the
`Star.o` source object. The shared match type now uses `StarManager` and the
already-proven `StarManagerEntry` vocabulary consistently with the BN/IDA
header. Its exact 0x4c extent closes between `MainMenu` and `Options` in
`GameRoot`; the rename is codegen-neutral at the same 98.38% near match.

## 2026-07-14 root ownership cleanup

The camera transform now comes through the canonical `GameRoot* g_game`
owner instead of a raw `char*` base followed by a local cast. This is
byte-identical at 98.38%, 247/247 instructions, with all 25 operands clean;
the remaining differences are still only the documented random/color and
corner-scale scheduling windows.

## 2026-07-19 entry and Sprite lifetimes

Binary Ninja now preserves each materialized `StarManagerEntry*`, its borrowed
`Sprite*`, and the `Vec3*`/`tColour*` children used by the position, velocity,
color, size, and final copy phases. The refreshed listing consequently exposes
the entry's speed/travel/position/velocity fields and the Sprite flag, color,
size, position, and velocity fields instead of `void*` plus numeric offsets.
The manager remains the owner of the entry bank; every entry merely borrows its
Sprite from `SpriteManager`.

The native EDI value is deliberately left as an automatic byte offset. A live
integer retype initially made the decompiler index the final
`facing_refresh_progress` store with the already incremented EBX loop counter,
even though EDI still addressed the prior entry. That annotation was removed
before export; only the independently materialized pointers are retained. The
guarded replay verifies all five owner widths and their exact fields before
setting the stable register lifetimes, and a second run is idempotent.

Matcher source is unchanged at the honest 97.57%, 247/247-instruction frontier,
prefix 126, with all 25 operands clean. Reversing the commutative corner-scale
multiply was codegen-neutral and was reverted; the remaining six instructions
are scheduling only.

## 2026-07-19 remaining Sprite member lifetimes

Eight additional SSA definitions reload the same entry-owned borrowed
`Sprite*` for isolated member stores. They now retain that type through
`progress`, `progress_step`, `gravity_step`, `color`, `size_start`,
`corner_scale`, and `facing_refresh_progress`; the corner-scale path also
materializes its true `StarManagerEntry*` before following `entry->sprite`.
This removes the last raw Sprite `+0x60/+0x68/+0x6c/+0x78/+0x88/+0x8c`
offsets from the Binary Ninja listing.

These are borrowed lifetimes into sprites allocated by `SpriteManager`; they
do not move ownership into `StarManagerEntry`. The EDI induction remains an
automatic byte offset for the previously documented reason. The replay now
guards nineteen stable definitions and remains idempotent. Matching source and
the honest 97.57%, 247/247-instruction, 25-clean-operand result are unchanged.
