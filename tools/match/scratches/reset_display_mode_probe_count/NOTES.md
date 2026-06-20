# reset_display_mode_probe_count

Tiny `DisplayModeState` method at `0x407920`. The window proc calls it after
restoring from minimization, clearing the probe count used by the display-mode
view-sample reader.
