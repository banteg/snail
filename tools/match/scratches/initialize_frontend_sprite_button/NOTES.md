# cRBorder::Init @ 0x401a70

Exact match: 100.00%, 157/157 instructions, with all ten masked operands
clean.

This is the sprite-backed overload of `cRBorder::Init`. It links the receiver
into the root-owned active border list, resets tooltip and visual-transition
state, installs fill and text colours, derives the hit rectangle from the
sprite texture, records the authored anchor and layer, and finishes with
`RePosition()`.

Android and iOS `Border.o` independently preserve
`cRBorder::Init(int, int, float, float, tColour, float, int)` and the same
lifecycle. Windows retains its separately proved 0x724-byte owner and borrows
the colour as `tColour*`; live analysis confirms a void thiscall and seven
native calls using that pointer ABI.

The exact VC6 source shape keeps an ordinary `idle_fill` alias live through
the colour-copy block and computes the adjusted anchor before the final layout
stores. The stable matcher identity remains
`initialize_frontend_sprite_button`; source and relocations now use the
authored overload name.

## 2026-09-07 verified colour-constructor temporaries

The four-float constructor mapping is already closed by its exact callee and
Windows/mobile caller roles. This local `sprite.h` shadow adds the real C++
constructors and converts all affected expressions to constructor temporaries,
without introducing default construction or changing the Windows pointer
parameter contracts. Both mobile Tip initializers independently construct one
colour temporary for each widget call.

Both expression-temporary controls retain the complete 157/157 match and
all ten clean references.
The two exact widget initializers therefore control the conversion, but it
does not close either partial caller. The recipe and receipts retain the
whole overlays; no shared header or canonical source is changed.
