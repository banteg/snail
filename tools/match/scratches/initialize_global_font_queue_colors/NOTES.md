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
