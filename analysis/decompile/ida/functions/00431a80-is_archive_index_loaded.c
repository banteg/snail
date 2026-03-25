/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_archive_index_loaded @ 0x431a80 */
/* selector: is_archive_index_loaded */

// Returns whether the global archive-index table has been initialized, so content loaders can decide between archive-backed reads and direct filesystem fallback.
bool sub_431A80()
{
  return MEMORY[0x53C7F8] != 0;
}

