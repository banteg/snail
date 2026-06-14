# advance_timer_counters

- Exact match: 100.00%, 38/38 instructions.
- Uses the same typed six-field `TimerCounters` layout as
  `zero_timer_counters`: total seconds, minutes, frames within the current
  second, display hundredths, display thousandths, and fractional second.
- Source shape detail: the exact form increments `frames_into_second` first,
  snapshots the updated field into a local, and then compares that local
  against 60. This preserves the native `edx -> eax` copy and the store before
  the compare without fake no-ops.
- Semantics: converts the incoming 60 Hz-scaled delta to seconds, accumulates
  total/fractional time, rolls frames at 60 into minutes, and refreshes the
  display hundredths/thousandths from the current fractional second.
