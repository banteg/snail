# cRBorder::AI @ 0x402820

Current recovery: semantic-complete (`compiler,references` residual). Binary
Ninja types the Windows entry as `void __thiscall(FrontendWidget*)`; the active
BOD dispatcher ignores callback results. Android and iOS independently retain
the same complete member as `cRBorder::AI()` in `Border.o`.

The recovered state machine covers flag snapshots and list teardown, mouse and
shortcut dispatch, delayed actions, tooltip/twinkle updates, text input,
RePosition/Draw, color easing, sound feedback, cursor history, and all three
slider children. Exact sibling methods corroborate its owner and field graph.

Focused VC6 result: **95.83%**, 649/647 candidate/target instructions, prefix
127/647, with 96 clean relocation operands and two candidate-only unaudited
`1.0f`/`0.0f` clamp loads. The remaining differences are bounded initialization,
x87 interpolation, and endpoint-store scheduling, not missing behavior.

The matcher source now uses the authored `AI` method and exact VC6 symbol
`?AI@cRBorder@@QAEXXZ`; `update_frontend_widget_interaction` remains only the
stable scratch and Windows-address identity.

## 2026-09-05 color and slider value ownership probes

Eight `whole-color-blend-and-slider-owners-20260905-mutations.json` variants
compare per-call blend values/references, hot-color references, and separate
hot/cold coefficients, each with local or direct-field slider clamps. The
best local-clamp alternative reaches 93.35%, below the retained 95.83%, and
still has 96 clean plus two unaudited references. Direct-field clamps remove
the two unaudited loads but regress to 77.85-80.12% with prefix 1.

Six `whole-slider-destination-borrows-20260905-mutations.json` variants then
borrow the slider destination at whole-tail, button-local, or publication
scope. Local scalar clamps are neutral at 95.83%, 649/647 instructions,
prefix 127, 96 clean and two unaudited references. Direct published clamps
reach only 80.62%, prefix 1, despite clearing reference debt. No alternative
is retained. The iOS body corroborates field publication before clamping;
the matching source expression and its surrounding allocation remain open.

## 2026-09-05 live flag and slider coupling

Seven combinations test direct flag reads, direct slider publication before
clamping, and reversed hot-color multiplication. The color-only control is
neutral at 95.83%; live flags yield 91.50%; direct slider publication clears
two unaudited constants but falls to 80.62%, or 78.27% with live flags. None
improves the canonical source. These results bound this combination only; they
do not establish compiler exhaustion.

## 2026-09-07 complete slider operations and zero-state handlers

A fresh full diagnostic of the direct-field clamps confirms why clearing the
two unaudited constant loads is insufficient: VC6 introduces a persistent
zero in EBP, saves EBX for the one constant, and reuses that zero through the
early list-removal and input paths. The candidate grows to 653/647 instructions
and falls to 80.62%, prefix 1. The native endpoint stores alone do not establish
a whole-function recovery.

`slider-publication-and-zero-state-dispatch-20260907.json` records twelve
coupled forms: each clamp publication combination with complete empty-flags,
warmup-countdown, or paired switch handlers. All compile. The countdown switch
is neutral for each publication form; the empty-flags switch changes return
sharing and regresses. The best non-identical candidate reaches 95.29%,
648/647 instructions, prefix 127, with one unaudited constant remaining.

`complete-slider-operations-20260907.json` records eight whole button or
slider-tail operations with pointer/reference receivers and local/published
clamps. Each matches the corresponding in-method form's bytes: 95.83% for
local clamps and 80.62% for published clamps. No helper, handler, or canonical
source change is retained. These controls leave the interpolation operands,
constant lifetimes, and native clamp publication open.

## 2026-09-25 structural metric: published less-button clamp

Scored with `--structural`, which ignores eax/ecx/edx rotation.
Baseline: 95.83% normalized, 96.30% structural, 23/25 changed. Retained:
**95.29%** normalized, **96.83%** structural, **20/21** changed, 648/647
instructions, prefix 127, 96 clean references and one unaudited constant
(down from two).

The less-button clamp now publishes directly, as in the iOS body:
`slider_value -= 0.2f; if (slider_value <= 0.1f) slider_value = 0.0f;`. That
region now matches exactly: `fst [0x17c]`, `fcomp 0.1`, then
`mov [0x17c], 0`. This is the 95.29% candidate recorded on 2026-09-07. It was
rejected then on the normalized metric. The structural metric shows that it
removes real work (48 → 41 changed instructions) without adding a register.
A staged local that is stored before the test, and
`if ((slider_value -= 0.2f) <= 0.1f)`, give identical bytes.

The more-button clamp stays local. Any published `slider_value = 1.0f` store
(`+=`, a staged local then store, compound, or if/else) makes VC6 give
`1.0f` to EBX for the whole function and a split zero to EBP. That changes
roughly 20 zero compares and stores (41/47 changed). Removing any single
zero use, such as a `text_effect_target = 0.0f` or the warmup test, does not
undo it. The trigger is the published `1.0f` store, not the number of zero
uses.

The hover colour operand order (`fld t; fmul hot`, eight lanes, 16 changed
instructions) is still open. The following all keep `fld hot; fmul t`:
swapped products and sums, a scratch inline blend helper (reference,
pointer, or `const float&` t, with or without an `inv` local), and
diagnostic-only forms. The diagnostics were an early reference to the hot
colour, `&hover_blend_current` escaping, and a `{target, current}` view of
`hover_blend_*`. One diagnostic did flip it: taking `&hot_fill_color.r`
loads `t` first against `[reg]`. This suggests VC6 picks the loaded operand
from its addressing form, but no plausible source form reproduces it. The
EDI/EBP constant-load order at +127 is also unchanged by the `flags` versus
`widget_flags` test spellings.
