# spawn_golb_trail_sprite @ 0x415bb0

Exact match under the standard `msvc6.5 /O2 /G5 /W3` profile.

This helper allocates the short-lived projectile trail sprite for the straight
Golb family:

- owner slot comes from `owner_player->player_slot`
- sprite id is `0x21`
- additive draw flag `0x800` is set and age/gravity/velocity lanes are zeroed
- the player movement flag branch writes two alternate progress-step values,
  then the native source unconditionally overwrites the same lane with
  `0.55555558f`
- the supplied world position is copied into the sprite and the projectile's
  `shot_slot_index` is forwarded bit-for-bit into `Sprite::object_ref`

The typed `Vector3* velocity` local is required for the native store schedule:
without it, VC6 delays the progress/size constants until after velocity zeroing
and lands at 93.62%.

Type consolidation:

- This scratch now uses the promoted `GolbShot` view in
  `tools/match/include/golb.h`, sharing `shot_slot_index +0x274` and
  `owner_player +0x278` with the exact creation and lifecycle helpers. The
  match stays exact.

## 2026-07-16 analysis receiver replay

The durable Binary Ninja and IDA ownership replays now preserve this helper as
`Sprite* __thiscall(GolbShot*, Vec3*)`. That agrees with the exact Windows
body, whose success path returns the allocated sprite, and prevents either
decompiler from falling back to a generic receiver when the shared Golb types
are replayed. The exact 47/47 matcher result is unchanged.

## 2026-07-23 Sprite owner lifetime replay

Binary Ninja's allocation result is now replayed as the complete `Sprite*`
owner for its register lifetime. The exported decompile consequently exposes
the flags, progress, lifetime, size, velocity, gravity, position, and
`object_ref` writes through `trail_sprite` instead of raw `void**` word
indices. This is analysis-only and leaves the exact 47/47 source match
unchanged.

## 2026-08-09 shot-slot identity closure

Whole-image Windows xrefs prove `GolbShot +0x274` is the 12-entry shot-bank
index written by `create_golb`; this exact helper is its only reader. The
explicit cast documents that the integer identity is copied into the trail
sprite's opaque `object_ref` lane. Impact sprites do not consume the field and
retain their allocator-installed `-1` sentinel. Removing the stale pointer
alias from `GolbShot` leaves this helper exact at 47/47 instructions with both
masked operands clean.
