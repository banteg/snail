# FontAI

`FontAI()` is the native-authored owner of the Windows routine at `0x449ca0`.
The focused match is exact: 25/25 instructions and 17 clean references.

It resets the transient text cursor and queue counters, advances both wave
phases, and wraps them by one full turn. Android and iOS both export `FontAI()`
from `Font.o`; the live Windows database has one main-loop caller.

The directory and manifest retain `update_font_wave_state` as the stable
matcher identifier; source and linkage use the recovered authored name.
