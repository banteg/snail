/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_config_file @ 0x42f540 */
/* selector: save_config_file */

// Windows implementation of authored `gRegisterSaveFile(char*, void*, int)`: writes the supplied byte span directly to the named path. Android and iOS preserve the exact three-argument Register.o symbol while using their platform file backends.
char *__cdecl save_config_file(char *file_name, void *bytes, int byte_count)
{
  File *stream; // esi
  char cwd_buffer[512]; // [esp+4h] [ebp-200h] BYREF

  stream = fopen(file_name, aWb);
  if ( stream == nullptr )
    return getcwd(cwd_buffer, 512);
  fwrite(bytes, 1u, byte_count, stream);
  return (char *)fclose(stream);
}
