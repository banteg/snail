# WIP - sprite pool topology

This scratch is a relationship map for the shared sprite manager: it clears the paused flag and active owner buckets, seeds `g_sprite_free_head` with the first sprite, initializes all 3000 sprite nodes, links the free-list chain, and records the final bucket tail around `0x83cbc/0x83cc0`.

Current residuals are register and block-layout differences around the zero-store setup and the first/last-node special cases. The source should stay topology-first until the exact VC6 loop shape is isolated.

`SpriteManager` now carries the recovered pool fields (`paused`, 3000 sprite
slots at `+0x04`, five active heads at `+0x83d64`, and `free_head` at
`+0x83d78`). A fully field-access body was tested but dropped because VC6 moved
`this` to `edi` and reduced the score to 22.22%; the retained body keeps the
better topology-first 47.19% shape.
