# initialize_tip

## 2026-09-09 live flag reads and alignment lifetime

The retained source improves **84.42% to 87.66%**, keeps **154/154**
instructions and **27 clean references**, and extends the exact prefix from
19 to 23 instructions. The alignment mask is applied at the widget call,
after preserving the signed-byte complement in an unsigned scalar. This
recovers the native full-width flag load, byte complement, and sign extension.
The result still has precisely the same two possible alignment values, 0 and 2.

The timed and modal gates now read the definition's flags at each use. Native
code tests `[eax]` directly on both gates, including after the timed-state
writes; Android also reloads the flags after entering the timed branch. This
removes the old shared flags snapshot and recovers the main widget argument
schedule and the timed/modal test region. Windows remains authoritative for
the unguarded dismiss-time division and the integer second formal.

The receipt in `live-flags-and-alignment-lifetime-20260909.json` embeds both
sources, native/baseline/candidate listings, full diagnostics, and the focused
probe. All seven authored `Tips.o` members were compiled in native and reversed
order: the six exact controls remain exact and this initializer preserves its
new metrics. The full 785-row status comparison changes only this initializer.

This remains a partial, with zero additional proof-grade functions or bytes.
The first remaining difference is equivalent shift/mask ordering; later
differences cover parent-widget call setup, the OK-only colour argument, and
the final frontend-owner handoff. The higher fuzzy result is not an encoded
body exactness claim. Additional slot-reference controls reach the same score
with a shorter prefix and are not retained.

Current recovery: semantic-complete (`compiler` residual). Exact Android/iOS
`cRTip::Init(cRTipData*, bool)` bodies and the live Windows Tip method establish
the default definition, timed/modal branch, three-widget construction, and
frontend-owner handoff. All 27 references are clean; the remaining delta is
equivalent definition-field register allocation and call scheduling.

Initial source-shaped scratch for the tip slot initializer.

Recovered relationships:

- `Tip::active`, `definition`, `widget_main`, `widget_ok`,
  `widget_disable`, `dismiss_progress`, `dismiss_step`, and
  `previous_outer_owner` use the shared `tip_manager.h` layout.
- null definitions fall back to the default tip definition at `data_4ac5c8`.
- the main widget is always allocated from the owned
  `GameRoot::border_manager` at root `+0xb4c`.
- definition flag bit `2` enables auto-dismiss timing; bit `1` enables the
  modal OK/Disable button path and switches the outer frontend owner to `0x16`.
- the second argument is a `hide_disable_button` gate: zero builds both OK and
  Disable buttons, while nonzero builds the OK-only modal path.

This is a first-pass relationship scratch; string/default-definition operands
may need curation before a future exact/audit-clean result.

Focused Wibo result after curating the real default tip definition at
`0x4ac5c8`: 75.00%, 158/154 candidate/target instructions, with 24 masked
operands OK and no unresolved or mismatched operands.

2026-06-21 tip argument/shape pass: native branches to the OK-only path when
the second argument is nonzero, so the parameter is now modeled as
`hide_disable_button`. Spelling the alignment as an unsigned masked value and
passing the button anchor positions as direct
`definition->anchor_x +/- constant` expressions moves focused Wibo to 81.70%,
152/154 candidate/target
instructions, with 25 clean masked operands. Remaining residual is source-shape
scheduling around the initial `widget_main` store versus definition reload,
main-widget argument load order, and final owner restore.

2026-06-21 post-allocation reload pass: reloading the stored definition member
through a narrow volatile view after allocating `widget_main` recovers native's
`widget_main` store before the two definition loads. Focused Wibo improves to
82.74%, with 153/154 candidate/target instructions, prefix 19/154, and the same
25 clean masked operands. Non-volatile member reloads are codegen-neutral at
81.70%, while local widget aliases perturb the prologue and drop to 69.90%.

2026-06-21 live-flags pass: keeping a separate `live_flags` dword for the
post-widget auto-dismiss/modal gates improves focused Wibo to 84.42% and
restores instruction-count parity at 154/154 while preserving the 25 clean
masked operands. Reusing the initial flags value for all later gates regresses
to 59.74% by overextending the first definition load, and signed-byte alignment
locals regress slightly; keep the scalar `definition_flags` for alignment and
the later `live_flags` reload for the gate checks.

2026-07-10 barrier retirement and owner promotion: the two volatile definition
reloads after `allocate_border` were register-scheduling barriers and are gone.
Direct member reads retain instruction-count parity and 25 clean masks at an
honest 83.12%, 154/154, prefix 16/154. The saved/replacement outer state is now
`GameRoot::players[0].frontend_state`; both that field and the border-manager
ownership are independently constructor- and exact-caller-backed.

2026-07-12 cross-port ownership pass: symbol-preserving iOS builds identify
this member as `cRTip::Init(cRTipData*, bool)` in v1.5 and
`cRTip::Init(cRTipData*, signed char)` in v1.9. The ARM bodies independently
confirm the 0x20-byte Tip layout and 0x14-byte TipData field order used here,
including the `gTips` null-definition fallback. Windows reads the second formal
with a 32-bit stack load and compare, so the native Windows declaration keeps
`int hide_disable_button` instead of importing either mobile-width spelling.

2026-07-18 durable decompiler replay: Binary Ninja and IDA now preserve the
full `Tip`/`TipData` graph, `FrontendWidget*` members, default `gTips` entry,
owned `GameRoot::border_manager`, and `players[0].frontend_state` handoff.
Exact 0x14/0x20/0x98 owner-size assertions and paired health checks prevent the
analysis from drifting back to synthetic slots, `void*` widgets, or raw root
offsets. The honest matcher result remains 83.12%, 154/154, prefix 16, with 25
clean masked operands; no source scheduling was changed for appearance.

## 2026-07-28 dual-mobile TipData coordinate ownership

The complete Android and iOS `cRTip::Init(cRTipData*, bool)` bodies close the
two formerly misnamed floats. In all three builds `TipData +0x04` is passed as
both the main widget X and anchor-X, while `+0x08` is passed as its Y
coordinate. The OK and Disable children reuse `+0x04` with `+40` and `-60`
offsets; neither port consumes `+0x08` as a font scale. Windows independently
confirms the producer by storing `(0.0f, 30.0f)` into the row-event definition
before enqueueing it.

The shared owner now names these fields `anchor_x` and `layout_y`. This is a
layout-preserving ownership correction: focused matching remains honestly at
83.12%, 154/154 instructions, prefix 16, with all audited operands clean.

## 2026-07-29 main-widget member borrow

Two recorded sweeps evaluated 54 ordinary widget, definition, flag, and
alignment lifetimes. Borrowing the owned `widget_main` slot as a
`FrontendWidget*&` before allocation is the only retained improvement. It
prevents VC6 from hoisting the following definition load across publication
of the newly allocated widget, recovering the native store and the next two
loads without a volatile barrier.

Focused matching rises from 83.12% to **84.42%**, still 154/154 instructions,
and the exact prefix grows from 16 to 19 instructions. All 26 aligned
references remain clean; the two existing unmatched global-load operands stay
explicitly unaudited.

Pointer/value aliases for the widget and definition, staged call fields,
direct or byte-sized post-call flag tests, and ten signed-character alignment
carriers are neutral or worse. In particular, spelling the signed conversion
more explicitly changes the final shift but does not recover native's
`not cl` / `movsx eax, cl` register split. The retained member reference states
real ownership; no volatile qualifier, raw offset, or register-shaped cast is
introduced.

## 2026-07-29 alignment and main-call owner closure

Two follow-up sweeps add twelve source-shaped variants. Explicit `register`
ownership on the full flags value, signed-byte carrier, alignment result, and
split initialization is completely byte-neutral in all six combinations.
VC6 continues to keep the flags/result in EAX, producing `not al` and eliding
native's `movsx eax, cl`; a source hint cannot recover the ECX-to-EAX split.

The earlier definition-borrow and field-staging tests did not include the
retained `FrontendWidget*&` publication owner, so the second sweep covers that
interaction directly. Single and split `TipData*` borrows are the closest at
80.78%. Staging only `layout_y` or the final anchor reaches 79.35-80.00%;
borrowing the anchor or staging only text perturbs the prologue and falls to
61.29-68.81%. None improves the initial call's register rotation or the later
root/border-manager load alignment.

The complete ledger now covers 66 unique variants: two improve an earlier
baseline, seven are neutral, and 57 regress, with one retained sweep win. The
current result is 84.42%,
154/154 instructions, prefix 19, with all 27 references clean. The member
reference remains the strongest honest source; no volatile reload, dummy use,
or raw owner view is reintroduced.

## 2026-08-09 primary cRTipData and cRTip ownership

The matcher now emits this body as
`cRTip::Init(cRTipData*, int)` and selects the exact VC6 symbol
`?Init@cRTip@@QAEXPAUcRTipData@@H@Z`. `TipData` and `Tip` remain compatibility
typedefs for shared callers and analyzer replays.

The live Windows view confirms a void `thiscall` receiver, two 32-bit stack
formals, and the sole direct call from `cRTipManager::TipNew` at `0x448d6a`.
Android and iOS independently preserve `cRTip::Init(cRTipData*, bool)` and the
same 0x14-byte definition / 0x20-byte owner graph; later iOS uses a signed-char
gate. Windows still loads and compares the full 32-bit second argument, so this
promotion deliberately keeps `int hide_disable_button` and does not import a
mobile-width ABI.

This authored-name change is codegen-neutral: focused matching remains 84.42%,
154/154 instructions, prefix 19, with all 27 currently audited references
clean. The 66 recorded source-shape variants remain as evidence. This closes
the matcher owner spelling.

## 2026-08-09 stale mutation-plan retirement

`main-widget-lifetime-mutations.json` is retired. The append-only experiment
ledger already preserves the explored widget-lifetime lane and its retained
member-reference winner, while the plan's anchor no longer matches the current
authored `cRTip` source.

## 2026-09-05 bounded source-expression probes

Three direct-widget and definition-flag reload combinations regress from 84.42%. No source change is retained.

The recorded specifications and experiment receipts preserve these negative
results. They do not establish source exhaustion or compiler provenance.

## 2026-09-05 whole-function source-lifetime probes

Eleven whole-function color/widget/flag combinations test call-local colors, independent color locals, direct widget access, and live definition flags. None improves 84.42%; all reference operands remain clean. These combinations do not close the remaining argument/register lifetimes.

## 2026-09-05 continued source-shape investigation

Eleven flag, definition, and widget-owner reuse forms give no gain at 84.42%. Reusing local names is neutral; changing the actual borrow or reload lifetimes regresses.


## 2026-09-07 five-function campaign evidence

Twenty-nine paired alignment, widget, and definition-flag ownership forms
were recorded. The best reaches 87.01% from 84.42% but does not recover the
complete native call and flag-read schedule. No source or shared flag type is
promoted; the signed-byte complement and later live reads remain useful leads.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.

## 2026-09-07 recipe discovery and allocator-name repair

The expanded `--check-specs` audit now discovers every scratch-local JSON
recipe. It exposed `main-call-owner-interactions.json` as an unreceipted,
stale input: its anchor and six alternatives still used `allocate_border()`
after the authored allocator was renamed to `GetBorder()`.

Only that method spelling is refreshed. All six variants were replayed and
recorded against the current source; they reproduce 80.78%, 80.78%, 80.00%,
79.35%, 68.81% and 61.29%, with 27 clean references apiece. None improves the
canonical 84.42%, 154/154, prefix-19 result. This fixes the runnable recipe
without changing or retroactively rewriting the prior experimental evidence.

## 2026-09-07 verified colour-constructor temporaries

The four-float constructor mapping is already closed by its exact callee and
Windows/mobile caller roles. This local `sprite.h` shadow adds the real C++
constructors and converts all affected expressions to constructor temporaries,
without introducing default construction or changing the Windows pointer
parameter contracts. Both mobile Tip initializers independently construct one
colour temporary for each widget call.

Both the compatibility-ABI expression temporaries and real C++ temporaries
remain 84.42%, 154/154 instructions, prefix 19, with 27 clean references.
The two exact widget initializers therefore control the conversion, but it
does not close either partial caller. The recipe and receipts retain the
whole overlays; no shared header or canonical source is changed.
