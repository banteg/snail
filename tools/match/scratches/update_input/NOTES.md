# update_input

Partial `InputState` edge updater at `0x40aa80`.

The function folds `current_buttons` and `previous_buttons` into per-frame
`pressed_buttons` and `released_buttons`, stores `~current_buttons` at
`inverse_current_buttons`, and clears `current_buttons` for the next input
sampling pass.

Current Wibo result is 37.84%. Computing `changed`, `pressed`, `inverse`, and
`released` before any member stores gives VC6 the native saved-`edi` lifetime
and removes one instruction of length debt. The first residual remains the same
early allocation split: native keeps `changed` in `edx` before saving `esi`,
while this source shape still saves `esi` first and uses it for `changed`.

2026-06-20 larger-chunk audit: rewriting the body in direct IDA statement order
(`previous`, `pressed`, then inverse/released) regresses to 34.29% by removing
the saved `edi` lifetime and shrinking the candidate to 16 instructions.
Adding a `register` hint to `changed` is codegen-neutral at 37.84% and does not
move the xor before `push esi`. Keep the precomputed locals until a real source
idiom explains native's early `edx` allocation.

2026-06-20 larger residual audit: staging `changed`, `pressed`, `inverse`, and
`released` as mutable locals is codegen-neutral at 37.84%; VC6 still saves
`esi` before loading `previous_buttons`. Snapshotting `previous_buttons` before
`current_buttons` and typing the bit-mask locals as `unsigned int` are also
neutral. These probes preserve the edge semantics but do not explain native's
early `edx = previous ^ current` allocation, so the clearer precomputed-local
source remains retained.
