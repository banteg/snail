# Sqrt @ 0x44cab0

Exact match: 100.00%, 3/3 instructions.

Android and iOS preserve the authored float `Sqrt(float)` contract. Promoting
the Windows return type is byte-identical in this helper and its exact vector
and kind-42 attachment callers; x87 still returns the value in `st(0)`.
