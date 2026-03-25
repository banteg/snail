/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: abort_startup_with_3d_error @ 0x4088a0 */
/* selector: abort_startup_with_3d_error */

// Shows the native 3D-accelerator startup error dialog, terminates the shell process, and returns through the shared `cRBod` constructor on the static sentinel object.
void __noreturn abort_startup_with_3d_error()
{
  ((void (__stdcall *)(_DWORD, char *, char *, int))MessageBoxA)(0, Text, Caption, 48);
  exit_1(0);
}

