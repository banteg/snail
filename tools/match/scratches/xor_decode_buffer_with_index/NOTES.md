# xor_decode_buffer_with_index

High-score file byte obfuscation helper at 0x433010. It mutates the supplied
buffer in place by XORing each byte with its zero-based byte index.

Exact match: 100.00%, 15/15 instructions, no masked operands. The helper
returns the post-loop cursor in `eax`; current high-score callsites ignore that
return and only consume the in-place mutation.

2026-07-16 replay closure: both decompilers now retain the `char* bytes` and
signed byte-count contract, and paired health checks guard against the former
raw `arg1`/`arg2` view. The source remains exact at 15/15 instructions with no
masked operands.
