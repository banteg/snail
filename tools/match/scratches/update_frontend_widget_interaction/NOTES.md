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
