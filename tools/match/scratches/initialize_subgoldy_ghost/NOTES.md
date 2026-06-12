# Residual diff — 97.67%, 107/108 insns

The initializer body is pinned: it allocates both `SPRITES/GHOST.TGA` sprite
slots (`sprite_id 159`) for the player slot, marks the sprite dword flags with
`0x800`, clears the native timer lanes at `+0x68`, `+0x6c`, and `+0x78`, copies
white RGBA into `+0x2c`, sets both scales to `0.5`, and places the pair at
`x = +/-4.5`, `y = 1.0`, `z = 0.0`.

The remaining miss is the final visibility-flag clear. The target materializes
`0xffffffbf` in `ecx` and uses full dword `and` instructions for both sprite
flag clears; VC6.5 narrows the same semantic clear to immediates, including
`and al, 0xbf` for the returned second flag. Do not force this with dead or
volatile code.
