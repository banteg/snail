# cRBorder::Init text overload @ 0x401d30

Current recovery: exact. Live Windows analysis establishes a void `thiscall`
member with eight stack arguments and a `cRBorder*` receiver. Android and iOS
independently retain the corresponding
`cRBorder::Init(int, char*, int, float, float, tColour, int, float)` method in
`Border.o`; Windows passes the color as a pointer.

The body covers active-list insertion, tooltip ownership, flags, all four style
presets, text and layout state, highlighting, and construction of the three
owned slider children. Its backing `BorderRecord` lifecycle and every consumed
field are represented through the shared `cRBorder` view.

Focused VC6 result: **100.00%**, 429/429 instructions and all 50 relocation
operands audited and clean.

The matcher source now uses the authored `Init` overload and exact VC6 symbol
`?Init@cRBorder@@QAEXHPADHMMPAUtColour@@HM@Z`;
`initialize_frontend_widget` remains only the stable scratch and Windows-address
identity.

## 2026-08-13 anonymous color-temporary recovery

The former scratch declared sixteen named `tColour` locals solely to carry the
four style colors through the switch. That spelling was not source-backed and
left two otherwise-identical instructions with the first and last temporary
stack slots exchanged.

Android and iOS independently materialize fresh `tColour` values for these
assignments. Spelling the Windows equivalent directly as
`tColour().Set(...)` for each style assignment and slider argument removes the
synthetic local bank and lets VC6 recover the native temporary lifetimes. The
result is an exact 429/429 match with a 429-instruction prefix and all 50
references clean. Replaying the old named-local source records the expected
99.53% regression and 355-instruction prefix loss.

The four color-slot mutation plans are retired because they target the removed
synthetic locals; their append-only ledger entries remain as historical
evidence.

## 2026-09-07 verified colour-constructor temporaries

The four-float constructor mapping is already closed by its exact callee and
Windows/mobile caller roles. This local `sprite.h` shadow adds the real C++
constructors and converts all affected expressions to constructor temporaries,
without introducing default construction or changing the Windows pointer
parameter contracts. Both mobile Tip initializers independently construct one
colour temporary for each widget call.

The real C++ constructor control retains the complete 429/429 match and
all 50 clean references.
The two exact widget initializers therefore control the conversion, but it
does not close either partial caller. The recipe and receipts retain the
whole overlays; no shared header or canonical source is changed.
