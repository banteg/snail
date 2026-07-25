# reset_display_mode_probe_count

Tiny `DisplayModeState` method at `0x407920`. The window proc calls it after
restoring from minimization, clearing the probe count used by the display-mode
view-sample reader.

2026-07-24 ownership replay: the native two-instruction body and its exact
window-proc callsite reject Binary Ninja's colliding PortablePDB
`pdb_internal::Array<PortablePDB::MethodInfo>::reset` name. Both analysis
databases now preserve the display-state receiver and `probe_count` field.
