# construct_game_runtime reconstruction notes

`construct_game_runtime` allocates the root game object, runs the embedded
manager constructors, installs the known callback tables, publishes
`g_game_base`, and reports constructor counters.

Current focused result:

- match: 80.40%
- target/candidate instructions: 310 / 287
- prefix: 0 / 310
- masked operands: 115 clean, 0 unresolved, 0 mismatched

The remaining broad shape gap is the compiler-generated setup around the root
allocation. The native function has MSVC EH registration and batches the
debug-report varargs stack cleanup into larger `add esp` groups; the readable
source emits ordinary per-call cleanup. The main constructor body is aligned
through the slot loops, render-camera array, overlay slots, border pool,
cached-mesh pool, backdrop/star-field setup, intro-logo arrays, runtime pools,
and tip manager.

2026-06-20 startup-runtime reference pass:

- Curated the CRT allocation helpers at `0x48ba34`/`0x48ba3f`, the runtime
  callback tables at `0x4972b0`, `0x4972f0`, and `0x4972f4`, and the
  `LocMirrorCount` counter at `0x4dfae0`.
- This clears the previous masked audit debt for `operator new`, the overlay
  stream and root-slot callback tables, and `g_loc_mirror_count` without
  changing the source body or instruction-stream score.

The helper constructors at `0x408000` and `0x408040` only appear in this
constructor in the current exports, so the scratch keeps them as local
`initialize_unknown_*` methods rather than adding speculative names.

2026-06-20 runtime-slot ABI pass:

- Promoted the neutral `RuntimeSlot` method set and the shared constructor
  callback typedef to `tools/match/include/runtime_slot.h`.
- The callback ABI is pointer-returning (`RuntimeSlot* (RuntimeSlot::*)()`),
  matching the exact `noop_runtime_slot_constructor` body while keeping
  `initialize_array_with_constructor` itself source-spelled as a void helper.
- Rechecked this scratch plus the three RuntimeSlot anchors. The anchors stayed
  exact, this scratch remained 80.40%, and the `RuntimeSlot` ABI-conflict row
  disappeared from `uv run snail match types --paths`.

2026-06-20 runtime no-op AI split:

- `RuntimeSlot` now also declares the empty `noop_runtime_ai()` callback used by
  embedded runtime slots in `build_subgame_level`, `initialize_subgame`, and
  `initialize_subgoldy`.
- Those three callsites stayed byte-stable at their pinned focused scores, the
  exact `noop_runtime_ai`, `noop_runtime_slot_constructor`,
  `initialize_array_with_constructor`, and
  `initialize_runtime_pools_and_path_template_bank` anchors stayed exact, and
  `construct_game_runtime` stayed 80.40%.
- `RuntimeCallback` is no longer a cross-scratch ABI-conflict name; the
  remaining local use in `run_frame_update` is the frame-loop virtual `update()`
  row, not this empty runtime-slot callback.
