# initialize_trigonometry_tables @ 0x44c930

Exact match: 100.00%, 18/18 instructions.

Builds the shared cosine and sine lookup tables, then resets the companion
gameplay random table. The angle scale is kept as two `float` multiplies so VC6
emits the native two `fmul dword` sequence before `fcos`/`fsin`.
