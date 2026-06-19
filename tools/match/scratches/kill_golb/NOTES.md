# kill_golb @ 0x414670

Exact match: 100.00%, 132/132 instructions.

This helper tears down one live Golb projectile:

- removes the primary projectile BOD from the shared active/free list;
- clears the live state at `+0x244`;
- for kind `0`, kills the owner sprite at `+0x248`;
- for kind `1`, removes the secondary BOD at `+0x80`; and
- for kind `2`, removes the tertiary BOD at `+0x118` and clears bit `0x1000`
  on the attached sprite at `+0x198`.

The exact source shape uses the shared typed `BodNode`/`BodList` intrusive-list
implementation as exact `recycle_bod_to_free_list`, spells the kind dispatch as
a `switch`, and calls `kill_sprite` as a sprite member function.

Type consolidation:

- `GolbShot` is now promoted in `tools/match/include/golb.h` for this
  teardown and the small trail/smoke/impact sprite emitters. This exact match
  anchors the primary/secondary/tertiary `BodNode` offsets, `kind +0x1c0`,
  `state +0x244`, and the variant-specific owners at `+0x198`/`+0x248`.
- `+0x198` is intentionally opaque in the shared header: kind-2 teardown reads
  an attached `Sprite*`, while `update_golb_ai` uses the same lane as homing
  state through `+0x1bf`.
