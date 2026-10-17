# initialize_global_font_queue_colors @ 0x449c50

Startup constructs exactly 1024 `cFontPrintBuffer::color` subobjects. The first
receiver is `g_font_queue + 0x6c`, each receiver advances by the exact
`sizeof(cFontPrintBuffer) == 0x84` stride, and every call targets the folded
trivial constructor at `0x44db50`. This proves the queue capacity and member
ownership independently of queue consumers.

The Android global constructor keyed to `Font.cpp` repeats the same walk over
`FontPrintBuffer`, constructs `tColour` at record +0x6c, advances by 33 dwords,
and stops at the adjacent `FontPrintBufferIndex` symbol. Its mangled renderer
signatures expose the record's authored name as `cFontPrintBuffer`.

## 2026-08-12 Font source-unit recovery

The Android symbol table preserves that constructor's exact local name as
`_GLOBAL__I_Font.cpp`. The same body constructs both `RFont3D` and
`FontPrintBuffer`, directly binding the two startup loops to the authored Font
source instead of relying on adjacency. The independent iOS source catalog
maps the Font symbol family to `Font.o`; together these recover `Font.o` for
this Windows body and its direct CRT thunk at `0x449c40`.

Windows remains authoritative for its 1024-entry capacity. Android proves the
same 0x84-byte record stride and +0x6c tColour lane but has only 512 entries,
so its capacity is not transferred. The exact Windows 11/11 body and 1/1 thunk
are unchanged.

## 2026-10-17 global-definition form deferred

This body and its thunk are VC6's `_$E1`/`_$E2` dynamic-initializer pair: the
thunk is a lone `jmp` to the body, and the body constructs `cFontPrintBuffer
g_font_queue[FONT_QUEUE_CAPACITY]`, whose implicit element constructor runs the
`color` member's constructor at +0x6c. Their original source is that global's
definition, as with RMaths' `TransformMatrix g_identity_matrix(1.0f)`, and the
explicit wrapper and loop here are stand-ins for it.

VC6 emits this construction only when `tColour` declares its default
constructor (the folded identity body at `0x44db50`). Declaring `tColour();` in
`sprite.h` breaks 118 currently exact functions in the whole-TU build: G0 and
Mouse stop compiling, and 48 functions in Border, Game, SubGame, Font, Path and
other units regress. Those functions still spell `tColour` construction
explicitly through `noop_this_constructor` and the pointer-returning four-float
`Set`. The explicit form stays until `tColour`'s constructors and those callers
are recovered together.
