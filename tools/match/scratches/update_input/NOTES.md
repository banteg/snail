# update_input

Partial `InputState` edge updater at `0x40aa80`.

The function folds `current_buttons` and `previous_buttons` into per-frame
`pressed_buttons` and `released_buttons`, stores `~current_buttons` at
`inverse_current_buttons`, and clears `current_buttons` for the next input
sampling pass.

Current Wibo result is 51.43%. Storing `previous_buttons` and
`pressed_buttons` before mutating the local result into the inverse recovers the
native opening allocation (`current` in `eax`, `changed` in `edx`, then save
`esi`) and moves the scratch out of early progress. The remaining residual is
the tail lifetime: native keeps the original `eax`, saves `edi`, materializes
the inverse in `esi`, and writes `released_buttons` through `edi`; this source
shrinks the tail and reloads `previous_buttons` for the return value.

2026-06-20 larger-chunk audit: rewriting the body in one direct IDA statement order
(`previous`, `pressed`, then inverse/released) regresses to 34.29% by removing
the saved `edi` lifetime and shrinking the candidate to 16 instructions.
Adding a `register` hint to `changed` is codegen-neutral at 37.84% and does not
move the xor before `push esi`.

2026-06-20 larger residual audit: staging `changed`, `pressed`, `inverse`, and
`released` as mutable locals is codegen-neutral at 37.84%; VC6 still saves
`esi` before loading `previous_buttons`. Snapshotting `previous_buttons` before
`current_buttons` and typing the bit-mask locals as `unsigned int` are also
neutral. These probes preserve the edge semantics but do not explain native's
early `edx = previous ^ current` allocation.

2026-06-20 shape update: the direct store/invert order verifies at 51.43% with
5/19 native prefix and no masked operands. A local `void update_input()` probe
reaches 52.94% by avoiding the explicit reload return, but the shared
`InputState` header and `update_game_input` owner bridge still model the return
value, so do not apply a leaf-only signature split without reconciling that
callsite.

2026-06-21 bridge-signature reconciliation: `update_game_input` ignores the
edge updater's source-level return and just falls through with the incidental
`eax` left by the call. Promoting `InputState::update_input()` to `void`
coherently with the owner bridge exact-matches `update_game_input` and keeps the
leaf at the known 52.94% shape. The remaining leaf residual is still the native
`edi` lifetime for `released_buttons`, not evidence for a real return value.
