# `layout_frontend_widget` notes

- Scratch-local `FrontendWidget` names only the fields touched by this layout
  pass. Shared `frontend_widget.h` has overlapping but not yet exact layout
  names for all of these offsets.
- The shadow flag passed into `layout_and_queue_wrapped_font_text` is
  `(g_render_flags >> 8) & 1`, matching the native load from `data_4df934`.
- 2026-06-20 layout-tail pass: focused Wibo improves from 78.06% to 86.44%,
  with 177/177 instructions and the same 20 clean masked operands. Moving the
  `layout_top_bits` read after the `widget_flags` reload recovers the native
  post-text-layout schedule (`texture_hit_x` store, flags reload, then
  `texture_hit_y` store). Computing `result = flags & 0x100000` while driving
  the slider-hit rectangle from the preserved `flags` value also restores the
  native separate `test eax, eax` before recursive child layout. Rejected
  probes: reordering the authored-frame locals regressed to 77.97%, naming all
  wrapped-text call arguments overgrew the frame to 0x1c and regressed to
  74.73%, and lane-view/output-pointer locals were codegen-neutral. Remaining
  residuals are authored-frame load scheduling, wrapped-text argument register
  assignment, and the recursive self-call target spelling (`call L0` versus
  candidate relocation), with no unresolved operands.
- 2026-06-20 larger-chunk audit: moving only the `authored_width` declaration
  after the layout pointer setup is codegen-neutral at 86.44% and leaves the
  same width-load hoist. Staging only `layout_mode`, `layout_center_x`, and
  `idle_text_color` before the wrapped-text call regresses to 72.11% by growing
  the frame to 0x0c. Loading `layout_top_bits` before storing
  `texture_hit_x` regresses to 78.53% by moving the preserved flags owner from
  `ecx` to `edx` and disturbing the recursive tail. Keep the current
  post-call read/store schedule.
- 2026-06-21 authored-frame pass: delaying the frame-width read until after the
  authored-left store and reading that lane through a narrow volatile view
  improves focused Wibo from 86.44% to 97.18%, keeps 177/177 instructions, and
  keeps all 20 masked operands clean. Reusing `result` for the authored-height
  temporary restores the wrapped-text call argument setup. Forcing the
  authored-left load volatile makes the authored-frame branch exact through
  instruction 32, but regresses the full function to 88.14% by disturbing the
  wrapped-text call registers. Pointer/ref spellings for the retained width and
  height lanes are codegen-neutral at 97.18%; the remaining local residual is
  the width load/store placement plus the known recursive self-call relocation
  spelling.
- 2026-06-21 width/top scheduling follow-up: moving the authored width load and
  layout-width store toward the addressed native order regresses to
  96.05%-96.61% by shortening the exact prefix to 21 instructions. Moving the
  `layout_top_bits` load before `texture_hit_x` store is worse (89.27% on the
  retained branch shape), while placing it between the X store and flags reload
  is codegen-neutral at 97.18%. The current volatile-width ordering remains the
  best whole-function tradeoff despite the local diff.
- 2026-07-12 caller agreement: `update_frontend_widget_interaction` now passes
  this same `+0x238/+0x23c/+0x248/+0x24c` layout block to the wrapped-text
  helper. The later `+0x240/+0x244` pair remains the derived/clamped hit-test
  position owned by this member, closing the previously conflicting caller
  view.

2026-07-13 no-fakematch audit: the authored-width volatile read was a register
schedule barrier and is removed. The plain width-bit copy retains the recovered
frontend layout block and exact instruction-count parity at an honest 87.57%,
177/177, prefix 23, with all 20 operands clean. The remaining drift is argument
and aggregate-copy allocation, not field ownership.

## 2026-07-14 slider layout ownership

The four slider hit bounds now use the shared `FrontendWidget` fields at
`+0x184..+0x190`, and the recursive tail follows the owned
`slider_more_widget`, `slider_less_widget`, and `slider_value_widget` handles
at `+0x71c/+0x718/+0x720`. This removes the last raw-offset writes and generic
child aliases from the layout pass while preserving the honest 87.57%,
177/177 instruction result, 23-instruction prefix, and all 20 clean operands.

## 2026-07-14 authored void contract

Android preserves this member as `cRBorder::RePosition()` and exits without a
stable result; all 24 Windows callsites discard EAX. Removing the synthetic
scalar return changes only register allocation: the honest focused result is
84.18%, 177/177 instructions, prefix 21, with all 20 operands clean. The lower
sequence score is retained because the shared API now models real ownership
instead of constraining EAX for the matcher.

## 2026-07-15 persisted RePosition receiver

Both mobile symbol tables retain this member as `cRBorder::RePosition()`
(`0x3892c` on iOS and `0x52678` on Android). Binary Ninja's transactional
prototype replay now saves and independently reads back
`void __thiscall(FrontendWidget*)`, so this member moves out of the deferred
set. IDA uses the same void receiver contract. A standalone `bn proto set
--preview` was not accepted as evidence because it left the unsaved preview
type active in the live session despite reporting a revert; the repository
sync instead reported `snapshot_saved: true` and a fresh `bn proto get`
confirmed the durable type. The source scratch remains the honest 84.18%,
177/177-instruction transcription with all 20 audited operands clean; no EAX
shaping was reintroduced.

## 2026-07-16 authored rectangle and screen-clamp flags

Android `cRBorder::RePosition()` independently preserves both Windows
branches: `0x00010000` copies the four authored rectangle lanes into the live
layout rectangle, while `0x20000000` skips the 640-by-480 clamp. The Windows
galaxy bounds frame supplies both bits and immediately authors all four frame
lanes; Android high-score rows supply the latter while placing widgets at
`y = -273.0f`. These closed producer/consumer roles are now
`USE_AUTHORED_RECT` and `ALLOW_OFFSCREEN`. The focused source remains
codegen-equivalent; no still-unknown style bit was named.

## 2026-07-24 font-shadow flag vocabulary

The forwarded config bit is `RUNTIME_RENDER_FONT_SHADOW`, not a wave enable.
This member invokes the wrapper in measure-only mode, so the byte is not
queued here; the per-frame interaction member supplies the same bit on the
actual queueing path. The vocabulary change preserves the honest 84.18%,
177/177-instruction result and all 20 clean operands.

## 2026-07-27 mobile-authored rectangle copies

Android and iOS both retain the `USE_AUTHORED_RECT` branch as four direct
member copies from the authored rectangle into the live layout rectangle.
Replacing the scratch's older integer-bit temporaries with those natural typed
copies restores the Windows VC6 load/store schedule and raises the focused
match from 84.18% to 99.44%, still at 177/177 instructions with all 20 masked
operands clean.

The only residual is one post-layout top-coordinate load moving across the
adjacent texture-hit X store. Hoisting that read in the source disturbed later
register ownership and regressed the whole function to 93.22%, so the clear
member-copy transcription is retained without a scheduling barrier.

## 2026-07-29 bounded hit-field borrow audit

Eight input/output pointer and reference variants were tested for the two
texture-hit stores. Seven are byte-identical to the 99.44%, 177/177 baseline;
snapshotting the top value before the X store does recover the local order but
regresses the full function to 93.22%.

The isolated native sequence loads `[edi]` into `edx`, stores the already
loaded X bits to `[esi+0x240]`, then reloads flags. The candidate performs the
X store and flag reload before that same `[edi]` top load; all 20 references
remain clean. The values are ordinary fields surrounding one already-matched
out-of-line layout call, so co-compiling neighboring functions supplies no
missing definition or lifetime. No TU or artificial dependency is retained.

## 2026-07-29 bounded hit-join lifetime search

Three recorded mutation sweeps now bound the remaining join schedule with 121
source variants. Forty-seven complete source combinations compile: three
pointer/reference or direct typed-copy spellings are byte-identical to the
99.44% baseline and the other 44 regress. The remaining 74 variants are
deliberately incomplete cross-site declaration/carrier combinations and fail
to compile; no improving, tradeoff, or exact result was found.

`hit-carrier-mutations.json` exhausts all 63 combinations of hoisting the top
snapshot and reusing the pre-existing `result` flag carrier suggested by the
mobile ports. The fully consistent carrier form falls to 89.27%.
`hit-publication-mutations.json` tests 24 complete declaration, integer/float,
reference, direct-copy, signedness, and load-order forms. Every form that
actually moves the top load early collapses to the same 93.22% EAX-owner
schedule or worse. `join-lifetime-mutations.json` moves the snapshot
declarations before the layout branch in all six complete pairings; each still
produces that same 93.22% schedule.

The hoisted disassembly explains the whole regression. It loads the top bits
into EAX rather than native EDX, then swaps the two clamp temporaries and all
three recursive-child publication temporaries later in the function. Delaying
the load gives VC6 the native EDX owner and leaves only the single adjacent
load/store transposition. The retained source therefore remains the honest
99.44%, 177/177, 20-reference transcription. Further work should start from
new ownership or control-flow evidence rather than another spelling
permutation.
