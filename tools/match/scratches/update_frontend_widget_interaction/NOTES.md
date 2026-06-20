# update_frontend_widget_interaction @ 0x402820

Starter scratch for the per-frame front-end widget state machine.

Models flag snapshot/teardown, hover hit testing, shortcut dispatch, delayed
click flags, easing, text-input update, tooltip/twinkle refresh, text layout,
draw, mouse settle, and slider arrow updates. Binary Ninja only exports a stub
for this function, so the scratch follows the IDA export and adjacent exact
helpers.

Expected residuals:
- list removal is source-shaped but not instruction-scheduled;
- several flag names remain raw until more callsites are pinned;
- slider/text color propagation is semantic but not exact.

2026-06-20 type consolidation: the method-only `TwinkleManager` declaration was
replaced with `include/twinkle_manager.h`, validated by exact
`update_twinkle_manager`. Focused rerun preserves the prior 46.85% result,
544 candidate instructions versus 647 target instructions, 55 masked operands
OK, and the same five masked call mismatches.

2026-06-20 frontend type pass: this scratch now uses the shared
`TooltipState` subobject declaration and the exact `int` return ABI for the
highlight/layout helpers. The focused matcher remains unchanged at `46.85%`,
`544/647` candidate/target instructions, `15/647` prefix, and the same
`55 ok / 5 mismatch` masked audit.

2026-06-20 shared frontend header pass: the local method-only
`FrontendWidget` declaration was replaced with `include/frontend_widget.h`.
Focused matcher evidence stayed unchanged at `46.85%`, `544/647`
candidate/target instructions, `15/647` prefix, and the same `55 ok /
5 mismatch` masked audit.
