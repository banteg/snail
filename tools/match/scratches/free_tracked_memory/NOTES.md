# free_tracked_memory

Guarded tracked free helper at 0x431bf0. It converts the caller payload pointer
back to the backing block, looks up and subtracts the guarded allocation size,
validates the `de ad ba be` sentinels at both ends, frees the backing block, and
removes the backing pointer from the tracked-allocation stack.

Current focused result: 95.35%, 43/43 candidate/target instructions, with nine
masked operands resolved. Remaining residual is entry scheduling only: this
source computes `pointer - 4` through `eax` before saving `esi`, while the target
saves `esi` first and then loads/subtracts the argument directly into `esi`.
