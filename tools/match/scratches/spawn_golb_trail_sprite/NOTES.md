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
- the supplied world position is copied into the sprite and `object_ref` is
  attached from the projectile

The typed `Vector3* velocity` local is required for the native store schedule:
without it, VC6 delays the progress/scale constants until after velocity zeroing
and lands at 93.62%.
