/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_from_path @ 0x42f490 */
/* selector: load_file_bytes_from_path */

// Windows implementation of authored `gRegisterLoadFile(char*, void*, int*, int)`: loads one filesystem path into caller-supplied or freshly allocated bytes, optionally returning the byte count through the extra output lanes. Android preserves the exact four-argument overload while delegating storage to its platform backend.
void *__cdecl load_file_bytes_from_path(char *file_name, void *buffer, int *out_size, int byte_count)
{
  File *v4; // eax
  File *v5; // esi
  int stream_length_preserve_position; // edi
  void *v8; // ebx
  char DstBuf[512]; // [esp+8h] [ebp-200h] BYREF

  v4 = fopen(file_name, mode);
  v5 = v4;
  if ( v4 != nullptr )
  {
    stream_length_preserve_position = byte_count;
    if ( byte_count == 0 )
      stream_length_preserve_position = get_stream_length_preserve_position(v4);
    v8 = buffer;
    if ( buffer == nullptr )
      v8 = malloc(stream_length_preserve_position);
    fread(v8, 1u, stream_length_preserve_position, v5);
    fclose(v5);
    if ( out_size != nullptr )
      *out_size = stream_length_preserve_position;
    return v8;
  }
  else
  {
    getcwd(DstBuf, 512);
    printf("WARNING:Cannot find file : %s (from %s)\n", file_name, DstBuf);
    return nullptr;
  }
}
