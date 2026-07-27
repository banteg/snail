/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_authored_view_width @ 0x433030 */
/* selector: get_authored_view_width */

// Exact Windows `RShellGetScreenWidth()` getter for the float-backed 640-style authored viewport width. Android and iOS preserve the RShell owner and `gG0ScreenWidth` vocabulary while using an integer-backed platform dimension.
float __cdecl get_authored_view_width()
{
  return g_authored_view_width;
}
