// query_directx_runtime_version @ 0x44afc0 (cdecl)

#include <windows.h>
#include <ddraw.h>

typedef HRESULT (WINAPI* DirectDrawCreateFn)(
    GUID* guid, IDirectDraw** out_direct_draw, IUnknown* outer_unknown);
typedef HRESULT (WINAPI* DirectDrawCreateExFn)(
    GUID* guid, void** out_direct_draw, REFIID iid, IUnknown* outer_unknown);

extern IID g_iid_idirectmusic; // data_49aff0
extern CLSID g_clsid_directmusic; // data_49b000
extern IID g_iid_idirectdrawsurface4; // data_49b0d0
extern IID g_iid_idirectdrawsurface3; // data_49b0e0
extern IID g_iid_idirectdraw7; // data_49b0f0
extern IID g_iid_idirectdraw2; // data_49b100

int query_directx_runtime_version()
{
    IDirectDraw* direct_draw = 0;
    IUnknown* direct_draw2 = 0;
    IDirectDrawSurface* surface = 0;
    IUnknown* surface3 = 0;
    IUnknown* direct_music;
    IUnknown* surface4 = 0;
    IUnknown* direct_draw7;
    DDSURFACEDESC surface_desc;

    HMODULE ddraw_module = LoadLibraryA("DDRAW.DLL");
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

    if (direct_draw->QueryInterface(g_iid_idirectdraw2, (void**)&direct_draw2) < 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't QI DDraw2\r\n");
        return 0x100;
    }
    direct_draw2->Release();

    HMODULE dinput_module = LoadLibraryA("DINPUT.DLL");
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

    for (int index = 0; index < sizeof(surface_desc) / sizeof(DWORD); ++index) {
        ((DWORD*)&surface_desc)[index] = 0;
    }
    surface_desc.dwSize = sizeof(surface_desc);
    surface_desc.dwFlags = DDSD_CAPS;
    surface_desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    if (direct_draw->SetCooperativeLevel(0, 8) < 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't Set coop level\r\n");
        return 0;
    }

    if (direct_draw->CreateSurface(&surface_desc, &surface, 0) < 0) {
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't CreateSurface\r\n");
        return 0;
    }

    if (surface->QueryInterface(g_iid_idirectdrawsurface3, (void**)&surface3) < 0) {
        surface->Release();
        direct_draw->Release();
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't QI DDS3\r\n");
        return 0x300;
    }
    surface3->Release();

    if (surface->QueryInterface(g_iid_idirectdrawsurface4, (void**)&surface4) < 0) {
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
    if (CoCreateInstance(g_clsid_directmusic, 0, 1, g_iid_idirectmusic,
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

    if (direct_draw_create_ex(0, (void**)&direct_draw7, g_iid_idirectdraw7, 0) < 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't DirectDrawCreateEx\r\n");
        return 0x601;
    }
    direct_draw7->Release();

    HMODULE d3d8_module = LoadLibraryA("D3D8.DLL");
    if (d3d8_module == 0) {
        FreeLibrary(ddraw_module);
        OutputDebugStringA("Couldn't LoadLibrary D3D8.DLL\r\n");
        return 0x700;
    }

    HMODULE dpnhpast_module = LoadLibraryA("dpnhpast.dll");
    if (dpnhpast_module == 0) {
        FreeLibrary(dpnhpast_module);
        OutputDebugStringA("Couldn't LoadLibrary dpnhpast.dll\r\n");
        return 0x800;
    }

    FreeLibrary(ddraw_module);
    FreeLibrary(d3d8_module);
    return 0x801;
}
