/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: delete_file_path_with_directory_walk @ 0x431540 */
/* selector: delete_file_path_with_directory_walk */

// Deletes one filesystem path after walking each parent directory component through the shared current-directory helper, mirroring the save-path builder beside it; used by the temporary BASS DLL teardown path.
int __cdecl sub_431540(char *a1)
{
  char v2; // al
  int i; // edi
  #91 *v4; // esi
  char FileName[256]; // [esp+8h] [ebp-500h] BYREF
  char DstBuf[512]; // [esp+108h] [ebp-400h] BYREF
  char Path[512]; // [esp+308h] [ebp-200h] BYREF

  _getcwd(Path, 512);
  do
  {
    v2 = *a1;
    for ( i = 0; v2; ++a1 )
    {
      if ( v2 == 47 )
        break;
      if ( v2 == 92 )
        break;
      FileName[i] = v2;
      v2 = a1[1];
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
  v4 = fopen(FileName, aWb);
  if ( v4 )
  {
    report_messagef("*Deleting file* :%s\n", FileName);
    fclose(v4);
    if ( remove(FileName) == -1 )
      report_messagef("ERROR:Cannot delete file : %s (from %s)\n", FileName, DstBuf);
  }
  else
  {
    _getcwd(DstBuf, 512);
    report_messagef("ERROR:Cannot delete file : %s (from %s)\n", FileName, DstBuf);
  }
  return _chdir(Path);
}

