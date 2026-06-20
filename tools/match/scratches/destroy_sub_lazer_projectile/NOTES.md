# destroy_sub_lazer_projectile

First relationship scratch for `TrackRowCell::destroy_sub_lazer_projectile()`
at `0x439bc0`.

Current match: 91.19% (`130/131` candidate/target instructions), 87-instruction
exact prefix, `17` masked operands ok, no unresolved or mismatched operands.

Recovered behavior:

- the receiver is the full `TrackRowCell`/fringe runtime object, not a
  `SubLazerSlot`; the first `0x10` bytes are the shared `BodNode` prefix;
- tile ids `0x1d` and `0x1e` may clear the row-color BOD record at
  `game+0x6410e0 + row*0xf4`, gated by the row record's dirty bit `0x08`;
  this is the shared `TrackAttachmentRuntimeRow` record viewed from the outer
  game base, so the scratch keeps the native outer cursor and typed offset
  accesses instead of folding `0x6410e0` into the row pointer;
- the cell's own BOD node is removed when active;
- the four `TrackRowCell::fringe_*` pointers are scanned and any active fringe
  BOD is unlinked back into the shared free list.

This helper is called by the wall-2 emitter update path and by
`SubgameRuntime::remove_subgame_bods()`, so it is the smaller source-of-truth target
before writing the larger subgame teardown pool scratch.

Residual: the four-fringe-pointer loop is semantically aligned, but VC6 keeps
the active-flag precheck value live in the candidate instead of clobbering and
reloading it after forming the shared `BodList` anchor as native does. Leave
that as a source-shape residual unless another caller/header gives a cleaner
fringe-array spelling.

## 2026-06-18 BN/IDA name sync

Promoted the analysis-side `TrackRowCell` prefix to `BodNode`, renamed
`+0x40` to `lane_and_flags`, and synced the four directional fringe pointers as
`fringe_front/right/left/back`. BN now resolves the cell unlink block through
`cell->bod.*` and starts the final four-pointer scan at `cell->fringe_front`.
The IDA snapshot was corrected away from the stale `SubLazerSlot` wording.

The same BN type sync does help `wall2_emitter_maybe_fire_sub_lazer`, but that
export was intentionally not kept in this slice because BN reused the
`lane_and_flags` field name for a generic condition/temp value across the
function, making the artifact less honest than the previous `result` spelling.

## 2026-06-19 fringe reload audit

Focused Wibo still reports 91.19%, 130/131 candidate/target instructions, an
87-instruction exact prefix, and 17 clean masked operands.

The remaining fringe-loop residual is a real source-shape/register-allocation
tradeoff:

- a fringe-only remove macro that names `g_game_base` through an intermediate
  `list_base` is codegen-neutral; VC6 still keeps the active precheck flags
  live and emits `mov edx, [g_game_base]; add edx, 0x5a8` without reloading
  `node->list_flags`;
- passing `fringe[i]` directly to the remove macro, or reloading it into a
  second local inside the active branch, does recover the native inner
  `mov ecx, [g_game_base]; lea edx, [ecx+0x5a8]; mov ecx, [eax+4]` sequence,
  but it regresses the whole function to 71.76% by changing saved-register
  ownership: the prologue drops `push ebx`, the unlink mask moves to `edi`, and
  the final fringe clear becomes a byte-lane `and ch, 0xfd` store instead of
  native `and dword [eax+4], ebx`.

Keep the local `FringeObject* object` loop as the pinned shape. It preserves the
native prologue, loop counter, and dword unlink mask; the lone missing reload is
less damaging than the expression-form register cascade.

## 2026-06-20 larger fringe-tail audit

Focused Wibo still reports 91.19%, 130/131 candidate/target instructions, an
87-instruction exact prefix, and 17 clean masked operands. Viewing the fringe
object as a `BodNode*` for both the active precheck and remover is codegen-neutral
and leaves the same CSE of the precheck flags. A fringe-tail-only remover that
reloads flags through a raw `node + 4` word after materializing
`g_game_base + 0x5a8` also compiles back to the same candidate, so the typed
macro spelling is not the blocker by itself. Passing `fringe[i]` as the remover
expression still recovers the native inner reload but regresses to 71.76% by
dropping `push ebx`, moving the unlink mask into `edi`, and ending with a
byte-lane `and ch, 0xfd` update. Rewriting the final scan as an explicit
`do/while` cursor loop is codegen-neutral. Keep the local `object` loop and the
shared typed remover; the remaining residual is the CSE/register-allocation
tradeoff, not a missing `FringeObject` layout field.
