# free_tracked_memory

Guarded tracked free helper at 0x431bf0. It converts the caller payload pointer
back to the backing block, looks up and subtracts the guarded allocation size,
validates the `de ad ba be` sentinels at both ends, frees the backing block, and
removes the backing pointer from the tracked-allocation stack.

Focused match: 100%, 43/43 instructions, with nine clean masked operands.

The public argument remains `void*` because callers pass object-specific
buffers. The native entry shape comes from mutating the parameter to the guarded
backing block before taking the typed byte view for sentinel checks; spelling the
adjustment as a separate `char*` initializer makes VC6 compute `pointer - 4`
through `eax` before saving `esi`.

iOS `RShell.o` names the public contract `RShellMemoryFree(void*)`. Windows
retains the same caller-owned pointer interface while adding guard validation
and tracked-stack removal. Exact and near-exact callers now declare the helper
`void`; the broad `initialize_intro_screen` relationship scratch still returns
its incidental `eax` and is left for a dedicated `cRIntro::Init` ABI audit.
