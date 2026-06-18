// abort_startup_with_3d_error @ 0x4088a0 (cdecl, noreturn)

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    void* hwnd, char* text, char* caption, unsigned int type);
extern "C" __declspec(noreturn) void exit(int code);

void abort_startup_with_3d_error()
{
    MessageBoxA(
        0,
        "Snail Mail failed to start.\nPlease make sure you have at least\na 32 Meg 3D Hardware Accelerated Card \nand the latest DirectX drivers.",
        "ERROR",
        0x30);
    exit(0);
}
