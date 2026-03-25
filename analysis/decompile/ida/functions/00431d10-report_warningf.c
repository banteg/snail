/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: report_warningf @ 0x431d10 */
/* selector: report_warningf */

// Formats one warning message with the native `* WARNING *` prefix and emits it through the shared debug-output path.
int report_warningf(char *Format, ...)
{
  char Buffer[4096]; // [esp+0h] [ebp-1000h] BYREF
  va_list ArgList; // [esp+1008h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  vsprintf(Buffer, Format, ArgList);
  sub_449C00();
  sub_449C00();
  return sub_449C00();
}

