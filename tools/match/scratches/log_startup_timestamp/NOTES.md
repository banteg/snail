# log_startup_timestamp

Startup timestamp report helper at `0x406d30`.

Recovered behavior:

- fills a stack `_timeb`-style buffer with `_ftime`;
- passes the leading `time` field to `ctime`;
- reports the date prefix, millisecond field, timezone suffix, and raw time
  value through the release-stripped debug report stub at `0x449c00`.

Focused match: 100%, 19/19 instructions, with four clean masked operands.

This scratch compiles as C (`/TC`). C-mode MSVC 6.5 preserves the old-style CRT
call cleanup across `_ftime`, `ctime`, and the debug stub call, producing the
native final `add esp, 0x28`.

2026-07-15 CRT ownership: the timestamp buffer is VC6's real `struct _timeb`
from `<sys/timeb.h>`, with `time_t` and `ctime` supplied by `<time.h>`. This
removes the scratch-local `TimeBuffer` layout and unprototyped CRT calls while
preserving the exact 19/19 object and all four masked operands.
