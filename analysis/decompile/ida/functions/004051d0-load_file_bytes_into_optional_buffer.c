/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_into_optional_buffer @ 0x4051d0 */
/* selector: load_file_bytes_into_optional_buffer */

// Loads one filesystem file into the caller-supplied buffer when present, otherwise allocates a new buffer, and optionally returns the byte length through the out parameter.
void *__cdecl load_file_bytes_into_optional_buffer(char *FileName, void *Buffer, #83 *a3)
{
  #91 *v3; // eax
  FILE *v4; // esi
  int stream_length_preserve_position; // eax
  void *v7; // ebx
  int v8; // edi
  char DstBuf[512]; // [esp+8h] [ebp-200h] BYREF

  v3 = fopen(FileName, Mode);
  v4 = v3;
  if ( v3 )
  {
    stream_length_preserve_position = get_stream_length_preserve_position(v3);
    v7 = Buffer;
    v8 = stream_length_preserve_position;
    if ( !Buffer )
      v7 = (void *)malloc(stream_length_preserve_position);
    fread(v7, 1, v8, v4);
    fclose(v4);
    if ( a3 )
      *(_DWORD *)a3 = v8;
    return v7;
  }
  else
  {
    _getcwd(DstBuf, 512);
    printf("WARNING:Cannot find file : %s (from %s)\n", FileName, DstBuf);
    return nullptr;
  }
}

