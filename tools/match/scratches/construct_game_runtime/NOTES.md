# construct_game_runtime reconstruction notes

`construct_game_runtime` allocates the root game object, runs the embedded
manager constructors, installs the known callback tables, publishes
`g_game_base`, and reports constructor counters.

The printed `Size of cRPathManager` value is now sourced from the recovered
one-byte `PathManager` type rather than a literal. Symbol-rich iOS builds name
its sole known member `NameCode(char*)`; the size and generated constructor
report remain unchanged.

The same ledger now sources its `cRSubLoc` and `cRSubRow` totals from the
recovered owner types. It reports `0x20d000` for 3200 rows of eight 0x54-byte
`SubLoc` cells and `0xbea00` for 3200 0xf4-byte `SubRow` records; the later
single-object `cRSubLoc` report remains 0x54.

The counter at `0x4dfadc` is now named `g_sub_loc_count`, following the native
`LocCount=%i Memory=%i` report and its `count * sizeof(SubLoc)` calculation.
The exact constructor wrapper at `0x4088c0` increments it once for every cell;
it is not the shared cRBod constructor count printed on the preceding line.

Current focused result after splitting the two adjacent helpers into their own
manifest functions:

- match: 88.89%
- target/candidate instructions: 268 / 299
- prefix: 2 / 268
- masked operands: 119 clean, 1 unresolved, 0 mismatched

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

The `0x408000` composite is now closed as the `GamePlayer`/Windows `cRPlayer`
constructor helper: it initializes consecutive
0x1f8-byte records at root `+0x124/+0x31c`, constructs the owned camera
subobject at player `+0xa0`, and installs the callback whose first entry is the
exact `update_frontend_state_machine` (`cRPlayer::AI()`). The constructor loop
therefore uses a typed `GamePlayer*` increment instead of raw `RuntimeSlot`
stride arithmetic.

The 0x408040 helper is independently mapped as
`initialize_noop_renderable_bod`: its three root uses construct the embedded
`RenderCamera` at `Overlay +0x80`, and its installed callback slot at 0x4972b0
points to `noop_runtime_ai`. Splitting both helpers out of this manifest extent
keeps `construct_game_runtime` focused on the actual cRGame constructor body.

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

2026-07-11 root allocation and exception-shape pass:

- The size ledger and `operator new(0x12e6ff4)` call now close the canonical
  `GameRoot` extent. `HighScoreScreen` ends at root `+0x12e6f20`; the owned
  `TipManager` begins at `+0x12e6f58`, spans `0x98`, and leaves only the final
  four bytes unresolved.
- `TipManager` now inherits the constructed `BodBase +0x00..+0x37` instead of
  treating it as padding. Its six lifecycle scratches remain byte-stable,
  including five proof-grade helpers and the pinned `initialize_tip` body.
- The root allocation is source-spelled as a real `new` expression under the
  target-specific `/GX` profile. This recovers the native C++ EH prologue,
  allocation state slot, null branch, and operator-delete cleanup path. A raw
  allocation class is deliberate: directly constructing the promoted
  `GameRoot` view caused synthetic no-op constructors from reverse-engineered
  helper types to run before the single native constructor body.
- Focused Wibo improves from `87.93%`, `287/268`, prefix `0/268`, to `88.89%`,
  `299/268`, prefix `2/268`. The one unresolved masked operand is the
  compiler-local `$L4917` EH-handler thunk corresponding structurally to target
  `0x496a7b`; it is left unresolved because the matcher does not content-audit
  cross-COMDAT local handlers.
- The remaining leading delta is the debug reporter's cdecl cleanup cadence:
  native batches eight two-argument calls into each `add esp, 0x40`, while the
  isolated `/GX` scratch restores each opaque call immediately. C linkage,
  `throw()`, `__declspec(nothrow)`, and one comma expression were neutral or
  regressive and were rejected. No manual stack adjustment was introduced.

## 2026-07-11 root overlay ownership

- The three repeated constructor islands at root `+0x67c`, `+0x7c8`, and
  `+0x914` are now typed as consecutive `0x14c`-byte `Overlay` objects.
- Each island constructs its inherited `RenderableBod`, constructs the owned
  `RenderCamera` at `+0x80`, and installs the overlay callback table. Startup
  later lends those camera subobjects to viewport slots 0, 2, and 3.
- The typed constructor spelling is byte-neutral: focused Wibo remains
  88.89%, 299/268 candidate/target instructions, prefix 2/268, with 119 clean
  operands and only the compiler-local EH-handler relocation unresolved.

## 2026-07-11 game-input inheritance closure

- The two 0x70-byte records at root `+0x44` are now typed as `GameInput`
  objects inheriting the 0x38-byte `BodBase` and owning the trailing 0x38-byte
  `InputState` at `+0x38`.
- The one-entry table installed by their constructor at `0x4972f0` contains
  `update_game_input` (`cRGameInput::AI()`) and has no other code owner, so it
  is renamed `g_game_input_callback_table` rather than left generic.
- The typed loop preserves the native two-record stride and remains an honest
  constructor-shape partial; no local-label or stack-cleanup fakematch is used.

## 2026-07-11 root manager inheritance closure

- Constructor calls and immediate callback-table stores prove that the owned
  `BorderManager +0xb4c`, `Backdrop +0x4ec10`, and `StarField +0x4f33c` all
  carry the canonical 0x38-byte `BodBase` prefix.
- `BorderManager` and `Backdrop` can express that as ordinary inheritance.
  `StarField` retains its synthetic virtual-prefix declaration because its exact
  initializer performs virtual callback dispatch; adding derived C++
  inheritance there would insert a second vptr, so construction uses a narrow
  `BodBase*` view instead.
- `GameRoot` now exposes the exact 0x6cc-byte backdrop boundary ending at the
  front-end block (`+0x4f2dc`), and the constructor uses the already-proven
  inactive sentinel, viewport array, border pool, backdrop, star field, and tip
  manager fields directly.
- The anonymous renderable at `+0xa60` and BodBase at `+0x4f3c8` remain generic;
  their concrete owners are not established by this pass.

## 2026-07-11 DirectX loader and cached-mesh ownership

- The root interval `+0x48e00..+0x4ec10` is one complete `DirectXLoader`, not
  overlapping `DirectXLoader` and `CachedXMeshBank` views. Its fields close
  the interval exactly: animation-script bytes at `+0x00`, cached-mesh count
  at `+0x04`, 128 `0xbc`-byte cached mesh slots at `+0x08`, and the
  `0x8`-byte duplicate-vertex buffer at `+0x5e08`.
- The constructor now initializes the owned slot array through
  `root->directx_loader.cached_x_mesh_slots`; the neutral `RuntimeSlot`
  callback type remains only at the generic array-constructor ABI boundary.
- `initialize_directx_loader`, `initialize_cached_x_mesh_slot`,
  `load_or_reuse_cached_x_mesh`, and `load_landscape_script_by_name` remain
  exact. This constructor remains `88.89%`, `299/268`, with 119 clean operands
  and only the compiler-local EH handler unresolved.

## 2026-07-11 root cRBod array ownership

- The immediately preceding constructor loop initializes 352 consecutive
  `0x38`-byte `BodBase` records from root `+0x44100`. The product is exactly
  `0x4d00`, so the array ends at the now-proven `DirectXLoader +0x48e00`
  boundary with no padding or overlap.
- `GameRoot::root_bods[0x160]` now owns that interval. Individual indices stay
  deliberately unnamed because the large startup function has not yet mapped
  every authored world object back to an array slot.

## 2026-07-11 intro screen and renderable-bank ownership

- Root `+0x4f400..+0x74618` is the complete `IntroScreenRuntime`. Its `0x18`
  state header is followed by 1024 `IntroLogoRenderable` records and the 32
  logo records consumed by `open_logo`; both banks use the constructor's
  exact `0x90` stride.
- The preceding `BodBase +0x4f3c8` remains a separate root-owned record with an
  unknown concrete role. It is typed without folding it into the intro owner.
- The constructor now addresses both arrays through the shared owner. Its
  focused metrics remain `88.89%`, `299/268`, with 119 clean operands and the
  single compiler-local EH-handler relocation unresolved.

## 2026-07-11 subgame constructor ownership

- The constructor call at root `+0x74618` now targets the owned
  `GameRoot::subgame` directly. Its constructor pass proves the two consecutive
  `SubTracks` extents inside that owner, including the exact second
  boundary at subgame `+0x355b64`.
- This is codegen-neutral: the constructor remains `88.89%`, `299/268`, with
  119 clean operands and only the existing compiler-local EH handler unresolved.
