/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_archive_data_end @ 0x431aa0 */
/* selector: get_archive_data_end */

// Windows RShellMemoryScratch2(): returns the second 2 MiB region of the global RShell scratch workspace at base +0x200000. Despite the stable harness name, this is a second workspace base rather than an end sentinel.
void *__cdecl get_archive_data_end()
{
  return (char *)g_archive_data_base + 0x200000;
}
