# sine @ 0x44c9d0

Exact match: 100.00%, 7/7 instructions.

This helper maps radians into the 0x2000-entry sine lookup table at
`data_77ff8c`. Keeping the scale as a named intermediate preserves the native
two-multiply source shape. It is used by pickup bobbing, projectile halos,
damage flash, nuke/ring presentation, and camera paths.
