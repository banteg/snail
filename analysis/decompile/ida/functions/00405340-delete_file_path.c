/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: delete_file_path @ 0x405340 */
/* selector: delete_file_path */

// Deletes one filesystem path; used by the archive rebuild pass to remove the old archive and temporary extracted PNG.
int __cdecl sub_405340(char *FileName)
{
  return remove(FileName);
}

