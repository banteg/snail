// read_current_display_resolution @ 0x4078b0 (cdecl)

extern "C" __declspec(dllimport) int __stdcall EnumDisplaySettingsA(char* device_name, int mode_num, void* dev_mode);

int* read_current_display_resolution(int* out_width, int* out_height)
{
    int dev_mode[39];

    if (EnumDisplaySettingsA(0, -1, dev_mode)) {
        *out_width = dev_mode[27];
        *out_height = dev_mode[28];
        return out_height;
    }

    *out_width = 640;
    *out_height = 480;
    return out_height;
}
