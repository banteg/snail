/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_config_file @ 0x42f540 */
/* selector: save_config_file */

char *__cdecl save_config_file(char *path, void *bytes, int byte_count)
{
  File *stream; // esi
  char cwd_buffer[512]; // [esp+4h] [ebp-200h] BYREF

  stream = fopen(path, aWb);
  if ( !stream )
    return getcwd(cwd_buffer, 512);
  fwrite(bytes, 1u, byte_count, stream);
  return (char *)fclose(stream);
}
