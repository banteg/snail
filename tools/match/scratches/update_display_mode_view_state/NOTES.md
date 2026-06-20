# update_display_mode_view_state

Display-mode view-state updater at `0x412940`. It requires a current
`DisplayModeRecord`, samples the authored view width/height getters, consumes
view samples through `read_next_display_mode_view_sample`, and returns whether
display-mode state was available.

Initial scratch result: 82.69%, with all four masked operands resolved. The
remaining residual is source-shape/codegen rather than unknown references:
native pops the second authored-height x87 return before setting up the sample
call, and it branches directly back to the sample call while this source shape
tail-duplicates the call block.
