# xor_decode_buffer_with_index

High-score file byte obfuscation helper at 0x433010. It mutates the supplied
buffer in place by XORing each byte with its zero-based byte index.

Exact match: 100.00%, 15/15 instructions, no masked operands. The helper
returns the post-loop cursor in `eax`; current high-score callsites ignore that
return and only consume the in-place mutation.
