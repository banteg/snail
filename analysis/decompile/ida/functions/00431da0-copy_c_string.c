/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_c_string @ 0x431da0 */
/* selector: copy_c_string */

// Void Windows `RTextCopy(char*, char*)`: copies one NUL-terminated C string into the destination buffer. Android and iOS preserve the authored RShell.o name, body, and placement at the head of the contiguous RText helper family.
void __cdecl copy_c_string(char *destination, char *source)
{
  char v4; // dl

  do
  {
    *destination = *source;
    v4 = *source;
    ++destination;
    ++source;
  }
  while ( v4 != 0 );
}
