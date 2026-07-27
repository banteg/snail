/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_authored_view_height @ 0x433040 */
/* selector: get_authored_view_height */

// Exact Windows `RShellGetScreenHeight()` getter for the float-backed 480-style authored viewport height. Android and iOS preserve the RShell owner and `gG0ScreenHeight` vocabulary while using an integer-backed platform dimension.
float __cdecl get_authored_view_height()
{
  return g_authored_view_height;
}
