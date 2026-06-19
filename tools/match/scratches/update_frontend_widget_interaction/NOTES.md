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
