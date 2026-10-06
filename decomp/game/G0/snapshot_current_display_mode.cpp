// snapshot_current_display_mode @ 0x407850 (cdecl)

extern "C" __declspec(dllimport) int __stdcall EnumDisplaySettingsA(char* device_name, int mode_num, void* dev_mode);

extern char g_current_display_mode;

int snapshot_current_display_mode()
{
    return EnumDisplaySettingsA(0, -1, &g_current_display_mode);
}
