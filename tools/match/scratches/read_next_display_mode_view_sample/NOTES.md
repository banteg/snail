# read_next_display_mode_view_sample

Display-mode/view-sample iterator at `0x407930`. During the first two probes it
returns the current display-mode dimensions from the `DisplayModeRecord`
pointer. After that it pops queued 16-byte view samples from the state tail.

2026-07-24 ownership replay: Binary Ninja and IDA now share the exact
`DisplayModeRecord`, `DisplayModeViewSample`, and minimum `DisplayModeState`
prefix. The code directly proves the two counters at `+0/+4`, the current-mode
pointer at `+8`, and one sample at `+0xc`, for a minimum extent of `0x1c`.
IDA's old `_DWORD[60]` annotation merely filled the otherwise-unowned gap up
to `g_mouse_wheel_delta`; it does not prove a sample capacity. The replay
therefore leaves `0x4df9fc..0x4dfad0` unclaimed rather than inventing fourteen
samples.
