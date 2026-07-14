# set_backdrop_texture_target @ 0x410f40

Exact match: 100.00% (14 target instructions, 14 candidate instructions),
clean masks.

The stable Windows harness name predates cross-port provenance. Android retains
the authored member as `cRBackdrop::SetWorld(int)` at `0x31980`, and its body is
the same two parallel transitions as Windows:

- invert the first blend fraction;
- shift its current world to previous world and install the argument;
- repeat the same operation for the second world-blend lane.

Those accesses, together with the two exact `Color4f` constructor calls in
`construct_game_runtime`, prove two repeated 0x20-byte `BackdropWorldBlend`
owners at Windows `+0x67c` and `+0x69c`. Each record contains `Color4f`, blend,
blend step, previous world, and current world.

Binary Ninja finds only the two calls in `initialize_backdrop`; both discard
EAX immediately. Android also establishes no result contract. Declaring the
Windows member `void` and removing the synthetic `return world` preserves all
14 native instructions and both clean masked operands.

The narrow Binary Ninja replay declares the exact `Backdrop` and
`BackdropWorldBlend` types and places the owner at `GameRoot +0x4ec10`.
Prototype preview produces the intended typed decompile, but live verification
restores the stale scalar `int32_t(void*, int32_t)` form. The replay therefore
reports all six Backdrop receiver prototypes as deferred instead of forcing or
misreporting a mutation the database rejects.
