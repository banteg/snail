# set_backdrop_texture_target @ 0x410f40

Exact match: 100.00% (14 target instructions, 14 candidate instructions),
clean masks.

The stable Windows harness name predates cross-port provenance. Android retains
the authored member as `cRBackdrop::SetWorld(int)` at `0x31980`, and its body is
the same two parallel transitions as Windows:

- invert the first blend fraction;
- shift its current world to previous world and install the argument;
- repeat the same operation for the second world-blend lane.

Those accesses, together with the two exact `tColour` constructor calls in
`construct_game_runtime`, prove two repeated 0x20-byte `BackdropWorldBlend`
owners at Windows `+0x67c` and `+0x69c`. Each record contains `tColour`, blend,
blend step, previous world, and current world.

Binary Ninja finds only the two calls in `initialize_backdrop`; both discard
EAX immediately. Android also establishes no result contract. Declaring the
Windows member `void` and removing the synthetic `return world` preserves all
14 native instructions and both clean masked operands.

The narrow Binary Ninja replay declares the exact `Backdrop` and
`BackdropWorldBlend` types and places the owner at `GameRoot +0x4ec10`.

## 2026-07-17 Binary Ninja owner-graph closure

A guarded six-function batch preview now verifies and cleanly reverts the
typed `void __thiscall` Backdrop ABI graph. Applying the same checked batch
persists all six member prototypes, including this authored `SetWorld(int)`
edge, instead of restoring the former scalar/`void*` views. The narrow replay
therefore owns these prototypes as normal idempotent updates rather than
reporting stale deferred database debt. No matcher source changed; all six
functions retain their exact instruction streams.

The same replay now carries the canonical complete 0x124-byte
`LandscapeScriptRecord` consumed by `change_backdrop`. This replaces Binja's
zero-width forward declaration with the already-proved producer layout, so
the backdrop texture id, split-pair flag, and distort value remain named
through the ownership boundary.
