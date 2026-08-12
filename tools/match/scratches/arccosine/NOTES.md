# ACos @ 0x44ca00

Exact match: 100.00%, 3/3 instructions.

Android and iOS preserve the authored float `ACos(float)` contract. The exact
Windows quaternion caller independently consumes a float result, and promoting
that return type remains byte-identical. The explicit double CRT-result local
prevents VC6 from tail-calling the wrapper.
