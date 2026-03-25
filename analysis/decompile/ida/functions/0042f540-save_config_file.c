/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: save_config_file @ 0x42f540 */
/* selector: save_config_file */

char *__cdecl save_config_file(char *FileName, void *Buffer, int ElementCount)
{
  #91 *v3; // esi
  char DstBuf[512]; // [esp+4h] [ebp-200h] BYREF

  v3 = fopen(FileName, aWb);
  if ( !v3 )
    return _getcwd(DstBuf, 512);
  fwrite(Buffer, 1, ElementCount, v3);
  return (char *)fclose(v3);
}

