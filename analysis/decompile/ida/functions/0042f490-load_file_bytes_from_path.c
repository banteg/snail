/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_from_path @ 0x42f490 */
/* selector: load_file_bytes_from_path */

// Loads one filesystem path into caller-supplied or freshly allocated bytes, optionally returning the byte count through the extra output lanes.
void *__cdecl load_file_bytes_from_path(char *FileName, void *Buffer, int *a3, int ElementCount)
{
  #91 *v4; // eax
  FILE *v5; // esi
  int v7; // edi
  void *v8; // ebx
  char DstBuf[512]; // [esp+8h] [ebp-200h] BYREF

  v4 = fopen(FileName, Mode);
  v5 = v4;
  if ( v4 )
  {
    v7 = ElementCount;
    if ( !ElementCount )
      v7 = get_stream_length_preserve_position(v4);
    v8 = Buffer;
    if ( !Buffer )
      v8 = (void *)malloc(v7);
    fread(v8, 1, v7, v5);
    fclose(v5);
    if ( a3 )
      *a3 = v7;
    return v8;
  }
  else
  {
    _getcwd(DstBuf, 512);
    printf("WARNING:Cannot find file : %s (from %s)\n", FileName, DstBuf);
    return nullptr;
  }
}

