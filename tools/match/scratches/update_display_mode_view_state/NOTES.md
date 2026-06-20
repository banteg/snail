# update_display_mode_view_state

Display-mode view-state updater at `0x412940`. It requires a current
`DisplayModeRecord`, samples the authored view width/height getters, consumes
view samples through `read_next_display_mode_view_sample`, and returns whether
display-mode state was available.

Exact match: 100.00%, 46/46 instructions, with all four masked operands
resolved.

2026-06-20 loop-shape fix: rewriting the sample retry as `while (1)` with
breaks for both the no-sample path and the changed `probe_count` path promoted
the scratch from 82.69% to exact. The earlier `goto sample_next` spelling
tail-duplicated the sample-call setup and delayed the second ignored x87 return
pop; the structured loop branches directly back to the call block like native.
