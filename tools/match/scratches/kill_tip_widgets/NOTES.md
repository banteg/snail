# Exact match

`kill_tip_widgets` matches exactly at 24/24 instructions. It is a Tip-owned
Windows helper over the same 0x20-byte object independently recovered from the
symbol-preserving iOS `cRTip::Init` and `cRTip::AI` bodies. No distinct mobile
symbol survives for this helper, so it remains descriptively named rather than
being assigned a speculative authored symbol.

2026-07-18 durable decompiler replay: the exact 0x20-byte `Tip` owner and its
three `FrontendWidget*` fields now survive in both tracked decompilers. The
helper reads `tip->widget_{main,ok,disable}` directly and clears
`tip->active`; raw arguments, `void*` widget views, and root-address literals
are rejected by paired health checks.
