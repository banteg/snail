/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: archive_or_file_exists @ 0x430fd0 */
/* selector: archive_or_file_exists */

// Windows RShellFindFile(char*, bool): checks the loaded DAT index unless the boolean formal forces a direct filesystem probe.
unsigned __int8 __cdecl archive_or_file_exists(char *path, unsigned __int8 force_filesystem)
{
  File *v3; // eax

  if ( !g_archive_index_records || force_filesystem )
  {
    v3 = fopen(path, Mode);
    if ( !v3 )
      return 0;
    fclose(v3);
  }
  else if ( !find_archive_entry(path) )
  {
    report_warningf("Missing Dat File %s", path);
    return 0;
  }
  return 1;
}
