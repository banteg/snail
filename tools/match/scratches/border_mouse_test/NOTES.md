# cRBorder::MouseTest @ 0x404580

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes an unsigned-byte `thiscall` member, while Android and iOS
independently retain `cRBorder::MouseTest()` in `Border.o`.

Ordinary widgets test the player-zero cursor against padded layout bounds.
Texture-backed widgets map the cursor into a borrowed `TgaImageView`, clamp the
sample coordinates, and accept a zero mask byte. The sprite manager getter,
cursor owner, TGA layout, and relevant `cRBorder` fields are independently
corroborated by exact siblings and both mobile bodies.

Focused VC6 result: **98.29%**, exact 117/117 instruction parity, prefix 73/117,
with all five relocation operands audited and clean. Native and candidate differ
only in which dead multiplicand register retains the final row product; 43
recorded natural source forms leave that isolated choice unchanged or regress.

The matcher source now uses the authored `MouseTest` method and exact VC6 symbol
`?MouseTest@cRBorder@@QAEEXZ`; `border_mouse_test` remains only the stable
scratch and Windows-address identity.
