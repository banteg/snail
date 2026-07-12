# get_archive_data_base

Exact 2/2-instruction Windows accessor for the global `RShellScratch`
workspace. The exact iOS `RShell.o` symbol is `RShellMemoryScratch()` and
returns its platform's corresponding scratch base. The stable harness name is
retained, but this is transient shell workspace ownership rather than a loaded
DAT payload pointer.
