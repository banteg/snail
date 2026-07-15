# kill_subgoldy

Exact match: 100.00%, 6/6 instructions, one clean masked operand.

The helper hides both cached ghost sprites and clears Goldy's active render
flag. Its sole `update_times_up` caller discards EAX, whose terminal value is
only the last flag-clear residue. The matching source was already void; the
durable BN and IDA declarations now preserve the real thiscall `Player`
receiver instead of an inferred fastcall scalar result.
