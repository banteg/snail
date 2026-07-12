# initialize_bod @ 0x4088c0

The stable Windows harness name is historical. This exact helper is the
`SubLoc` constructor wrapper: it runs the shared `cRBod` base constructor,
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

The scratch therefore defines the historical `initialize_bod` method directly
on `SubLoc`; the receiver ownership is real even though the stable Windows
method name is generic. It remains exact at 10/10 instructions with four clean
masked operands.
