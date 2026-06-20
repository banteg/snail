# load_archive_index @ 0x4319c0

Loads and decrypts the archive index blob, rebases each entry path pointer from
file-relative offsets to live pointers, opens the backing dat stream, and leaves
`g_archive_index_records` null when no archive exists.

Current matcher result: 92.54%, 67/67 candidate instructions, 40/67 exact prefix,
13/13 masked references resolved.

Known residual: after the full-index decrypt call, native copies the allocated
index pointer from `esi` to `eax`, cleans up the batched call arguments, stores
`g_archive_index_records` through `eax`, then tests the entry count. The source
shape here still stores the global directly from `esi` before the stack cleanup,
then copies `esi` to `eax` before the rebase loop. The archive semantics and
entry-pointer rebase loop are otherwise aligned.

2026-06-20 shared header sync: `archive_index.h` now owns the `File` forward
declaration plus `g_archive_file` and typed `ArchiveIndex* g_archive_index_records`
externs. Removing duplicate local externs from the archive-index consumers is
codegen-neutral for the focused archive scratches; `load_archive_index` remains
92.54% with the same store/stack-cleanup residual.

2026-06-20 install-store retry: a typed `ArchiveIndex* installed_records`
temporary and a raw integer base temporary both preserve the 92.54% object.
Neither source shape moves VC6's `mov eax, esi` before stack cleanup or the
global store, reinforcing that the residual is local scheduling rather than the
source-level alias used for `g_archive_index_records`.

2026-06-20 archive-family audit: making the installed global the explicit owner
for the entry-count test (`g_archive_index_records = index; records =
g_archive_index_records; if (records->count > 0)`), using a chained assignment
(`g_archive_index_records = records = index`), and using the assignment result
inside the count test all compile identically at 92.54%. None recover native's
`mov eax, esi; add esp, 0x38; mov [global], eax` schedule. Keep the current
clear `records = index; g_archive_index_records = records` source shape.
