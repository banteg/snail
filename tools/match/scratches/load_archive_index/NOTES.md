# load_archive_index @ 0x4319c0

Loads and decrypts the archive index blob, rebases each entry path pointer from
file-relative offsets to live pointers, opens the backing dat stream, and leaves
`g_archive_index_records` null when no archive exists.

Current matcher result: **100.00%**, 67/67 exact instructions, with all 14
masked references resolved.

The proof-grade source publishes the decoded allocation directly as
`g_archive_index_records`, then updates each typed `ArchiveEntry::path` in
place through that published owner. VC6 strength-reduces the typed entry loop
to the native 12-byte offset induction, including the otherwise elusive SIB
base/index order.

## 2026-08-13 exact typed-entry recovery

Both verified mobile bodies publish the decoded allocation directly to their
authored `gDat` owner before rebasing its path entries. Removing the separate
Windows `records` carrier first improved the focused result from **92.54%** to
**97.01%** and extended the exact prefix from 40 to 48 instructions. Expressing
the remaining rebase as the owned operation
`g_archive_index_records->entries[i].path += (int)g_archive_index_records`
then recovers the two scale-one SIB encodings exactly.

The final result is **100.00%**, 67/67 instructions, exact prefix 67, and all
14 references clean. This is a semantic ownership correction, not an address
or register coercion: the typed source is also simpler than the former manual
byte-offset load/store sequence.

## Supporting ownership evidence

- Android and iOS retain the exact authored `RShellDatInit(char*)` symbol in
  `RShell.o`. Both decode an archive index, publish it as `gDat`, rebase every
  entry path in place, and open the backing stream.
- `SerializedArchiveIndex` owns the decoded file-relative `path_offset` values
  until publication. The same allocation then becomes an `ArchiveIndex` whose
  12-byte `ArchiveEntry` records hold live `char* path` values.
- The shared archive header owns `ArchiveIndex* g_archive_index_records` and the
  authentic VC6 `FILE* g_archive_file`; the archive consumers use those same
  types, so the exact loop does not depend on a scratch-local layout alias.
- Binary Ninja and IDA replays retain distinct serialized header, decoded
  allocation, live index, rebased path, and stream lifetimes.
