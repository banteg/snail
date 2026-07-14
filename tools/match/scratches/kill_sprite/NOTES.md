# Exact - sprite unlink/free-list return

Current source maps the native behavior: validates `SPRITE_FLAG_ACTIVE`,
reports the texture-name-backed error string from `texture_ref->name`
(`TextureRef+0x0c`), unlinks from the owner active bucket, and pushes the
sprite onto `g_sprite_manager.free_head`.

This is exact once the active buckets and free-list head are modeled as fields
inside `g_sprite_manager` (`active_heads[5]` at `+0x83d64`, `free_head` at
`+0x83d78`). Modeling them as independent globals caused VC6 to hoist the
free-head load before the active-head store.

Rejected source-shaped probe:

- assigning `g_sprite_active_heads[owner] = next_sprite` instead of `next`
  regressed the block layout and removed the native reload; the correct fix is
  the manager relationship, not an expression-order tweak.
