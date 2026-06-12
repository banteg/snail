# Exact match — 100.00%, 108/108 insns

The initializer body is pinned: it allocates both `SPRITES/GHOST.TGA` sprite
slots (`sprite_id 159`) for the player slot, marks the sprite dword flags with
`0x800`, clears the native timer lanes at `+0x68`, `+0x6c`, and `+0x78`, copies
white RGBA into `+0x2c`, sets both scales to `0.5`, and places the pair at
`x = +/-4.5`, `y = 1.0`, `z = 0.0`.

The final visibility-flag clear needs the second sprite clear expressed as the
returned compound assignment. With that source shape, VC6.5 materializes the
shared `0xffffffbf` mask in `ecx` and emits the target dword `and` sequence for
both sprite flag clears.
