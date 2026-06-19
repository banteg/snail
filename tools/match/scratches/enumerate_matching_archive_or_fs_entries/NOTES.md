# Scratch status

Initial structure-first scratch for `enumerate_matching_archive_or_fs_entries @ 0x431740`.

Focused matcher result: 49.60%, 189 candidate instructions versus 182 target
instructions, 0-instruction prefix, and 23 clean masked operands.

Recovered behavior:

- if the DAT archive index is loaded, scan `ArchiveIndex` records;
- match `directory` against the archive path prefix case-insensitively, then require a `/`;
- apply the simple `*` wildcard pattern to the basename;
- copy matching basenames into 128-byte output slots and publish the count through `out_count`;
- otherwise save cwd, try to enter the requested directory, enumerate filesystem matches with `_findfirst`/`_findnext`, then restore cwd.

The native does not close the find handle in this routine. The scratch keeps that behavior.

Retained source-shape choices:

- model the function as `void`; callers ignore `eax`, and the observed return values are incidental leftovers from the archive pointer, count, or `chdir`;
- keep `_finddata_t::name` at `+0x14`, matching the native copies from the stack record;
- keep the archive prefix comparison inline, but call the exact `ascii_upper_if_lowercase` helper for wildcard matching;
- curate `g_enumerated_entry_count`, `_findfirst`, and `_findnext` in `analysis/symbols/gameplay-references.json` after BN confirmed the xrefs and wrapper behavior.

Remaining source-shape debt:

- the scratch spills the archive index into `ebx` for the whole function and reserves a `0x328` frame, while native loads `g_archive_index_records` into `eax` before frame setup and only saves `ebx` inside the archive loop;
- the wildcard loop is semantically correct but still differs in register scheduling and branch layout around `*`.

Rejected probes:

- branching to the filesystem path before clearing `g_enumerated_entry_count` regressed to 34.41%;
- reloading `g_archive_index_records` directly in the archive loop regressed to 37.84%;
- default C++ mode emitted the same code as explicit `/TC`, so the scratch keeps the clearer C-mode build.
