/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: report_messagef @ 0x431d60 */
/* selector: report_messagef */

// Formats and emits one plain debug message without the warning prefix; archive/file loading paths use it for missing-file notices.
int report_messagef(char *Format, ...)
{
  char Buffer[4096]; // [esp+0h] [ebp-1000h] BYREF
  va_list ArgList; // [esp+1008h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  vsprintf(Buffer, Format, ArgList);
  return sub_449C00();
}

