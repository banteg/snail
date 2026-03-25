/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: read_current_display_resolution @ 0x4078b0 */
/* selector: read_current_display_resolution */

// Reads the current desktop width and height into the supplied outputs, falling back to `640x480` if `EnumDisplaySettingsA` fails.
uint8_t *__cdecl read_current_display_resolution(uint8_t *a1, uint8_t *a2)
{
  _DWORD DevMode[39]; // [esp+0h] [ebp-9Ch] BYREF

  if ( ((int (__stdcall *)(_DWORD, int, _DWORD *))EnumDisplaySettingsA)(0, -1, DevMode) )
  {
    *(_DWORD *)a1 = DevMode[27];
    *(_DWORD *)a2 = DevMode[28];
    return a2;
  }
  else
  {
    *(_DWORD *)a1 = 640;
    *(_DWORD *)a2 = 480;
    return a2;
  }
}

