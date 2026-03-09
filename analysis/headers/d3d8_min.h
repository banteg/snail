#ifndef SNAIL_D3D8_MIN_H
#define SNAIL_D3D8_MIN_H

#include "win32_min.h"

/*
 * Minimal Direct3D 8 declarations for the callsites currently recovered in
 * `initialize_d3d8_device`. This is intentionally not a full SDK header.
 */

#define D3D_SDK_VERSION 220u
#define D3DADAPTER_DEFAULT 0u

#define D3DCREATE_SOFTWARE_VERTEXPROCESSING 0x00000020u
#define D3DCREATE_HARDWARE_VERTEXPROCESSING 0x00000040u

typedef DWORD D3DCOLOR;

typedef enum D3DDEVTYPE {
    D3DDEVTYPE_HAL = 1,
    D3DDEVTYPE_REF = 2,
    D3DDEVTYPE_SW = 3,
} D3DDEVTYPE;

typedef enum D3DFORMAT {
    D3DFMT_UNKNOWN = 0,
    D3DFMT_R5G6B5 = 23,
    D3DFMT_X1R5G5B5 = 24,
    D3DFMT_A1R5G5B5 = 25,
    D3DFMT_X8R8G8B8 = 22,
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_D16 = 80,
    D3DFMT_D24X8 = 77,
} D3DFORMAT;

typedef enum D3DMULTISAMPLE_TYPE {
    D3DMULTISAMPLE_NONE = 0,
} D3DMULTISAMPLE_TYPE;

typedef enum D3DSWAPEFFECT {
    D3DSWAPEFFECT_DISCARD = 1,
    D3DSWAPEFFECT_FLIP = 2,
    D3DSWAPEFFECT_COPY = 3,
    D3DSWAPEFFECT_COPY_VSYNC = 4,
} D3DSWAPEFFECT;

typedef struct D3DDISPLAYMODE {
    UINT Width;
    UINT Height;
    UINT RefreshRate;
    D3DFORMAT Format;
} D3DDISPLAYMODE;

typedef struct D3DPRESENT_PARAMETERS {
    UINT BackBufferWidth;
    UINT BackBufferHeight;
    D3DFORMAT BackBufferFormat;
    UINT BackBufferCount;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    D3DSWAPEFFECT SwapEffect;
    HWND hDeviceWindow;
    BOOL Windowed;
    BOOL EnableAutoDepthStencil;
    D3DFORMAT AutoDepthStencilFormat;
    DWORD Flags;
    UINT FullScreen_RefreshRateInHz;
    UINT FullScreen_PresentationInterval;
} D3DPRESENT_PARAMETERS;

typedef struct IDirect3DDevice8 IDirect3DDevice8;

typedef struct IDirect3D8Vtbl IDirect3D8Vtbl;
typedef struct IDirect3D8 IDirect3D8;

struct IDirect3D8Vtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IDirect3D8 *self, REFIID riid, void **out_object);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDirect3D8 *self);
    ULONG (STDMETHODCALLTYPE *Release)(IDirect3D8 *self);
    HRESULT (STDMETHODCALLTYPE *RegisterSoftwareDevice)(IDirect3D8 *self, void *init_function);
    UINT (STDMETHODCALLTYPE *GetAdapterCount)(IDirect3D8 *self);
    HRESULT (STDMETHODCALLTYPE *GetAdapterIdentifier)(IDirect3D8 *self, UINT adapter, DWORD flags, void *identifier);
    UINT (STDMETHODCALLTYPE *GetAdapterModeCount)(IDirect3D8 *self, UINT adapter);
    HRESULT (STDMETHODCALLTYPE *EnumAdapterModes)(IDirect3D8 *self, UINT adapter, UINT mode, D3DDISPLAYMODE *mode_out);
    HRESULT (STDMETHODCALLTYPE *GetAdapterDisplayMode)(IDirect3D8 *self, UINT adapter, D3DDISPLAYMODE *mode_out);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceType)(IDirect3D8 *self, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT display_format, D3DFORMAT backbuffer_format, BOOL windowed);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceFormat)(IDirect3D8 *self, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT adapter_format, DWORD usage, DWORD resource_type, D3DFORMAT check_format);
    HRESULT (STDMETHODCALLTYPE *CheckDeviceMultiSampleType)(IDirect3D8 *self, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT surface_format, BOOL windowed, D3DMULTISAMPLE_TYPE sample_type);
    HRESULT (STDMETHODCALLTYPE *CheckDepthStencilMatch)(IDirect3D8 *self, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT adapter_format, D3DFORMAT render_target_format, D3DFORMAT depth_stencil_format);
    HRESULT (STDMETHODCALLTYPE *GetDeviceCaps)(IDirect3D8 *self, UINT adapter, D3DDEVTYPE device_type, void *caps_out);
    HMONITOR (STDMETHODCALLTYPE *GetAdapterMonitor)(IDirect3D8 *self, UINT adapter);
    HRESULT (STDMETHODCALLTYPE *CreateDevice)(IDirect3D8 *self, UINT adapter, D3DDEVTYPE device_type, HWND focus_window, DWORD behavior_flags, D3DPRESENT_PARAMETERS *present_parameters, IDirect3DDevice8 **device_out);
};

struct IDirect3D8 {
    IDirect3D8Vtbl *lpVtbl;
};

IDirect3D8 *WINAPI Direct3DCreate8(UINT sdk_version);

#endif
