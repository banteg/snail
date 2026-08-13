# initialize_warning @ 0x446e80

Exact match: 100.00%, 32/32 instructions.

This allocates the warning border, initializes sprite `0x5e` with frontend
sprite-button flag word `0x400802`, disables the sprite shadow draw, hides the
border, and resets the progress state.

2026-06-16 type consolidation: the warning border now uses the shared
`FrontendWidget` view from `frontend_widget.h`; +0x178 is a confirmed widget
slot. This scratch remains exact.

2026-06-16 warning actor consolidation: the 16-byte controller now uses the
shared `Warning` view from `warning.h`; the phase fields are
+0x04/+0x08 and the frontend border pointer is +0x0c. This scratch remains
exact.

2026-07-11 authored-owner recovery: iOS names the wider mobile entry point
`cRWarning::Init(cRSubGoldy*)`; Android exports `cRWarning::Init()` and calls
it from `cRSubGame::Init()`. Android initializes the same state/phase/border
roles but places two extra presentation lanes before its border pointer, so
the shared `Warning` type preserves the exact 0x10-byte Windows layout without
claiming cross-port byte identity. Focused Wibo remains exact at 32/32
instructions with six clean masked operands.

2026-07-12 cRBorder layout closure: the exact sprite initializer writes 4.0f
to +0x178 and the draw path uses it as the optional second-sprite offset, so
the field is now `sprite_shadow_offset`, not warning state. Warning setup clears
that presentation effect. Focused Wibo remains exact at 32/32 instructions.

## 2026-07-14 warning lifecycle ownership

Initialization now names the authored controller's reset state as
`WARNING_STATE_INACTIVE`. The complete Windows field-xref set and Android
`cRWarning` methods expose only states 0, 1, and 2. Focused output remains exact
at 32/32 instructions with six clean operands.

## 2026-07-17 paired decompiler ownership replay

The narrow `Warning` replay now guards the exact `0x10` Windows owner and all
six `void __thiscall(Warning*)` lifecycle ABIs in both databases. Binary Ninja
was already current through the broader root replay; IDA applied the missing
receiver types, so both tracked decompiles now expose `state`, `phase`,
`phase_step`, and the owned `FrontendWidget* border` directly. Focused matching
remains exact at 32/32 instructions with six clean masked operands.

## 2026-08-09 primary cRWarning ownership

The matcher now emits this initializer as `cRWarning::Init()` and binds the
owner-qualified VC6 symbol `?Init@cRWarning@@QAEXXZ`; `Warning` remains a
compatibility typedef for existing analysis replays. The live Windows view
confirms the void `thiscall` receiver and sole direct call at `0x4379e5` from
subgame initialization. Android independently exports `cRWarning::Init()`;
iOS preserves the same owner role as `cRWarning::Init(cRSubGoldy*)`, with its
port-specific parent argument and wider layout left local to that build. The
promotion is codegen-neutral: focused matching remains exact at 32/32
instructions with all six masked operands clean.

## 2026-08-13 canonical analysis-owner replay

The paired analysis databases now use `cRWarning` as the sole primary 0x10-byte
Windows owner. The replay retires the generic `Warning` record only after exact
layout equivalence, verifies the embed at `Player +0x3f4`, and rebinds all six
lifecycle ABIs. The matcher keeps `Warning` only as a source-compatibility
typedef. This ownership-only change leaves `Init` exact at 32/32 instructions
with all six masked operands clean.
