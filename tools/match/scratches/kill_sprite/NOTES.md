# WIP - sprite unlink/free-list return

Current source maps the native behavior: validates the live flag, reports the texture-name-backed error string from `texture_ref + 0xc`, unlinks from the owner active bucket, and pushes the sprite onto `g_sprite_free_head`.

Current residual: one scheduling difference in the active-head path. Native stores `g_sprite_active_heads[owner] = next` before loading `g_sprite_free_head`; VC6 hoists the free-head load one instruction earlier from the clear source shape. Do not force this with volatile or dummy barriers.
