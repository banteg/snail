# allocate_tracked_memory

Guarded tracked allocator at 0x431b60. It allocates `size + 8` bytes, records
the backing block and guarded size on the global tracked-allocation stack, zeros
the guarded block, writes `de ad ba be` sentinels at both ends, adds the guarded
size to the global tracked byte total, and returns the caller-visible payload
at `block + 4`.

Current focused result: 91.67%, 48/48 candidate/target instructions, with seven
masked operands resolved. Remaining residual is register scheduling at entry
and at the tracked-stack push arguments: the target saves callee-saved registers
before loading `size` into `ebx` and uses `eax` for the label argument, while
this source computes via `eax` before the saves and uses `ecx` for the label.
