/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: archive_or_file_exists @ 0x430fd0 */
/* selector: archive_or_file_exists */

char __cdecl sub_430FD0(char *FileName, char a2)
{
  #91 *v3; // eax

  if ( !MEMORY[0x53C7F8] || a2 )
  {
    v3 = fopen(FileName, Mode);
    if ( !v3 )
      return 0;
    fclose(v3);
  }
  else if ( !find_archive_entry(FileName) )
  {
    report_warningf("Missing Dat File %s", FileName);
    return 0;
  }
  return 1;
}

