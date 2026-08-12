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
