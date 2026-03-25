/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: restore_desktop_display_mode @ 0x407860 */
/* selector: restore_desktop_display_mode */

// Restores the desktop display mode with ChangeDisplaySettingsA(nullptr, 0) and makes the OS cursor visible again. The startup loop and deactivate path use it when leaving fullscreen presentation.
int restore_desktop_display_mode()
{
  ((void (__stdcall *)(_DWORD, _DWORD))ChangeDisplaySettingsA)(0, 0);
  return ((int (__stdcall *)(int))ShowCursor)(1);
}

