/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: report_errorf @ 0x431cc0 */
/* selector: report_errorf */

// Formats and emits one fatal-style engine error message with a varargs payload. Runtime and content-loading paths use it for hard failures such as missing hotspot textures, parcel-pool exhaustion, and invalid track segment lengths.
int report_errorf(char *Format, ...)
{
  char Buffer[4096]; // [esp+0h] [ebp-1000h] BYREF
  va_list ArgList; // [esp+1008h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  vsprintf(Buffer, Format, ArgList);
  sub_449C00();
  sub_449C00();
  return sub_449C00();
}

