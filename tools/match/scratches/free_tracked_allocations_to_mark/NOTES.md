# free_tracked_allocations_to_mark

Windows tracked-allocation unwind helper at `0x431c70`. It repeatedly frees the
caller-visible pointer for the top allocation until
`g_tracked_allocation_stack.depth` reaches `.bookmark_depth`.

The three-word indexing is now expressed through the recovered owner as
`records[depth - 1].pointer + 4`: record zero begins at object `+0x0c`, so this
is the same address as the native `(&depth)[depth * 3] + 4` expression without
discarding the record ownership. The focused result remains exact at 15/15
instructions with all six masked operands resolved.

Android names the corresponding lifecycle edge `RShellMemoryUnBookmark()` and
uses the same top-record pointer unwind against its platform-specific
`cRShellMemory` layout. Together with `RShellMemoryBookmark()`, that independently
supports the bookmark/depth semantics without assuming the ports share every
field offset.
