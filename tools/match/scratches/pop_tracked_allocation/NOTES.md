# pop_tracked_allocation

Tracked-allocation stack pop helper at 0x431b30. It decrements the stack depth
first, checks whether the freed pointer was the top stack entry, and falls back
to a linear pointer search if the free order differs.

Current focused result: 66.67%, 25 candidate instructions versus 20 target
instructions, no masked operands. The semantic shape is recovered, but VC6 keeps
saving `edi` and hoists the first fallback-search load instead of emitting the
target's direct `cmp dword [ecx], esi` loop.
