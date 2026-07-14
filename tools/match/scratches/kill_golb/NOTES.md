# kill_golb @ 0x414670

Exact match: 100.00%, 132/132 instructions.

This helper tears down one live Golb projectile:

- removes the primary projectile BOD from the shared active/free list;
- clears the live state at `+0x244`;
- for kind `0`, kills the owner sprite at `+0x248`;
- for kind `1`, removes the secondary BOD at `+0x80`; and
- for kind `2`, removes the tertiary BOD at `+0x118` and clears bit `0x1000`
  on the reserved contact-target object at `+0x198`.

The exact source shape uses the shared typed `BodNode`/`BodList` intrusive-list
implementation as exact `recycle_bod_to_free_list`, spells the kind dispatch as
a `switch`, and calls `kill_sprite` as a sprite member function.

Type consolidation:

- `GolbShot` is now promoted in `tools/match/include/golb.h` for this
  teardown and the small trail/smoke/impact sprite emitters. This exact match
  anchors the primary/secondary/tertiary `BodNode` offsets, `kind +0x1c0`,
  `state +0x244`, and the variant-specific owners at `+0x198`/`+0x248`.
- The exact `EnemyManager` search/register pair proves that `+0x198`
  is a borrowed `ContactTargetObject*`: `create_golb` sets its reservation bit
  and this teardown clears the same bit. Promoting that owner leaves the exact
  132/132 instruction body unchanged.

2026-07-14 root-list closure: all three variant removals now name
`GameRoot::active_bod_list` directly. The canonical owner graph preserves the
exact 132/132 body and all 16 clean operands.

The kind-0 `+0x248` owner is now shared as `GolbShot::render_sprite` across
creation, per-tick position updates, and this exact teardown. Replacing the
last local cast preserves the exact 132/132 body and all 16 clean operands.
