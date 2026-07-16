/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_archive_data_base @ 0x431a90 */
/* selector: get_archive_data_base */

// Windows RShellMemoryScratch(): returns the base of the global 4 MiB RShell scratch workspace used by transient mesh, voice, object-definition, and render-buffer builders. It does not own the DAT payload.
void *__cdecl get_archive_data_base()
{
  return g_archive_data_base;
}
