# construct_game_runtime reconstruction notes

`construct_game_runtime` allocates the root game object, runs the embedded
manager constructors, installs the known callback tables, publishes
`g_game_base`, and reports constructor counters.

Current focused result:

- match: 80.40%
- target/candidate instructions: 310 / 287
- prefix: 0 / 310
- masked operands: 111 clean, 4 unresolved, 0 mismatched

The remaining broad shape gap is the compiler-generated setup around the root
allocation. The native function has MSVC EH registration and batches the
debug-report varargs stack cleanup into larger `add esp` groups; the readable
source emits ordinary per-call cleanup. The main constructor body is aligned
through the slot loops, render-camera array, overlay slots, border pool,
cached-mesh pool, backdrop/star-field setup, intro-logo arrays, runtime pools,
and tip manager.

Unresolved operands are intentionally left visible:

- `operator new` at `0x48ba3f`;
- callback tables at `0x4972f0` and `0x4972b0`;
- the `LocMirrorCount` counter at `0x4dfae0`.

The helper constructors at `0x408000` and `0x408040` only appear in this
constructor in the current exports, so the scratch keeps them as local
`initialize_unknown_*` methods rather than adding speculative names.
