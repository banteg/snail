# emit_ring_star_shower result

- **Before:** `90.77%`; target `65` instructions, candidate `65`; common prefix
  `1/65`; masked operands `9 ok`, `0 unresolved`, `0 mismatch`.
- **After:** `100.00%`; target `65` instructions, candidate `65`; common prefix
  `65/65`; masked operands `9 ok`, `0 unresolved`, `0 mismatch`.
- **Accepted changes:** stage unscaled sine/cosine results in a semantic
  `Vector3 orbit_velocity`, scale into `velocity`, retain the aggregate velocity
  copy, and use direct `star->position = sprite->position` assignment. Together
  these recover the native `0x18` frame and the final gravity/z store schedule.
- **Rejected trials:** scalar x/y locals (`85.94%`, `63/65`); scalar x with x87
  y (`84.62%`, `65/65`); scalar x with `double` y (`82.81%`, `63/65`); winning
  two-vector velocity with named position pointers (`98.46%`, `65/65`, prefix
  `59/65`); gravity before aggregate position assignment (`81.54%`, prefix
  `20/65`); manual dword or two-lane position copies (`82.17%`, `64/65`, prefix
  `5/65`); staged source-position vector (`87.02%`, `66/65`, prefix `5/65`).
- **Next region to attack:** none in this target; the normalized instruction
  stream and masked operand audit are exact.
