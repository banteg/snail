/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: probe_display_mode_count @ 0x407880 */
/* selector: probe_display_mode_count */

// Walks `EnumDisplaySettingsA` until it fails and returns the terminal result, which the startup path uses while gathering desktop display capabilities.
int probe_display_mode_count()
{
  int v0; // esi
  int result; // eax
  _BYTE DevMode[156]; // [esp+8h] [ebp-9Ch] BYREF

  v0 = 0;
  do
    result = ((int (__stdcall *)(_DWORD, int, _BYTE *))EnumDisplaySettingsA)(0, v0++, DevMode);
  while ( result );
  return result;
}

