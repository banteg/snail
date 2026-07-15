# initialize_sub_loc @ 0x4088c0

This exact helper is the `SubLoc` constructor wrapper: it runs the shared
`cRBod` base constructor,
installs the cell-specific vtable at `0x497368`, increments the counter later
reported as `LocCount`, and returns the receiver.

The table entry at `0x497368` points directly to
`update_sub_loc @ 0x439d50`, independently confirming the
`cRSubLoc::AI()` receiver mapping.

Ownership is fixed by three independent Windows facts:

- `initialize_runtime_pools_and_path_template_bank` calls it exactly `0x6400`
  times over the owned runtime-cell slab at `SubgameRuntime +0x3bfac8`;
- every call advances by the exact `SubLoc` size, `0x54`;
- `construct_game_runtime` reports the incremented global as
  `LocCount=%i Memory=%i`, with memory computed as `count * 0x54`.

The scratch defines `initialize_sub_loc` directly on `SubLoc`; the old generic
`initialize_bod` label is retired. It remains exact at 10/10 instructions with
four clean masked operands.

## 2026-07-14 BodBase inheritance closure

`SubLoc` now derives directly from the `BodBase` initialized here. The vtable
write uses the inherited zero-offset object, `BodBase::position +0x10` owns the
cell anchor used across the runtime grid, and the first cell-specific field
remains `attachment_template_record +0x38`. The constructor remains exact at
10/10 instructions with all four operands clean.

## 2026-07-15 durable root composition replay

The owned 25,600-cell slab now sits under a complete `SubgameRuntime` embedded
at `GameRoot +0x74618`; the runtime is exactly `0x1272838` bytes and ends at
root `+0x12e6e50`. All three IDA replay lanes preserve that composition instead
of letting the sparse frame view truncate the runtime tail. The constructor
remains exact at 10/10 instructions with all four operands clean.
