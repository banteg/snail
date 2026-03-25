/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_hide_system_cursor_flag @ 0x44c050 */
/* selector: set_hide_system_cursor_flag */

// Sets the shared latch that tells `update_mouse` whether to hide the OS cursor after the current pointer-region update.
char __cdecl sub_44C050(char a1)
{
  MEMORY[0x777D70] = a1;
  return a1;
}

