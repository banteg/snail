# Exact match

`kill_tip_widgets` matches exactly at 24/24 instructions. It is a Tip-owned
Windows helper over the same 0x20-byte object independently recovered from the
symbol-preserving iOS `cRTip::Init` and `cRTip::AI` bodies.

2026-07-18 durable decompiler replay: the exact 0x20-byte `Tip` owner and its
three `FrontendWidget*` fields now survive in both tracked decompilers. The
helper reads `tip->widget_{main,ok,disable}` directly and clears
`tip->active`; raw arguments, `void*` widget views, and root-address literals
are rejected by paired health checks.

## 2026-07-27 Android authored owner

The new Android corpus retains the missing symbol as `cRTip::UnInit()` and its
body independently confirms the Windows layout and operation sequence:

- `active` at +0x00;
- main, OK, and Disable border pointers at +0x0c, +0x10, and +0x14;
- unconditional main-border teardown;
- conditional teardown of both optional borders; and
- the final active-state clear.

Android and Windows both route all three kills through the root-owned
BorderManager. No `cRTip::UnInit()` export survives in the iOS corpus, so the
crosswalk deliberately records Android-only proof rather than manufacturing
an iOS mapping. The Windows method remains exact at 24/24 instructions.
