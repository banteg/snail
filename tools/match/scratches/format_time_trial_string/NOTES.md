# format_time_trial_string

`format_time_trial_string` @ 0x448960 formats the shared Time Trial HUD buffer
at 0x751478 from the exact authored `cRTime` layout used by
`cRTime::Add(float)` / `advance_timer_counters`.

iOS and Android preserve the authored signature as
`cRTimeTrial::TimeString(cRTime&)` in `TimeTrial.o`. Windows callsites seed
`this` with `SubgameRuntime +0xff25e0`; the following proven PathManager at
`+0xff2910` and the runtime size ledger independently fix this owner at 0x330
bytes. The formatter body itself does not read receiver fields.

Behavior:

- `total_seconds == 0.0f` emits the `-:--:--` sentinel.
- Non-zero timers first emit the thousandths string and then immediately
  overwrite it with the centiseconds string; callers observe the final
  `%1i:%02i:%02i` form.
- The helper returns the shared 0x751478 buffer.

Focused match: 100%, 36/36 instructions, with twelve clean masked operands.

This scratch compiles as C (`/TC`) with a local C-compatible `Time`
layout shell. C-mode MSVC 6.5 coalesces cdecl stack cleanup across the two
adjacent non-zero-branch `sprintf` calls, producing the native `add esp, 0x28`
after the second call.

2026-06-20 local C-view naming: the local timer shell is now
`TimeTrialTimeCView`. The shared `game_time.h` class is the right C++ owner,
but this `/TC` scratch deliberately keeps a C-compatible view.
The focused match stays exact at `100.00%`, `36/36`, with `12 ok` masked
operands, and the type report no longer advertises the local view as a
promotable local duplicate.

2026-07-11 ownership pass:

- Promoted the former method-only receiver view to the complete embedded
  `TimeTrial` owner. The exact formatter scratch deliberately remains `/TC` so
  VC6 retains the native coalesced `sprintf` cleanup; C++ callers now address
  the real owner directly without changing their codegen.

2026-07-12 cRTime ownership pass:

- Cross-port symbols recover the parameter owner as `cRTime`, so the local C
  shell and the shared C++ class now use `Time` vocabulary. This remains a
  naming-only change to the exact 0x18-byte layout.

2026-07-13 analysis propagation:

- The path-template Binary Ninja/IDA runtime now embeds the complete 0x330-byte
  `TimeTrial` at `+0xff25e0`, followed by the one-byte `PathManager` at
  `+0xff2910` and all 63 exact `PathPair` values at `+0xff2914`.
- The former `runtime_track_index` lane was a flattened field inside the
  TimeTrial extent, not an independent SubgameRuntime member.
- Binary Ninja preview verifies all boundaries and keeps
  `SubgameRuntime == 0x1272838`, then reverts. The formatter remains exact at
  36/36 instructions with all twelve operands clean.
