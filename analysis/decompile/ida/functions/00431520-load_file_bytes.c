/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes @ 0x431520 */
/* selector: load_file_bytes */

// Exact Windows RShellLoadFile(char*, int*) overload that delegates to the three-argument loader with a null destination buffer.
void *__cdecl load_file_bytes(char *path, int *out_size)
{
  return load_file_bytes_from_archive_or_fs(path, nullptr, out_size);
}
