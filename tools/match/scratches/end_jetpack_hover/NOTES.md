# end_jetpack_hover @ 0x43a370

Exact `cRSubHover::End()` hover clamp helper.

- It is a `SubHover` member that only acts while
  `state == SUB_HOVER_STATE_ACTIVE`.
- If active and `progress < 0.94f`, it clamps `progress` to `0.94f`; otherwise
  it returns without side effects.
- 2026-06-18 BN/IDA sync: BN's raw prototype was `void __fastcall(int32_t*)`.
  Syncing it to `void __thiscall end_jetpack_hover(SubHover*)`
  resolves `gauge->state` and `gauge->progress` in the tracked BN export.
- Android independently exports `cRSubHover::End()` and performs the same
  state test and 0.94 clamp at identical owner offsets. Focused Windows remains
  exact at 9/9 instructions.

## 2026-07-14 hover lifecycle ownership

The clamp gate now consumes the typed active state rather than raw value one.
Focused output remains exact at 9/9 instructions with its operand clean.

## 2026-07-18 focused lifecycle replay

The durable BN and IDA replay now names the function at 0x43a370 and verifies
the exact 0x214-byte `SubHover` owner before applying the authored void member
ABI. Both tracked artifacts render `state`, `progress`, and
`SUB_HOVER_STATE_ACTIVE`; the stale scalar/gauge view is guarded out. The
matcher remains exact at 9/9 instructions with its operand clean.
