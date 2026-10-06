// restore_desktop_display_mode @ 0x407860 (cdecl)

extern "C" __declspec(dllimport) int __stdcall ChangeDisplaySettingsA(void* dev_mode, int flags);
extern "C" __declspec(dllimport) int __stdcall ShowCursor(int show);

int restore_desktop_display_mode()
{
    ChangeDisplaySettingsA(0, 0);
    return ShowCursor(1);
}
