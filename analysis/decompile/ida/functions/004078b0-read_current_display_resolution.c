/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_current_display_resolution @ 0x4078b0 */
/* selector: read_current_display_resolution */

// Reads the current desktop width and height into the supplied outputs, falling back to `640x480` if `EnumDisplaySettingsA` fails.
int *__cdecl read_current_display_resolution(int *out_width, int *out_height)
{
  _DWORD DevMode[39]; // [esp+0h] [ebp-9Ch] BYREF

  if ( ((int (__stdcall *)(_DWORD, int, _DWORD *))EnumDisplaySettingsA)(0, -1, DevMode) )
  {
    *out_width = DevMode[27];
    *out_height = DevMode[28];
    return out_height;
  }
  else
  {
    *out_width = 640;
    *out_height = 480;
    return out_height;
  }
}
