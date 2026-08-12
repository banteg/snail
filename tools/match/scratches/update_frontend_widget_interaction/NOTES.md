# update_frontend_widget_interaction @ 0x402820

Current recovery: semantic-complete (`compiler,references` residual). Exact
Android/iOS `cRBorder::AI` bodies and the live Windows slot-zero void method
establish the complete flag/list, input, tooltip/twinkle, text, draw, and
slider-child state machine. No reference is unresolved or mismatched. The two
unaudited operands are known candidate-only `1.0f` and `0.0f` clamp loads from
VC6's alternate endpoint-store schedule.

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
`FrontendWidgetTooltip` subobject declaration and the exact `int` return ABI for the
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
inline the proved `GameRoot::active_bod_list.remove_bod(this)` owner.
The zero-flags path, explicit-kill `0x200` path, and expired-transition `0x400`
path are three native copies of the same `cLinkedList<cRBod>::Remove` template,
not a scratch-local widget-unlink helper. `FrontendWidget`/`cRBorder` now
inherits the exact `BodBase` initialized by its record constructor, so the
intrusive `BodNode` links have one owner rather than a cast-only prefix view.

This lifts the focused result from `55.62%` (`572/647`) to `64.35%`
(`646/647`) and improves the masked audit from `71 ok / 2 mismatch` to
`83 ok / 1 mismatch`. The prefix falls from 42 to 1 because VC6 keeps a zero
in `edi` across the three template expansions and consequently saves an extra
`ebx`; the retained code is still the substantially closer and better-owned
source. Keeping only the first teardown manually expanded regressed to
`58.08%`, `634/647`, and `73 ok / 2 mismatch`, so that probe was rejected.

2026-07-12 widget-lane and input-state recovery:

- `+0x264/+0x268` are the teardown progress/step pair consumed under widget
  flag `0x400`; they are not font fields. The exact sprite initializer clears
  both lanes.
- `+0x278` is a one-frame mouse-history warmup counter initialized by the text
  widget constructor. `+0x27c/+0x280` retain the previous root cursor sample.
  These fields replace the false `+0x264` counter and false
  `+0x6e4/+0x6e8` history aliases.
- The wrapped-text update writes `layout_x/+0x238`, `layout_y/+0x23c`,
  `layout_width/+0x248`, and `layout_height/+0x24c`, agreeing with the adjacent
  `layout_frontend_widget` member. `+0x240/+0x244` are the later derived hit
  coordinates, not text-layout outputs.
- `shortcut_key_code +0x194` is an integer; the signed-byte key result is
  promoted before comparison, matching the native `movsx` plus dword compare.
- Primary input (`input +0x3d & 0x40`) belongs to widget flag `0x10` and is
  gated while the BorderManager delayed lane is active. Secondary input
  (`& 0x80`) is a separate widget-flag `0x40` path. Splitting those paths also
  recovers the `FrontendWidgetTooltip::mode_flags & 0x20` reset gate.

Together these corrections lift the focused result from `64.35%` (`646/647`)
to `68.32%` (`644/647`) and improve the masked audit from
`83 ok / 1 mismatch` to `93 ok / 0 mismatch`. The one-instruction prefix still
reflects the documented extra saved `ebx`; no fake register coercion was kept.

2026-07-13 embedded twinkle ownership: native forms `ecx = this + 0x80` before
the exact `update_twinkle_manager` call. That manager's exact helper reads
`active_state +0xf0`, `twinkle_count +0xf4`, and walks five 0x30-byte inline
twinkles, proving a 0xf8-byte `TwinkleManager` subobject at widget
`+0x80..+0x177`. It ends exactly where the independently recovered
`sprite_shadow_offset +0x178` begins. The shared widget and decompiler views
now expose that owned subobject instead of anonymous padding.

## 2026-07-13 complete widget field ownership

The update body now addresses the shared `FrontendWidget` fields directly
instead of rebuilding its exact 0x724-byte layout through raw `self + offset`
casts. The same pass reaches the root-owned player cursor, borrowed
`GameInput`, and embedded `BorderManager` through `GameRoot`. The primary and
secondary input tests are the `pressed_buttons` bits `0x4000` and `0x8000`.

The mouse-movement edge specifically samples `MouseCursorState::saved_x/y` at
player-cursor `+0x0c/+0x10`; these are root `+0x29c/+0x2a0`, not the live
coordinates at `+0x294/+0x298`. Focused output remains the honest 68.32%,
644/647-instruction partial with all 93 masked operands clean.

The preview-verified Binary Ninja layout now carries the complete 0x724-byte
`FrontendWidget`, including the 0x40-byte tooltip/`InputOkState` overlay at
`+0x28c`. This replaces the previous zero-sized forward declaration and makes
all border-manager pointers use the recovered concrete record view.

2026-07-14 base ownership closure: the semantic `FrontendWidget` and backing
`BorderRecord` views now share their actual inherited `BodBase`. Exact
`initialize_border_record` constructs that base before installing the widget
vtable, and `allocate_border` returns the same record storage through the
widget view. The interaction scratch remains the honest 68.32%, 644/647
partial with a one-instruction prefix and all 93 masked operands clean.

The three active-list removals now rely on that proven public inheritance
directly. No `BodNode*` prefix cast remains to obscure that the list borrows
the widget's inherited node rather than a separate overlay object.

## 2026-07-14 widget flag ownership

Independent exact helpers now close the shared state word around this dense
consumer: hide/unhide own `HIDDEN`, `kill_border` produces `KILL_PENDING`, the
text editor clears `TEXT_INPUT_ACTIVE`, `SetKeyLeft` produces
`SHORTCUT_KEY_ENABLED`, the tooltip consumes `POINTER_INSIDE`, and the delayed
manager pair owns `FADE_BEFORE_ACTION`. Menu/screen updaters consume and clear
`PRIMARY_ACTION_TRIGGERED`; slider endpoints, the border stack, and twinkles
independently establish `DISABLED`. Bits without comparable external evidence
remain numeric.

## 2026-07-14 root ownership closure

The interaction method now holds the process global as `GameRoot*` throughout.
Its three active-list removals, player-zero cursor/input reads, and delayed
widget operations therefore traverse the canonical root graph without a
scratch-local byte-owner declaration. Focused output remains 68.32%, 644/647
instructions, with all 93 operands clean.

## 2026-07-14 analysis ownership synchronization

The proven nine-bit `FrontendWidgetFlag` vocabulary now reaches every
checked-in `FrontendWidget` analysis header and the narrow Binary Ninja replay.
Both `widget_flags +0x1a0` and `previous_widget_flags +0x1a4` carry the shared
enum on the exact 0x724-byte live owner. The matcher remains byte-identical;
unproven interaction/style bits deliberately stay numeric.

## 2026-07-15 authored cRBorder AI ownership

The mobile binaries close the original class identity without relying on a
name-only match:

- the iOS `Border.o` function `cRBorder::AI()` spans `0x3c410..0x3d14f` and
  calls `cRBorder::MouseTest`, `cRToolTip::AI`, `cRTwinkle::AI`,
  `cRBorder::RePosition`, `cRBorder::Draw`, `cRBorder::InputText`, and
  `cRSound::Play`; its sound immediates and branches retain the Windows 8/9
  activation/hover roles;
- the unstripped Android `cRBorder::AI()` at `0x55948` preserves the Windows
  `+0x194/+0x198` flag snapshot, `+0x170/+0x174` slider easing, three
  active-list removals, delayed-click manager calls, text/color interpolation,
  input editor, and `+0x710..+0x720` slider-child tail;
- Windows has no direct call xrefs to `0x402820`: its only reference is the
  slot at `g_frontend_widget_vtable +0`, installed by
  `initialize_border_record`. Exact `run_frame_update` invokes every active
  BOD's slot zero as `void (__thiscall *)(FrameBodBase*)`, then advances to the
  saved successor without consuming EAX.

The Android decompiler's guessed `float` prototype merely propagates whatever
callee result happens to survive each exit; it is not source ABI evidence. The
shared slot-zero dispatch and cross-port class identity support the authored
void `cRBorder::AI()` contract already present in both analysis databases.
This pass changes ownership metadata and guards only: the scratch remains the
honest 68.32%, 644/647-instruction partial with a one-instruction prefix and all
93 masked operands clean. No register coercion or result-producing return was
introduced.

The focused tracked export also reanalyzed Binary Ninja's prior
`ExceedFunctionAnalysisTime` skip and recovered the complete high-level body
instead of the former prototype-only stub. That artifact now independently
shows the same `FrontendWidget`, `GameRoot::active_bod_list`, player cursor,
`BorderManager`, twinkle, tooltip, and slider-child owner graph as IDA; focused
health checks guard both lanes against falling back to raw offsets or an
anonymous receiver.

## 2026-07-16 interaction/style flag closure

The exact Windows initializers, interaction loop, draw/layout/kill helpers,
and high-score text-submit path now provide producer/consumer pairs for thirteen
additional interaction and style roles. Android `cRBorder::AI()` independently
preserves the same highlight, hover, primary/secondary input, immediate-action,
and sound-suppression branches. The shared enum therefore adds highlighted,
hover-highlight, hover-text-effect, primary-input, secondary-input/action,
sprite, snap-visual-state, slider, frameless, suppress-action-sound,
immediate-action, and text-input-submit bits across source and replay headers.
Bits that still
lack a comparably closed role remain numeric. These vocabulary-only changes do
not alter the focused machine-code matches. The narrow Binary Ninja replay now
compares enum names and values as well as owner widths, so future same-width
vocabulary changes cannot be silently skipped; a second live replay is cleanly
idempotent.

## 2026-07-16 manager deactivation restore marker

The Android `cRBorderManager::DeActivateBorders()` and all four
`DeActivateOtherBorders()` overloads set `0x80000000` only when a live widget
already has `DISABLED`, then force `DISABLED` for the batch. Its paired
`ActivateBorders()` clears `DISABLED` only when that marker is absent and
always clears the marker afterward, exactly matching Windows
`activate_all_borders`. The bit is therefore
`DISABLED_BEFORE_DEACTIVATION`. By contrast, `0x10000000` is only observed as
a bulk hide/disable/kill exemption and still has no producer in either port,
so it deliberately remains numeric. Binary Ninja represents the four-byte
high-bit member as signed `-2147483648`; replay readback now normalizes enum
values modulo their stored width, making the exact-member audit idempotent
without changing the saved declaration.

## 2026-07-16 shared input-button vocabulary

The controller-axis adapter and pointer-region adapter independently produce
the same `0x4000` primary-action bit, while the pointer adapter also produces
the `0x8000` secondary-action bit. `copy_active_input_controller_state` carries
that word into the typed `InputState` button lanes, and this routine consumes
the high-byte forms as `INPUT_BUTTON_PRIMARY >> 8` and
`INPUT_BUTTON_SECONDARY >> 8`. The shared names replace isolated literals
without inventing meanings for the other controller bits. Focused output
remains the honest 68.32%, 644/647-instruction partial with all 93 masked
operands clean.

## 2026-07-24 font-shadow flag recovery

Binary Ninja disassembly shows this member loading the full config flag word,
shifting it right by eight, masking the low bit, and preserving that byte
across the authored-rectangle branch before the wrapped-text call. A fresh
IDA 9.3 export independently renders the value as
`BYTE1(g_runtime_config.render_flags) & 1`. The previous scratch instead read
low bit zero, which was a real source error hidden by the larger register
schedule residual.

`draw_font_text_instance` closes the behavior: the byte gates only a second
black glyph draw at the positive font offset, while wave displacement always
uses `text_wave_amplitude`. The config bit is therefore
`RUNTIME_RENDER_FONT_SHADOW` and the queue byte is `shadow_enabled`.
Preserving the native byte in a local before the rectangle branch restores the
exact 647-instruction topology. Focused Wibo improves from 68.32% to 75.73%,
and the operand audit improves from 93 to 95 clean operands with no unresolved
or mismatched masks.

## 2026-07-27 mobile-authored color interpolation

iOS `cRBorder::AI()` explicitly recomputes the cold interpolation weight
around its separate fill-color and text-color writes; Android preserves those
same two calls, although its decompiler loses their argument expressions. The
Windows x87 body independently forms `1.0f - hover_blend_current` before each
four-lane color call rather than preserving one C++ local across both calls.
Removing that false shared lifetime raises the focused match from 75.73% to
77.07%. The candidate remains an honest 648 instructions against the
647-instruction target, and all 96 masked operands are now audited cleanly.

## 2026-07-29 bounded frontend constant schedule

Three complete mutation sweeps tested the remaining source-natural ways to
remove the candidate's extra saved `ebx`: equivalent zero predicates, original
unsuffixed `1.0` spellings, and slider-value lifetimes suggested by the
Android/iOS `cRBorder::AI()` bodies. The ledger covers 53 unique variants with
no repeats: 1 score-only improvement, 30 byte-identical variants, and 22
regressions.

All 15 zero-predicate combinations and the 30 float-preserving literal
combinations were neutral. The unsuffixed slider endpoint comparison instead
introduced a double comparison, two extra instructions, and an unaudited
reference, so it was rejected.

The mobile-style `more` branch local combined with a separate slider-tail
local moved the first mismatch from instruction 1 to instruction 37, confirming
that a float lifetime can repair the opening register schedule. It is not a
material improvement: the fuzzy score rises only 3 weighted bytes while the
candidate grows from 648 to 659 instructions against a 647-instruction target
and introduces three unaudited references. The other six slider-lifetime
combinations regress. The clean 77.07%, 648/647, 96-reference baseline remains
the retained source; recovering the native prologue now needs new ownership or
control-flow evidence rather than more constant spelling or artificial
register coercion.

## 2026-07-30 slider child and branch-value ownership

The Windows tail reloads `slider_less_widget +0x718`,
`slider_more_widget +0x71c`, and `slider_value_widget +0x720` at their
endpoint, color, blend, and text consumers. The prior scratch instead kept
three invented pointer locals live across those consumers, producing the
candidate's cached `edx`/`edi` tail. Direct member ownership at both endpoint
tests and all value-child writes raises the focused result from `77.07%` to
`80.62%`. All 96 masked references remain clean; the apparent `653/647`
instruction-count gap at that stage consists of the extra `ebx` save/restore
on the function's exits rather than a larger semantic tail.

The Android `cRBorder::AI()` body independently retains branch-local results
for both `slider_value + 0.2f` and `slider_value - 0.2f`. Reintroducing those
two float lifetimes on top of the corrected child ownership removes the false
long-lived `ebx`, advances the exact prefix from 1 to 127 instructions, and
raises the focused result to `95.83%`. The retained candidate has 649
instructions against the 647-instruction target, with `96 ok / 0 unresolved /
0 mismatch / 2 unaudited` references. The two unaudited references are the
local clamp assignments' `1.0f` and `0.0f` loads.

The obsolete `slider-pointer-lifetime-mutations.json` input is removed after
the owner rewrite. Its complete 5-variant and 31-variant sweeps remain in the
append-only experiment ledger; the old `FrontendWidget*` anchors no longer
describe the primary `cRBorder*` source and should not be replayed.

The remaining differences are now three bounded scheduling families:

- target initializes the long-lived `0x2000` flag in `edi` immediately before
  initializing `1.0f` in `ebp`; the candidate emits those two moves in the
  opposite order;
- the fill and text calls have identical topology and operands, but VC6
  commutes the eight `hover_blend_current * hot_channel` x87 multiplies;
- each branch-local clamp needs one extra `fld`/`fstp` pair, while the target
  stores the computed field before comparing and overwrites the endpoint
  directly.

Five follow-up sweeps bound the natural alternatives. Eight fill/text product
order variants and all compile-valid explicit `0x2000` owner variants are
byte-neutral. Fifteen branch-store variants do not improve the retained
source. Fifteen separate mobile-style cold-lifetime/direct-clamp combinations
are either neutral or regress to `95.29%`/`80.62%`. The experiment ledger now
covers 152 variants (141 unique), with five consecutive non-winning sweeps;
the current residual needs new source or ownership evidence rather than
constant spelling, shared cold lifetimes, direct field clamps, or register
coercion.
