# Authored owner — `cRWarning::UnInit`

Android exports `cRWarning::UnInit()` and calls it from
`cRSubGame::UnInit()`, matching the Windows SubGame teardown edge. The exact
Windows method releases the border at `Warning +0x0c`; the wider Android owner
stores its border at +0x14.

2026-07-11 focused Wibo verifies an exact 100.00% match, 6/6 instructions,
with two clean masked operands.
