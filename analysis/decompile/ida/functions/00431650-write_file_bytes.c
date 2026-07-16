/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: write_file_bytes @ 0x431650 */
/* selector: write_file_bytes */

// Windows RShellSaveFile(char*, void*, int): walks intermediate directory components, writes the caller-owned byte range, and restores the original working directory.
int __cdecl write_file_bytes(char *path, void *bytes, int byte_count)
{
  char v4; // al
  int i; // edi
  File *stream; // esi
  char file_name[256]; // [esp+8h] [ebp-500h] BYREF
  char cwd_buffer[512]; // [esp+108h] [ebp-400h] BYREF
  char original_directory[512]; // [esp+308h] [ebp-200h] BYREF

  getcwd(original_directory, 512);
  do
  {
    v4 = *path;
    for ( i = 0; v4; ++path )
    {
      if ( v4 == 47 )
        break;
      if ( v4 == 92 )
        break;
      file_name[i] = v4;
      v4 = path[1];
      ++i;
    }
    if ( *path == 47 || *path == 92 )
    {
      file_name[i] = 0;
      set_current_directory_with_drive_fallback(file_name);
      ++path;
    }
  }
  while ( *path );
  file_name[i] = 0;
  stream = fopen(file_name, aWb);
  if ( stream )
  {
    fwrite(bytes, 1u, byte_count, stream);
    fclose(stream);
  }
  else
  {
    getcwd(cwd_buffer, 512);
    report_messagef("ERROR:Cannot save file : %s (from %s)\n", file_name, cwd_buffer);
  }
  return chdir(original_directory);
}
