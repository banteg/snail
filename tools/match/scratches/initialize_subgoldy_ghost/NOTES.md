# Exact match — 100.00%, 108/108 insns

The initializer body is pinned: it allocates both `SPRITES/GHOST.TGA` sprite
slots (`sprite_id 159`) for the player slot, marks the sprite dword flags with
`SPRITE_FLAG_GAMEPLAY_OWNED`, clears `progress`, `progress_step`, and
`gravity_step`, copies white RGBA into `color`, sets both scales to `0.5`, and
places the pair at
`position.x = +/-4.5`, `position.y = 1.0`, `position.z = 0.0`.

The final visibility-flag clear is a natural compound-assignment statement.
Even with the authored void contract, VC6.5 materializes the shared
`0xffffffbf` mask in `ecx` and emits the target dword `and` sequence for both
sprite flag clears. The previous synthetic returned assignment was unnecessary:
the void source remains exact at 108/108 instructions with all six operands
clean.

The mask is now derived from `SPRITE_FLAG_RENDER_ENABLED`; exact
`set_subgoldy_ghost_z` sets the same named policy when the pair receives its
live Z. Together the initializer and setter close the ghost visibility
lifecycle without retaining raw `0x40` spellings.
