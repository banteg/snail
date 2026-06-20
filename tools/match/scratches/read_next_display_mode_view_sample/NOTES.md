# read_next_display_mode_view_sample

Display-mode/view-sample iterator at `0x407930`. During the first two probes it
returns the current display-mode dimensions from the `DisplayModeRecord`
pointer. After that it pops queued 16-byte view samples from the state tail.
