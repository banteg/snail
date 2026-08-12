# xor_decode_buffer_with_index

High-score file byte obfuscation helper at 0x433010. It mutates the supplied
buffer in place by XORing each byte with its zero-based byte index.

Exact match: 100.00%, 15/15 instructions, no masked operands. The helper
leaves the post-loop cursor in `eax`; all four high-score callsites ignore that
incidental residue and only consume the in-place mutation.

## 2026-08-12 authored RShell contract

Android retains the exact exported symbol
`RShellScrambleFile(void*, int)`. Its body has the same signed positive-count
guard and XORs byte `i` with the low byte of `i`; only the ARM loop shape
keeps the base pointer instead of advancing a cursor. The symbol family and
the proved Windows neighbors on both sides recover `RShell.o` ownership.

The Android decompile is void, and live Windows callsite inspection confirms
that `load_high_scores_from_file` and all three calls in
`save_high_scores_and_config` immediately continue without consuming EAX.
Changing the Windows scratch from a synthetic `char*` return to the authored
`void RShellScrambleFile(void*, int)` contract is codegen-neutral: it remains
exact at 15/15 instructions with no masked operands. The Binary Ninja and IDA
replays now preserve that void-pointer ABI while retaining the stable matcher
name.

2026-07-16 replay closure first replaced the raw `arg1`/`arg2` view with a
provisional `char*` cursor and signed count. The authored recovery above
supersedes that pointer/return transcription while keeping the proved count.
