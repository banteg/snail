/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: snapshot_current_display_mode @ 0x407850 */
/* selector: snapshot_current_display_mode */

// Reads the current desktop display mode into the shared `DEVMODEA` buffer at `data_4df868` before fullscreen or pointer-scaling setup.
int snapshot_current_display_mode()
{
  return ((int (__stdcall *)(_DWORD, int, void *))EnumDisplaySettingsA)(0, -1, &MEMORY[0x4DF868]);
}

