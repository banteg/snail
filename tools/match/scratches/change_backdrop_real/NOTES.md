# cRBackdrop::ChangeReal @ 0x410dc0

Exact Windows member: 30/30 instructions with its masked call operand clean.
Android and iOS independently preserve `cRBackdrop::ChangeReal()` and the same
state transition.

The method commits the pending primary and optional secondary textures, resets
zoom and calls `SetDistort` when the primary texture changes, then publishes
the pending flip and split-pair flags. `cRBackdrop::AI`, installed as the first
callback-table entry at construction, calls it when a change is queued.
