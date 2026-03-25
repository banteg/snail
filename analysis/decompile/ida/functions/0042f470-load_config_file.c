/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_config_file @ 0x42f470 */
/* selector: load_config_file */

void *__cdecl load_config_file(char *FileName, void *Buffer)
{
  return (void *)load_file_bytes_from_path(FileName, Buffer, 0, 0);
}

