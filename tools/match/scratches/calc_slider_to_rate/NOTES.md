# SubgameRuntime::calc_slider_to_rate @ 0x437e80

## 2026-07-26 mobile body match

The imported Android body preserves the exact authored method name
`cRSubGame::CalcSliderToRate(float)` and the complete Windows expression:
`x == 1.0 ? 1.1 : x * 0.90000004 + 0.2`. This is direct owner and body
evidence; no iOS mapping is claimed.

All three Windows callsites in `SubgameRuntime::build_subgame_level` move the
runtime receiver into `ECX` immediately before the call, even though the helper
does not read it. Android independently retains the symbol
`cRSubGame::CalcSliderToRate(cRSubGame*, float)`, confirming that this exact
rate transform belongs to the subgame object rather than being a standalone
stdcall helper.
