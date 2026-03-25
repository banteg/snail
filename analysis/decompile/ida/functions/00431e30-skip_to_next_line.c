/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: skip_to_next_line @ 0x431e30 */
/* selector: skip_to_next_line */

// Advances the caller-owned text cursor to the next line break and then steps once more so the cursor starts on the following line.
_BYTE *__cdecl sub_431E30(_BYTE **a1)
{
  _BYTE *result; // eax

  for ( result = *a1; *result; *a1 = ++result )
  {
    result = *a1;
    if ( **a1 == 10 )
      break;
  }
  ++*a1;
  return result;
}

