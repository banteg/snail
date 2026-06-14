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

Match status: 95.89% (35/36 target instructions semantically aligned, candidate
has one extra instruction).

Residual:

- Native coalesces the cdecl stack cleanup across the two adjacent `sprintf`
  calls in the non-zero branch (`add esp, 0x28` after the second call).
  `msvc6.5 /O2 /G5 /W3` emits `add esp, 0x14` after each call for the plain
  source shape.
- Rejected source-shape probes: comma expression, early return from the non-zero
  branch, return comma expression, `void sprintf`, non-const format pointer, and
  VC6 `<stdio.h>` declaration. All kept the same cleanup split.
