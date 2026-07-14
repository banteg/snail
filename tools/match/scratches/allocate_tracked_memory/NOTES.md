# allocate_tracked_memory

Guarded tracked allocator at 0x431b60. It allocates `size + 8` bytes, records
the backing block and guarded size on the global tracked-allocation stack, zeros
the guarded block, writes `de ad ba be` sentinels at both ends, adds the guarded
size to the global tracked byte total, and returns the caller-visible payload
at `block + 4`.

Focused match: 100%, 48/48 instructions, with seven clean masked operands.

The native shape mutates the `size` parameter to the guarded allocation size
before allocation and uses the `name` parameter directly for the tracked-stack
record. Spelling those as separate `guarded_size` and `label` locals makes VC6
compute through `eax` before saving callee-saved registers and passes the label
through `ecx`.

iOS `RShell.o` names the public contract `RShellMemoryMalloc(int, char*)`.
Windows adds the recovered guard bytes and allocation-stack accounting around
that size/label interface; iOS delegates its platform body directly to malloc.

The call now goes through the canonical `g_tracked_allocation_stack` owner at
`0x5108c0`, rather than recasting its first `depth` word into an object. This is
codegen-neutral: the focused result remains exact with all seven operands
resolved.
