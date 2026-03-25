/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: log_startup_timestamp @ 0x406d30 */
/* selector: log_startup_timestamp */

int log_startup_timestamp()
{
  int Time; // [esp+0h] [ebp-Ch] BYREF

  _ftime(&Time);
  unknown_libname_6((#90 *)&Time);
  return sub_449C00();
}

