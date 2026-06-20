# format_time_trial_string

`format_time_trial_string` @ 0x448960 formats the shared Time Trial HUD buffer
at 0x751478 from the exact `TimerCounters` layout used by
`advance_timer_counters`.

Behavior:

- `total_seconds == 0.0f` emits the `-:--:--` sentinel.
- Non-zero timers first emit the thousandths string and then immediately
  overwrite it with the centiseconds string; callers observe the final
  `%1i:%02i:%02i` form.
- The helper returns the shared 0x751478 buffer.

Focused match: 100%, 36/36 instructions, with twelve clean masked operands.

This scratch compiles as C (`/TC`) with a local C-compatible `TimerCounters`
layout shell. C-mode MSVC 6.5 coalesces cdecl stack cleanup across the two
adjacent non-zero-branch `sprintf` calls, producing the native `add esp, 0x28`
after the second call.

2026-06-20 local C-view naming: the local timer shell is now
`TimeTrialTimerCountersCView`. The shared `timer_counters.h` class remains the
right C++ owner, but this `/TC` scratch deliberately keeps a C-compatible view.
The focused match stays exact at `100.00%`, `36/36`, with `12 ok` masked
operands, and the type report no longer advertises `TimerCounters` as a
promotable local duplicate.
