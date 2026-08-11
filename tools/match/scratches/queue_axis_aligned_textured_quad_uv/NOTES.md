# queue_axis_aligned_textured_quad_uv

Initial scratch for the explicit-UV 2D textured quad queue helper at
`0x44a9b0`.

Wibo result: 76.12%, 66 target instructions versus 68 candidate instructions.
The helper matches the non-UV queue shape; remaining residual is the same
shared-zero epilogue distance, color alpha/count store scheduling, and stack
argument register choice for the UV/blend-mode/rotation stores.

Recovered relationships:

- The active byte at `data_4b7236` is the broader render queue gate, not a
  font-only flag.
- Shares the same `cFontPrintBuffer` layout and validation gates as
  `queue_axis_aligned_textured_quad`.
- Stores caller-provided UV bounds at `+0x5c..+0x68`.
- Used by front-end widgets, progress bars, damage gauge, galaxy display, and
  gameplay HUD quads.

2026-06-20 render-queue chunk: the same missing-final-return probe used on the
default-UV and corner queue helpers cannot be kept here either. It likely models
native's shared incidental skip return, but under Wibo the MSVC warning path
aborts on a missing `lstrcpynA` import before producing a comparable object.
Keep the runnable explicit `return 0` until a real source spelling avoids the
extra epilogue without entering the warning path.

2026-06-21 color-copy split retry: replacing `entry->color = *color` with
integer-lane copies, including variants that write RGB, update
`g_font_queue_count`, then write alpha, regresses this helper to the mid-40%
range and adds/moves masked queue-offset mismatches. The aggregate `tColour`
copy remains the only source-plausible shape that preserves the saved-register
copy sequence.

2026-06-21 count-store sweep: moving the `g_font_queue_count` publish after the
entry field stores improves focused Wibo from 76.12% to 92.54%, with 68
candidate instructions versus 66 target instructions and all 19 masked operands
clean. Intermediate placements monotonically recovered the queue-field offsets;
the retained after-`rotation` spelling removes the previous masked offset
mismatches while preserving the aggregate color copy. The residual is now only
the moved count store plus the known shared zero-return epilogue.

2026-06-21 granular count-store retry: placements before color and after each
field through `blend_mode` were retested. Scores rise monotonically from 59.09%
to 89.55% as the store moves later, but only the retained after-`rotation`
placement
reaches 92.54% and keeps all 19 masked operands clean. Native's earlier count
publish remains a scheduling tradeoff; moving it back reintroduces field-offset
mismatches.

2026-06-21 signature/tail retry: a `void` helper removes the explicit zero
return in source, but it also changes the saved-register set and drops the
focused match to 24.43%. Removing only the success `return offset` keeps the
`int` signature but falls to 67.67% and dirties the queue-offset audit. Keep the
current runnable `int` source with the explicit skip return despite the native
incidental return register.

2026-07-09 family sync: count-before-rotation (axis-aligned non-UV order) drops
to 89.55%. Early-out rewrite is neutral at 92.54%. Keep rotation before count.

## 2026-07-14 font queue ownership closure

Android's `G0RenderFont(..., int, float)` signature and the exact queued-quad
forwarder independently resolve this producer's final pair as integer
`blend_mode` followed by float `rotation`. Binary Ninja and IDA now emit those
typed queue fields directly. The source remains at the honest `92.54%`
frontier (`68/66`, all 19 masked operands clean); the known count-store and
return-register scheduling differences remain documented rather than shaped.

## 2026-07-23 embedded color owner

The register previously rendered as `float* edx_4` is exactly
`&g_font_queue[index].color`. The canonical BN replay now records it as
`tColour* entry_color`, yielding all four RGBA fields and matching IDA's
independent `p_color` view. No source-shape probe was retained: focused Wibo
stays at 92.54% (`68/66`, prefix `2/66`, 19 clean operands).

## 2026-07-24 partial return contract

This producer shares the family's authored partial result: a successful append
returns the byte offset, overflow returns the reporter result, and inactive or
zero-size skips do not define `eax`. Its 35 live Binary Ninja callsites
normally discard the result, while `draw_split_backdrop` forwards the final
append result from its tail.

A local C4715 suppression allows that native fallthrough under the unchanged
VC6 `/O2 /G5 /W3` profile. Removing the scratch-only `return 0` raises the
focused result from 92.54% (`68/66`) to 98.48% with exact `66/66` instruction
parity, a 42-instruction prefix, and all 19 operands clean. Only the
semantically independent `g_font_queue_count` store moves from the middle of
the aggregate color copy to the completed-entry tail; natural allocation and
post-copy placements regress and are not retained.

## 2026-07-25 authored overload provenance

Both symbol-rich iOS phone builds and Android retain the short overload as
`OSDPrintUV(int, float, float, float, float, int, tColour, float, float,`
` float, float, int, float)` in `Font.cpp`/`Font.o`. The mobile bodies append
the same rectangle, UV, integer blend-mode, and float rotation fields at a
`0x84` stride. The Windows scratch remains 98.48%; the evidence clarifies the
owner and ABI rather than altering scheduling.

## 2026-07-26 platform return ABI audit

Although both mobile bodies declare this `OSDPrintUV` overload void, the
Windows append path exposes its byte offset and `draw_split_backdrop` forwards
the second append's EAX. Projecting the mobile return type changes VC6's queue
address schedule and drops focused matching from 98.48% to 68.18%.

Windows therefore keeps the evidence-backed integer result and mobile keeps
its void API. No dummy dependency or forced return was introduced.

## 2026-07-29 bounded queue-publication audit

The earlier 143-combination count/color/publication audit is now backed by
three compact recorded sweeps that isolate each axis: 24 unique variants,
twelve byte-identical and twelve regressive. All eleven alternate publication
positions are worse, every semantics-preserving count carrier is neutral at
98.48%, 66/66, prefix 42, and embedded-color pointer/reference variants do not
move the global store without disturbing the aggregate copy.

There is one exact residual: native publishes `g_font_queue_count` immediately
before the aggregate alpha store, while the candidate emits that same store
after the final rotation field at the function tail. All 20 masked operands
remain clean. The source already has the cross-port-proved `Font.o` owner and
no missing file-local callee or data definition, so same-TU placement cannot
explain the independent global-store scheduling. No barrier or TU cluster is
introduced.

## 2026-08-11 VC6 profile boundary

Recovery triage surfaced both `Font.o` quad appenders among the closest
unclassified matches. The explicit-UV source was therefore replayed under all
preserved VC6 game-code profiles after the 24 ordinary publication/color-owner
variants above had failed to move the count store.

`msvc6.0`, canonical `msvc6.5`, and `msvc6.6` all retain the 98.48% result,
66/66 instructions, 42-instruction prefix, and first mismatch at candidate
offset `0x95`. `msvc6.5pp` instead regresses to 93.94%, keeps 66/66
instructions, shortens the prefix to 13, and first differs at candidate offset
`0x35`. The three noncanonical results are recorded in `experiments.jsonl`.

Processor Pack code generation is therefore positively excluded for this
authored `Font.o` helper, while the other preserved VC6 builds share the same
independent queue-count publication schedule. Cross-port ownership, full field
layout, return behavior, exact instruction count, and all 20 references are
already closed, so this scratch is classified `RECOVERY=semantic-complete`
with `RESIDUAL=compiler`.
