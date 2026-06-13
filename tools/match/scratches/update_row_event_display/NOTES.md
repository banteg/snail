
## Iteration gain (loop session 2026-06-12): 78.52% -> 85.06%

The two sound calls are THISCALL on a global manager
(`mov ecx, ADDR; push id; call`) — converted from the old __stdcall
decl; +6.5 points. Remaining: the float-accumulation region around
target lines 161-196 spills intermediate sums to slots (the dual-slot
temp class — break the expression tree into named float temps per the
IDA rendering, output pointer lea [esi+0x34] suggests the sums build
into a member vector through a temp), and the frame is 0x3c vs 0x30.

## Iteration gain (2026-06-13): 85.06% -> 85.19%

The widget-world output now writes through a typed `Vec3*` view of
`controller+0x34` instead of a separate local copied back to the
controller. This is source-plausible for the native member-vector store
owner and trims three candidate instructions without changing the
recovered row-event semantics. A `< 10` spelling of the delivered-count
tens branch was tested because it matched the local branch direction, but
it regressed the whole function to 82.87%, so the clearer `>= 10` source
form remains.
