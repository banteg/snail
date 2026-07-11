# initialize_star_field

- Source-shaped initializer for the `cRStarManager` entries and backing
  `Sprite` objects. Windows owns the manager at `GameRoot +0x4f33c`; its first
  `0x38` bytes are the constructed `BodBase` prefix and the manager-specific
  state begins at `+0x38`.
- The final call is the first vtable slot on the star-field object; the scratch
  models that slot as `update_star_field_callback()` while the named
  `update_star_field()` body remains the concrete callback at `0x4346f0`.

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

Current focused result: 98.38%, 247/247 candidate/target instructions,
29-instruction prefix, and 25 masked operands clean. The four residual
instruction-order differences are VC6 scheduling around the random travel
store/color arguments and the corner-scale sprite dereference; the candidate
otherwise has the exact instruction count and semantics. A retained tail-entry
pointer probe regressed to 66.80% by changing register ownership, so it was
rejected rather than forcing the final scheduling differences.

## 2026-07-11 cRStarManager ownership

Android and iOS preserve the complete `cRStarManager` lifecycle and the
`Star.o` source object. The shared match type now uses `StarManager` and the
already-proven `StarManagerEntry` vocabulary consistently with the BN/IDA
header. Its exact 0x4c extent closes between `MainMenu` and `Options` in
`GameRoot`; the rename is codegen-neutral at the same 98.38% near match.
