# initialize_tip

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
baseline, seven are neutral, and 57 regress, with one retained sweep win and
three trailing non-improving sweeps. `initialize_tip` is formally stalled at
84.42%, 154/154 instructions, prefix 19, 26 clean references, and the same two
unaudited global loads. The member reference remains the strongest honest
source; no volatile reload, dummy use, or raw owner view is reintroduced.
