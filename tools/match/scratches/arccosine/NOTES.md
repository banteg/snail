# arccosine @ 0x44ca00

Exact match: 100.00%, 3/3 instructions.

This helper is the shared arccosine wrapper used by quaternion and
attachment/camera math paths. The explicit result local prevents VC6 from
tail-calling the CRT wrapper.
