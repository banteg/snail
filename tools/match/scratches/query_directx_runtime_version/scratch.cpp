// query_directx_runtime_version @ 0x44afc0 (cdecl)

struct DirectDrawSurface {
    virtual int __stdcall QueryInterface(void* iid, void** out_object) = 0;
    virtual int __stdcall AddRef() = 0;
    virtual int __stdcall Release() = 0;
};

struct DirectDraw {
    virtual int __stdcall QueryInterface(void* iid, void** out_object) = 0;
    virtual int __stdcall AddRef() = 0;
    virtual int __stdcall Release() = 0;
    virtual int __stdcall Compact() = 0;
    virtual int __stdcall CreateClipper(int flags, void** out_clipper, void* outer_unknown) = 0;
    virtual int __stdcall CreatePalette(
        int flags, void* entries, void** out_palette, void* outer_unknown) = 0;
    virtual int __stdcall CreateSurface(
        void* surface_desc, DirectDrawSurface** out_surface, void* outer_unknown) = 0;
    virtual int __stdcall DuplicateSurface(DirectDrawSurface* source, DirectDrawSurface** out_surface) = 0;
    virtual int __stdcall EnumDisplayModes(
        int flags, void* surface_desc, void* context, void* callback) = 0;
    virtual int __stdcall EnumSurfaces(
        int flags, void* surface_desc, void* context, void* callback) = 0;
    virtual int __stdcall FlipToGDISurface() = 0;
    virtual int __stdcall GetCaps(void* driver_caps, void* hel_caps) = 0;
    virtual int __stdcall GetDisplayMode(void* surface_desc) = 0;
    virtual int __stdcall GetFourCCCodes(int* count, int* codes) = 0;
    virtual int __stdcall GetGDISurface(DirectDrawSurface** out_surface) = 0;
    virtual int __stdcall GetMonitorFrequency(int* frequency) = 0;
    virtual int __stdcall GetScanLine(int* scan_line) = 0;
    virtual int __stdcall GetVerticalBlankStatus(int* status) = 0;
    virtual int __stdcall Initialize(void* guid) = 0;
    virtual int __stdcall RestoreDisplayMode() = 0;
    virtual int __stdcall SetCooperativeLevel(int hwnd, unsigned int flags) = 0;
};

struct DirectMusic {
    virtual int __stdcall QueryInterface(void* iid, void** out_object) = 0;
    virtual int __stdcall AddRef() = 0;
    virtual int __stdcall Release() = 0;
};

typedef int (__stdcall* DirectDrawCreateFn)(
    void* guid, DirectDraw** out_direct_draw, void* outer_unknown);
typedef int (__stdcall* DirectDrawCreateExFn)(
    void* guid, void** out_direct_draw, void* iid, void* outer_unknown);

extern char g_iid_idirectmusic; // data_49aff0
extern char g_clsid_directmusic; // data_49b000
extern char g_iid_idirectdrawsurface4; // data_49b0d0
extern char g_iid_idirectdrawsurface3; // data_49b0e0
extern char g_iid_idirectdraw7; // data_49b0f0
extern char g_iid_idirectdraw2; // data_49b100

extern "C" __declspec(dllimport) int __stdcall GetProcAddress(int module, char* name);
extern "C" __declspec(dllimport) int __stdcall LoadLibraryA(char* library_name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(int module);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(char* text);
extern "C" __declspec(dllimport) int __stdcall CoCreateInstance(
    void* clsid, void* outer_unknown, unsigned int context, void* iid, void** out_object);
extern "C" __declspec(dllimport) int __stdcall CoInitialize(void* reserved);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize();

int query_directx_runtime_version()
{
    DirectDraw* direct_draw = 0;
    DirectDraw* direct_draw2 = 0;
    DirectDrawSurface* surface = 0;
    DirectDrawSurface* surface3 = 0;
    DirectMusic* direct_music;
    DirectDrawSurface* surface4 = 0;
    DirectDraw* direct_draw7;
    unsigned int surface_desc[0x1b];

    int ddraw_module = LoadLibraryA("DDRAW.DLL");
    if (ddraw_module == 0) {
        OutputDebugStringA("Couldn't LoadLibrary DDraw\r\n");
        return 0;
    }

    DirectDrawCreateFn direct_draw_create =
        (DirectDrawCreateFn)GetProcAddress(ddraw_module, "DirectDrawCreate");
    if (direct_draw_create == 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't GetProcAddress DirectDrawCreate\r\n");
        return 0;
    }

    if (direct_draw_create(0, &direct_draw, 0) < 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't create DDraw\r\n");
        return 0;
    }

    if (direct_draw->QueryInterface(&g_iid_idirectdraw2, (void**)&direct_draw2) < 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't QI DDraw2\r\n");
        return 0x100;
    }
    direct_draw2->Release();

    int dinput_module = LoadLibraryA("DINPUT.DLL");
    if (dinput_module == 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't LoadLibrary DInput\r\n");
        return 0x200;
    }

    if (GetProcAddress(dinput_module, "DirectInputCreateA") == 0) {
        FreeLibrary(dinput_module);
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't GetProcAddress DInputCreate\r\n");
        return 0x200;
    }
    FreeLibrary(dinput_module);

    for (int index = 0; index < 0x1b; ++index) {
        surface_desc[index] = 0;
    }
    surface_desc[0] = 0x6c;
    surface_desc[1] = 1;
    surface_desc[0x1a] = 0x200;

    if (direct_draw->SetCooperativeLevel(0, 8) < 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't Set coop level\r\n");
        return 0;
    }

    if (direct_draw->CreateSurface(surface_desc, &surface, 0) < 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't CreateSurface\r\n");
        return 0;
    }

    if (surface->QueryInterface(&g_iid_idirectdrawsurface3, (void**)&surface3) < 0) {
        surface->Release();
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't QI DDS3\r\n");
        return 0x300;
    }
    surface3->Release();

    if (surface->QueryInterface(&g_iid_idirectdrawsurface4, (void**)&surface4) < 0) {
        surface->Release();
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't QI DDS4\r\n");
        return 0x500;
    }
    surface4->Release();
    surface->Release();
    direct_draw->Release();

    direct_music = 0;
    CoInitialize(0);
    if (CoCreateInstance(&g_clsid_directmusic, 0, 1, &g_iid_idirectmusic,
            (void**)&direct_music) < 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't create CLSID_DirectMusic\r\n");
        return 0x600;
    }
    direct_music->Release();
    CoUninitialize();

    DirectDrawCreateExFn direct_draw_create_ex =
        (DirectDrawCreateExFn)GetProcAddress(ddraw_module, "DirectDrawCreateEx");
    if (direct_draw_create_ex == 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't GetProcAddress DirectDrawCreateEx\r\n");
        return 0x601;
    }

    if (direct_draw_create_ex(0, (void**)&direct_draw7, &g_iid_idirectdraw7, 0) < 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't DirectDrawCreateEx\r\n");
        return 0x601;
    }
    direct_draw7->Release();

    int d3d8_module = LoadLibraryA("D3D8.DLL");
    if (d3d8_module == 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't LoadLibrary D3D8.DLL\r\n");
        return 0x700;
    }

    int dpnhpast_module = LoadLibraryA("dpnhpast.dll");
    if (dpnhpast_module == 0) {
        FreeLibrary(dpnhpast_module);
        OutputDebugStringA("Couldn't LoadLibrary dpnhpast.dll\r\n");
        return 0x800;
    }

    FreeLibrary(ddraw_module);
    FreeLibrary(d3d8_module);
    return 0x801;
}
