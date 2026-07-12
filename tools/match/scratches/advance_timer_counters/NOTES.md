# advance_timer_counters

- Exact match: 100.00%, 38/38 instructions.
- Uses the same typed six-field authored `Time` layout as `cRTime::Zero` /
  `zero_timer_counters`: total seconds, minutes, seconds within the current
  minute, display hundredths, display thousandths, and fractional second.
- Source shape detail: the exact form increments `seconds` first,
  snapshots the updated field into a local, and then compares that local
  against 60. This preserves the native `edx -> eax` copy and the store before
  the compare without fake no-ops.
- Semantics: converts the incoming 60 Hz-scaled delta to seconds, accumulates
  total/fractional time, rolls seconds at 60 into minutes, and refreshes the
  display hundredths/thousandths from the current fractional second.
- 2026-06-16 type consolidation: the timer value now comes from a shared
  header; `zero_timer_counters`, `advance_timer_counters`,
  `format_time_trial_string`, and the runtime-populate reset call all keep their
  previous match/audit profiles.
- 2026-07-12 ownership recovery: Android exports this exact 0x18-byte owner as
  `cRTime` and preserves `cRTime::Add(float)` beside `Zero`, `AddFraction`, and
  `Faster`; iOS also preserves the authored `Add(float)` name. Both mobile
  bodies return void. Declaring the Windows method as void leaves its 38/38
  codegen exact: the final EAX value is merely the integer conversion stored in
  `display_thousandths`, not a semantic return value.
