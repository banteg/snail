# cRBorder::Init text overload @ 0x401d30

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes a void `thiscall` member with eight stack arguments and a
`cRBorder*` receiver. Android and iOS independently retain the corresponding
`cRBorder::Init(int, char*, int, float, float, tColour, int, float)` method in
`Border.o`; Windows passes the color as a pointer.

The body covers active-list insertion, tooltip ownership, flags, all four style
presets, text and layout state, highlighting, and construction of the three
owned slider children. Its backing `BorderRecord` lifecycle and every consumed
field are represented through the shared `cRBorder` view.

Focused VC6 result: **99.53%**, exact 429/429 instruction parity, prefix
74/429, with all 50 relocation operands audited and clean. The only difference
is an exchange between two anonymous `tColour` temporary stack slots; recorded
natural declaration/lifetime variants do not improve it.

The matcher source now uses the authored `Init` overload and exact VC6 symbol
`?Init@cRBorder@@QAEXHPADHMMPAUtColour@@HM@Z`;
`initialize_frontend_widget` remains only the stable scratch and Windows-address
identity.
