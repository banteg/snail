# Exact match

`enqueue_tip_message` matches exactly at 26/26 instructions.

The exact source shape is a plain `while (1)` scan over the three tip slots:
break when the current slot is inactive, otherwise advance the slot pointer and
index, and report `"Run out of Tips"` as soon as the index reaches three.

Rejected source-shaped probes:

- a natural `for (slot = slots; slot->active; ++slot)` form made VC6 look ahead
  to the next slot and moved the exhaustion path after the success path;
- label/goto spellings kept the right semantics but still rotated the loop into
  a bottom-tested shape;
- a post-loop exhaustion check kept the cold path near the target but emitted a
  redundant compare before the error call.

Keep the current `while (1)` form as the tip-slot allocator idiom.

2026-06-16 type consolidation: `TipManager`, `TipSlot`, and
`TipMessageDefinition` now come from shared `tip_manager.h`. The allocator keeps
the exact 26/26-instruction match.
