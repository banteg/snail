# reset_tooltip @ 0x403be0

The exact embedded tooltip reset releases its borrowed widget through the
root-owned `GameRoot::border_manager`, clears the handle, and returns to state
1. The root-owner spelling remains exact at 16/16 instructions with two clean
operands.
