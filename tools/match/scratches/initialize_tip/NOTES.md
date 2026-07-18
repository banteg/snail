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
passing the button y positions as direct `definition->layout_y +/- constant`
expressions moves focused Wibo to 81.70%, 152/154 candidate/target
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
