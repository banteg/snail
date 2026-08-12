# cRBackdrop::Change @ 0x410d50

Exact Windows member: 34/34 instructions with no masked operands. The exact
`cRLandscape*` and `bool` signature also preserves the 123/123-instruction
`cRLandscapeManager::Init` caller.

Android and iOS independently preserve
`cRBackdrop::Change(cRLandscape*, bool)`. Windows constructs the receiver at
`GameRoot +0x4ec10`, installs the backdrop callback table there, and all nine
native callsites use that same embedded owner.

The method stages the landscape texture at `cRLandscape +0x84`, its split-pair
flag at `+0x88`, and `Distort:` value at `+0x120`. A nonzero texture queues the
primary texture and optional adjacent secondary texture; a zero texture clears
the persistent render gate without overwriting the pending values.
