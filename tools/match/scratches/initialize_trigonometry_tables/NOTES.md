# initialize_trigonometry_tables @ 0x44c930

Exact match: 100.00%, 18/18 instructions.

Builds the shared cosine and sine lookup tables, then resets the companion
gameplay random table. The angle scale is kept as two `float` multiplies so VC6
emits the native two `fmul dword` sequence before `fcos`/`fsin`.

The init loop increments the table index before storing, so VC6 relocates the
writes against one-float-before bases at `data_777f38` and `data_77ff88`. The
lookup helpers still read the canonical table starts at `data_777f3c` and
`data_77ff8c`.
