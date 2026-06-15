// probe_display_mode_count @ 0x407880 (cdecl)

extern "C" __declspec(dllimport) int __stdcall EnumDisplaySettingsA(char* device_name, int mode_num, void* dev_mode);

int probe_display_mode_count()
{
    char dev_mode[156];
    int mode_num = 0;
    int result;

    do {
        result = EnumDisplaySettingsA(0, mode_num, dev_mode);
        mode_num++;
    } while (result);

    return result;
}
