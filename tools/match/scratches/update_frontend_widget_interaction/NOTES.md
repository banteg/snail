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
- slider/text color propagation now follows the native slot relationships but
  still has local scheduling drift.

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

2026-06-20 slider layout pass: the focused matcher improved from `46.85%` to
`48.36%`, with the candidate still `544/647` instructions but the prefix
advancing from `15/647` to `42/647`. The slider overlay hit rectangle is
layout-relative and lives in `+0x184..+0x190`; the late slider child pointers
are `less +0x718`, `more +0x71c`, and `value +0x720`; the authored-frame
refresh copies `+0x4c/+0x50/+0x54/+0x58` back into layout
`+0x238/+0x23c/+0x248/+0x24c`; and the value child color tail copies
`+0x1dc` to `+0x1dc`. Making `unlink_frontend_widget` `__inline` regressed to
`45.53%`, and rewriting the internal text layout call to the apparent
`+0x6ec/+0x6f0` font fields regressed to `48.32%`, so both probes were
rejected.

2026-06-20 current-color layout pass: focused matcher improves from `48.36%`
to `52.85%`, with `579/647` candidate/target instructions, prefix `42/647`,
and masked operands `65 ok / 4 mismatch`. The zero-flags teardown is inlined
because the target has the first intrusive-list removal in the main function,
and the diagnostic string is the shared `"List remove NEXTBOD"`. Constructor
and update dumps agree on the color slots: current fill `+0x1ac`, idle fill
`+0x1bc`, hot fill `+0x1cc`, current text `+0x1dc`, idle text `+0x1ec`, and
hot text `+0x1fc`; the internal wrapped-text call also uses the real font
fields `+0x6ec/+0x6f0`. Rejected probes: expanding all teardown paths raised
masked operands to `70 ok / 2 mismatch` but regressed to `50.19%` by forcing
an extra saved `ebx`; a macro-based teardown expansion similarly regressed to
`48.79%` through register-pressure artifacts.

2026-07-11 border owner pass: the hover test now calls the shared
`FrontendWidget::border_mouse_test()` method directly, matching the exact iOS
`cRBorder::MouseTest()` owner recovered by the adjacent scratch. This is an ABI
clarification only: the focused result remains `52.85%`, `579/647`
candidate/target instructions, prefix `42/647`, and `65 ok / 4 mismatch`.

2026-07-12 border-manager tail and ABI recovery: the global interaction gate
at root `+0x440ec` is `BorderManager::delayed_widget_active`, not unowned root
padding. More importantly, all three delayed-click sites now call the proven
`BorderManager::queue_frontend_widget_flag_after_delay` `thiscall` instead of
a false free three-argument helper. This removes seven candidate instructions,
raises the focused match from `52.85%` to `55.29%` (`572/647`), and improves
the masked audit from `65 ok / 4 mismatch` to `70 ok / 3 mismatch` while
retaining the 42-instruction prefix.

2026-07-12 sound-manager ABI recovery: the three UI feedback calls use the
global `g_sound_effect_manager` receiver, agreeing with the exact
`register_parcel_delivery` callsites and iOS `cRSound`/`gRSound` ownership.
Replacing the false free cdecl declaration preserves `572/647` instructions,
raises the focused result from `55.29%` to `55.62%`, and improves the masked
audit from `70 ok / 3 mismatch` to `71 ok / 2 mismatch`. Both remaining
mismatches are now earlier intrusive-list teardown scheduling, not audio ABI.

2026-07-12 intrusive-list owner recovery: all three widget teardown paths now
inline the proved `GameRoot::active_bod_list.remove_bod((BodNode*)this)` owner.
The zero-flags path, explicit-kill `0x200` path, and expired-transition `0x400`
path are three native copies of the same `cLinkedList<cRBod>::Remove` template,
not a scratch-local widget-unlink helper. The cast is an exact shared-prefix
view: `FrontendWidget`/`cRBorder` storage begins with the 0x10-byte `BodNode`.

This lifts the focused result from `55.62%` (`572/647`) to `64.35%`
(`646/647`) and improves the masked audit from `71 ok / 2 mismatch` to
`83 ok / 1 mismatch`. The prefix falls from 42 to 1 because VC6 keeps a zero
in `edi` across the three template expansions and consequently saves an extra
`ebx`; the retained code is still the substantially closer and better-owned
source. Keeping only the first teardown manually expanded regressed to
`58.08%`, `634/647`, and `73 ok / 2 mismatch`, so that probe was rejected.
