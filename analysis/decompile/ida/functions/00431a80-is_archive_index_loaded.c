/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_archive_index_loaded @ 0x431a80 */
/* selector: is_archive_index_loaded */

// Returns whether the global archive-index table has been initialized, so content loaders can decide between archive-backed reads and direct filesystem fallback.
unsigned __int8 __cdecl is_archive_index_loaded()
{
  return g_archive_index_records != nullptr;
}
