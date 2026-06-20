# initialize_track_render_cache_manager @ 0x433060

Initial shape:

- Seeds five render-cache capacity pairs.
- Stores the live track-render grid pointer at `game+0x74618`.
- Initializes the 143 x 5 cache BOD slots by allocating an `Object` for each
  slot, attaching it through `set_bod_object`, clearing the object geometry
  counters, and allocating per-object D3D/index/texture-group resources.
- The fifth slot in each row uses `blend_mode = 5`, matching the skirt/cache
  lane used by `update_track_render_cache_rows`.
- Allocates the five shared GDX cache vertex/index buffers from the recovered
  capacity arrays.

Layout correction:

- The existing header had `track_render_grid` at `+0x28`. The native
  constructor proves the fixed layout is `unknown_00`, capacity arrays at
  `+0x04/+0x18`, shared vertex/index buffers at `+0x2c/+0x40`, and
  `track_render_grid` at `+0x54`, with cache slots still starting at `+0x58`.
- The slot initialization loop uses a manager-relative cursor view: native
  computes `manager + slot_index * 0x3c`, then accesses the BOD at `+0x58` and
  the attached object pointer at `+0x7c`.

Status:

- 2026-06-18: 91.80%, 122/122 instructions, masked operands clean. Remaining
  residuals were register/scheduling only: capacity seed register choice, a
  commuted slot-index `lea`, and a delayed shared-vertex-buffer store before
  the index-buffer allocation setup.
- 2026-06-18 follow-up: spelling the shared GDX vertex allocation through an
  explicit `vertex_buffer` temporary recovers the native store-before-index
  setup order. Keeping the index element count as a separate temporary gives
  the best current shape: 93.44%, 122/122 instructions, 18 clean masked
  operands. Remaining residuals are the capacity seed register/scheduling
  block, the commuted slot-index `lea`, and the tail byte-count register choice
  (`eax` plus `lea edx,[eax+eax]` versus native `edx` plus `shl edx,1`).
- 2026-06-20 larger near-proof pass: spelling the slot cursor as
  `this + slot_base * 0x3c + i * 0x3c` to mirror the IDA expression
  (`60 * row_base + 60 * i`) is codegen-neutral at 93.44%. VC6 still emits the
  same commuted `lea eax, [edi+edx]`, so the compact `(slot_base + i) * 0x3c`
  source remains retained.
