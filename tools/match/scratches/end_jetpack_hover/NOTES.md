# end_jetpack_hover @ 0x43a370

Small jetpack hover clamp helper.

- It is a `JetpackGaugeController` member that only acts while `state == 1`.
- If active and `progress < 0.94f`, it clamps `progress` to `0.94f`; otherwise
  it returns without side effects.
- 2026-06-18 BN/IDA sync: BN's raw prototype was `void __fastcall(int32_t*)`.
  Syncing it to `void __fastcall end_jetpack_hover(JetpackGaugeController*)`
  resolves `gauge->state` and `gauge->progress` in the tracked BN export.
