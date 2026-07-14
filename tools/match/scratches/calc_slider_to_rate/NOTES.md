# SubgameRuntime::calc_slider_to_rate @ 0x437e80

All three Windows callsites in `SubgameRuntime::build_subgame_level` move the
runtime receiver into `ECX` immediately before the call, even though the helper
does not read it. Android independently retains the symbol
`cRSubGame::CalcSliderToRate(cRSubGame*, float)`, confirming that this exact
rate transform belongs to the subgame object rather than being a standalone
stdcall helper.
