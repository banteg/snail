# get_archive_data_end

Exact 3/3-instruction Windows accessor for the second half of the global
`RShellScratch` workspace. The exact iOS `RShell.o` symbol is
`RShellMemoryScratch2()`; Windows returns `scratch + 0x200000` from its 4 MiB
allocation, while iOS returns `scratch + 0x280000` from its 5 MiB allocation.

The stable harness name is retained for status continuity, but the returned
pointer is a second workspace base, not an archive-data end sentinel.
