/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_current_directory_with_drive_fallback @ 0x430f30 */
/* selector: set_current_directory_with_drive_fallback */

// Wraps `SetCurrentDirectoryA`, retrying drive-qualified paths through the Win32 current-drive environment-variable fallback before emitting a plain debug message on failure.
int __cdecl sub_430F30(char *a1)
{
  const char *v1; // esi
  char Path; // [esp+4h] [ebp-104h] BYREF
  char v4[259]; // [esp+5h] [ebp-103h] BYREF

  v1 = a1;
  if ( a1 == (char *)&flt_4DFAFC[3] )
    return 0;
  if ( a1[1] == 58 )
  {
    Path = *a1;
    strcpy(v4, ":\\");
    _chdir(&Path);
    if ( !a1[2] || !a1[3] )
      return 0;
    v1 = a1 + 3;
  }
  if ( _chdir(v1) )
  {
    _getcwd(&v4[3], 256);
    report_messagef("ERROR: cannot find directory %s (from %s)\n", v1, &v4[3]);
    return 1;
  }
  return 0;
}

