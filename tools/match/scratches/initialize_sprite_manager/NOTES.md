# WIP - sprite pool topology

This scratch is a relationship map for the shared sprite manager: it clears the paused flag and active owner buckets, seeds `g_sprite_free_head` with the first sprite, initializes all 3000 sprite nodes, links the free-list chain, and records the final bucket tail around `0x83cbc/0x83cc0`.

Current residuals are register and block-layout differences around the zero-store setup and the first/last-node special cases. The source should stay topology-first until the exact VC6 loop shape is isolated.
