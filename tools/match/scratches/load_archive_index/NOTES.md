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
