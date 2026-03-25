/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: write_file_bytes @ 0x431650 */
/* selector: write_file_bytes */

int __cdecl write_file_bytes(char *a1, void *Buffer, int ElementCount)
{
  char v4; // al
  int i; // edi
  #91 *v6; // esi
  char FileName[256]; // [esp+8h] [ebp-500h] BYREF
  char DstBuf[512]; // [esp+108h] [ebp-400h] BYREF
  char Path[512]; // [esp+308h] [ebp-200h] BYREF

  _getcwd(Path, 512);
  do
  {
    v4 = *a1;
    for ( i = 0; v4; ++a1 )
    {
      if ( v4 == 47 )
        break;
      if ( v4 == 92 )
        break;
      FileName[i] = v4;
      v4 = a1[1];
      ++i;
    }
    if ( *a1 == 47 || *a1 == 92 )
    {
      FileName[i] = 0;
      set_current_directory_with_drive_fallback(FileName);
      ++a1;
    }
  }
  while ( *a1 );
  FileName[i] = 0;
  v6 = fopen(FileName, aWb);
  if ( v6 )
  {
    fwrite(Buffer, 1, ElementCount, v6);
    fclose(v6);
  }
  else
  {
    _getcwd(DstBuf, 512);
    report_messagef("ERROR:Cannot save file : %s (from %s)\n", FileName, DstBuf);
  }
  return _chdir(Path);
}

