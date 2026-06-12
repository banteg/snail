
## Iteration gain (loop session 2026-06-12): 78.52% -> 85.06%

The two sound calls are THISCALL on a global manager
(`mov ecx, ADDR; push id; call`) — converted from the old __stdcall
decl; +6.5 points. Remaining: the float-accumulation region around
target lines 161-196 spills intermediate sums to slots (the dual-slot
temp class — break the expression tree into named float temps per the
IDA rendering, output pointer lea [esi+0x34] suggests the sums build
into a member vector through a temp), and the frame is 0x3c vs 0x30.
