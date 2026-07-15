#ifndef SNAIL_BN_IMPORT_H
#define SNAIL_BN_IMPORT_H

/*
 * Flattened Binary Ninja import header.
 *
 * Binary Ninja's header importer does not reliably resolve sibling includes
 * when importing from a file, so this entrypoint intentionally inlines the
 * small handwritten declarations we maintain in the split `*_min.h` files.
 */

/* win32_min.h */

#define WINAPI
#define CALLBACK
#define STDMETHODCALLTYPE

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef int LONG;
typedef unsigned int ULONG;
typedef LONG HRESULT;
typedef void VOID;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef char CHAR;
typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;
typedef void *HANDLE;
typedef HANDLE HMODULE;
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef HANDLE HMONITOR;
typedef unsigned int ULONG_PTR;
typedef unsigned int DWORD_PTR;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef ULONGLONG QWORD;

typedef struct GUID {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[8];
} GUID;

typedef const GUID *REFGUID;
typedef REFGUID REFIID;
typedef GUID IID;
typedef IID CLSID;

typedef struct RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

typedef struct POINT {
    LONG x;
    LONG y;
} POINT;

typedef struct IUnknownVtbl IUnknownVtbl;
typedef struct IUnknown IUnknown;

struct IUnknownVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IUnknown *self, REFIID riid, void **out_object);
    ULONG (STDMETHODCALLTYPE *AddRef)(IUnknown *self);
    ULONG (STDMETHODCALLTYPE *Release)(IUnknown *self);
};

struct IUnknown {
    IUnknownVtbl *lpVtbl;
};

/* d3d8_min.h */

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
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_X8R8G8B8 = 22,
    D3DFMT_R5G6B5 = 23,
    D3DFMT_X1R5G5B5 = 24,
    D3DFMT_A1R5G5B5 = 25,
    D3DFMT_D24X8 = 77,
    D3DFMT_D16 = 80,
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

/* dinput8_min.h */

#define DIRECTINPUT_VERSION 0x0800u

#define DI_OK 0
#define DIENUM_STOP 0
#define DIENUM_CONTINUE 1

#define DI8DEVCLASS_ALL 0u
#define DI8DEVCLASS_DEVICE 1u
#define DI8DEVCLASS_POINTER 2u
#define DI8DEVCLASS_KEYBOARD 3u
#define DI8DEVCLASS_GAMECTRL 4u

#define DIEDFL_ALLDEVICES 0u
#define DIEDFL_ATTACHEDONLY 0x00000001u

#define DISCL_EXCLUSIVE 0x00000001u
#define DISCL_NONEXCLUSIVE 0x00000002u
#define DISCL_FOREGROUND 0x00000004u
#define DISCL_BACKGROUND 0x00000008u

#define DIDFT_AXIS 0x00000003u
#define DIPH_BYID 2u

typedef struct DIOBJECTDATAFORMAT {
    const GUID *pguid;
    DWORD dwOfs;
    DWORD dwType;
    DWORD dwFlags;
} DIOBJECTDATAFORMAT;

typedef struct DIDATAFORMAT {
    DWORD dwSize;
    DWORD dwObjSize;
    DWORD dwFlags;
    DWORD dwDataSize;
    DWORD dwNumObjs;
    const DIOBJECTDATAFORMAT *rgodf;
} DIDATAFORMAT;

typedef struct DIDEVCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwDevType;
    DWORD dwAxes;
    DWORD dwButtons;
    DWORD dwPOVs;
} DIDEVCAPS;

typedef struct DIPROPHEADER {
    DWORD dwSize;
    DWORD dwHeaderSize;
    DWORD dwObj;
    DWORD dwHow;
} DIPROPHEADER;

typedef struct DIPROPDWORD {
    DIPROPHEADER diph;
    DWORD dwData;
} DIPROPDWORD;

typedef struct DIPROPRANGE {
    DIPROPHEADER diph;
    LONG lMin;
    LONG lMax;
} DIPROPRANGE;

typedef struct DIJOYSTATE2 {
    LONG lX;
    LONG lY;
    LONG lZ;
    LONG lRx;
    LONG lRy;
    LONG lRz;
    LONG rglSlider[2];
    DWORD rgdwPOV[4];
    BYTE rgbButtons[128];
    LONG lVX;
    LONG lVY;
    LONG lVZ;
    LONG lVRx;
    LONG lVRy;
    LONG lVRz;
    LONG rglVSlider[2];
    LONG lAX;
    LONG lAY;
    LONG lAZ;
    LONG lARx;
    LONG lARy;
    LONG lARz;
    LONG rglASlider[2];
    LONG lFX;
    LONG lFY;
    LONG lFZ;
    LONG lFRx;
    LONG lFRy;
    LONG lFRz;
    LONG rglFSlider[2];
} DIJOYSTATE2;

typedef struct DIDEVICEINSTANCEA {
    DWORD dwSize;
    GUID guidInstance;
    GUID guidProduct;
    DWORD dwDevType;
    CHAR tszInstanceName[260];
    CHAR tszProductName[260];
    GUID guidFFDriver;
    WORD wUsagePage;
    WORD wUsage;
} DIDEVICEINSTANCEA;

typedef struct DIDEVICEOBJECTINSTANCEA {
    DWORD dwSize;
    GUID guidType;
    DWORD dwOfs;
    DWORD dwType;
    DWORD dwFlags;
    CHAR tszName[260];
    DWORD dwFFMaxForce;
    DWORD dwFFForceResolution;
    WORD wCollectionNumber;
    WORD wDesignatorIndex;
    WORD wUsagePage;
    WORD wUsage;
    DWORD dwDimension;
    WORD wExponent;
    WORD wReportId;
} DIDEVICEOBJECTINSTANCEA;

typedef BOOL (CALLBACK *LPDIENUMDEVICESCALLBACKA)(const DIDEVICEINSTANCEA *instance, void *user);
typedef BOOL (CALLBACK *LPDIENUMDEVICEOBJECTSCALLBACKA)(const DIDEVICEOBJECTINSTANCEA *object, void *user);

typedef struct IDirectInputDevice8AVtbl IDirectInputDevice8AVtbl;
typedef struct IDirectInputDevice8A IDirectInputDevice8A;

struct IDirectInputDevice8AVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IDirectInputDevice8A *self, REFIID riid, void **out_object);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDirectInputDevice8A *self);
    ULONG (STDMETHODCALLTYPE *Release)(IDirectInputDevice8A *self);
    HRESULT (STDMETHODCALLTYPE *GetCapabilities)(IDirectInputDevice8A *self, DIDEVCAPS *caps_out);
    HRESULT (STDMETHODCALLTYPE *EnumObjects)(IDirectInputDevice8A *self, LPDIENUMDEVICEOBJECTSCALLBACKA callback, void *user, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *GetProperty)(IDirectInputDevice8A *self, REFGUID prop, DIPROPHEADER *header);
    HRESULT (STDMETHODCALLTYPE *SetProperty)(IDirectInputDevice8A *self, REFGUID prop, const DIPROPHEADER *header);
    HRESULT (STDMETHODCALLTYPE *Acquire)(IDirectInputDevice8A *self);
    HRESULT (STDMETHODCALLTYPE *Unacquire)(IDirectInputDevice8A *self);
    HRESULT (STDMETHODCALLTYPE *GetDeviceState)(IDirectInputDevice8A *self, DWORD bytes, void *state_out);
    HRESULT (STDMETHODCALLTYPE *GetDeviceData)(IDirectInputDevice8A *self, DWORD object_data_size, void *object_data, DWORD *entries, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *SetDataFormat)(IDirectInputDevice8A *self, const DIDATAFORMAT *data_format);
    HRESULT (STDMETHODCALLTYPE *SetEventNotification)(IDirectInputDevice8A *self, HANDLE event_handle);
    HRESULT (STDMETHODCALLTYPE *SetCooperativeLevel)(IDirectInputDevice8A *self, HWND window, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *GetObjectInfo)(IDirectInputDevice8A *self, DIDEVICEOBJECTINSTANCEA *object_out, DWORD object_id, DWORD how);
    HRESULT (STDMETHODCALLTYPE *GetDeviceInfo)(IDirectInputDevice8A *self, DIDEVICEINSTANCEA *instance_out);
    HRESULT (STDMETHODCALLTYPE *RunControlPanel)(IDirectInputDevice8A *self, HWND owner, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *Initialize)(IDirectInputDevice8A *self, HINSTANCE instance, DWORD version, REFGUID guid);
    HRESULT (STDMETHODCALLTYPE *CreateEffect)(IDirectInputDevice8A *self, REFGUID guid, void *effect, void **effect_out, IUnknown *outer_unknown);
    HRESULT (STDMETHODCALLTYPE *EnumEffects)(IDirectInputDevice8A *self, void *callback, void *user, DWORD effect_type);
    HRESULT (STDMETHODCALLTYPE *GetEffectInfo)(IDirectInputDevice8A *self, void *effect_info, REFGUID guid);
    HRESULT (STDMETHODCALLTYPE *GetForceFeedbackState)(IDirectInputDevice8A *self, DWORD *state_out);
    HRESULT (STDMETHODCALLTYPE *SendForceFeedbackCommand)(IDirectInputDevice8A *self, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *EnumCreatedEffectObjects)(IDirectInputDevice8A *self, void *callback, void *user, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *Escape)(IDirectInputDevice8A *self, void *escape);
    HRESULT (STDMETHODCALLTYPE *Poll)(IDirectInputDevice8A *self);
};

struct IDirectInputDevice8A {
    IDirectInputDevice8AVtbl *lpVtbl;
};

typedef struct IDirectInput8AVtbl IDirectInput8AVtbl;
typedef struct IDirectInput8A IDirectInput8A;

struct IDirectInput8AVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IDirectInput8A *self, REFIID riid, void **out_object);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDirectInput8A *self);
    ULONG (STDMETHODCALLTYPE *Release)(IDirectInput8A *self);
    HRESULT (STDMETHODCALLTYPE *CreateDevice)(IDirectInput8A *self, const GUID *guid, IDirectInputDevice8A **device_out, IUnknown *outer_unknown);
    HRESULT (STDMETHODCALLTYPE *EnumDevices)(IDirectInput8A *self, DWORD device_class, LPDIENUMDEVICESCALLBACKA callback, void *user, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *GetDeviceStatus)(IDirectInput8A *self, const GUID *guid);
    HRESULT (STDMETHODCALLTYPE *RunControlPanel)(IDirectInput8A *self, HWND owner, DWORD flags);
    HRESULT (STDMETHODCALLTYPE *Initialize)(IDirectInput8A *self, HINSTANCE instance, DWORD version);
    HRESULT (STDMETHODCALLTYPE *FindDevice)(IDirectInput8A *self, const GUID *guid_class, LPCSTR name, GUID *guid_instance_out);
};

struct IDirectInput8A {
    IDirectInput8AVtbl *lpVtbl;
};

HRESULT WINAPI DirectInput8Create(HINSTANCE instance, DWORD version, REFIID interface_id, void **out_interface, IUnknown *outer_unknown);

extern const GUID GUID_SysKeyboard;
extern const GUID GUID_SysMouse;
extern const DIDATAFORMAT c_dfDIKeyboard;
extern const DIDATAFORMAT c_dfDIMouse2;

/* bass_min.h */

typedef DWORD HCHANNEL;
typedef DWORD HSAMPLE;
typedef DWORD HSTREAM;
typedef DWORD HMUSIC;
typedef DWORD HSYNC;

typedef void (CALLBACK *SYNCPROC)(HSYNC sync, DWORD channel, DWORD data, void *user);

BOOL WINAPI BASS_Init(INT device, DWORD freq, DWORD flags, HWND window, const GUID *clsid);
BOOL WINAPI BASS_SetConfig(DWORD option, DWORD value);
BOOL WINAPI BASS_Free(void);
BOOL WINAPI BASS_Update(DWORD length);

HSTREAM WINAPI BASS_StreamCreateFile(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD flags);
BOOL WINAPI BASS_StreamPlay(HSTREAM stream, BOOL flush, DWORD flags);
BOOL WINAPI BASS_StreamPreBuf(HSTREAM stream);
BOOL WINAPI BASS_StreamFree(HSTREAM stream);

HSAMPLE WINAPI BASS_SampleLoad(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD max, DWORD flags);
HCHANNEL WINAPI BASS_SamplePlayEx(HSAMPLE sample, DWORD start, INT volume, INT pan, BOOL loop);
BOOL WINAPI BASS_SampleStop(HSAMPLE sample);

BOOL WINAPI BASS_ChannelStop(DWORD channel);
QWORD WINAPI BASS_ChannelBytes2Seconds(DWORD channel, DWORD bytes);
DWORD WINAPI BASS_ChannelGetLevel(DWORD channel);
DWORD WINAPI BASS_ChannelGetData(DWORD channel, void *buffer, DWORD length);
HSYNC WINAPI BASS_ChannelSetSync(DWORD channel, DWORD sync_type, DWORD parameter, SYNCPROC proc, void *user);
DWORD WINAPI BASS_ChannelGetPosition(DWORD channel);
BOOL WINAPI BASS_ChannelRemoveSync(DWORD channel, HSYNC sync);
DWORD WINAPI BASS_ChannelIsActive(DWORD channel);

DWORD WINAPI BASS_ErrorGetCode(void);
BOOL WINAPI BASS_Start(void);
BOOL WINAPI BASS_Stop(void);
BOOL WINAPI BASS_Pause(void);

typedef BOOL (WINAPI *BASS_InitProc)(INT device, DWORD freq, DWORD flags, HWND window, const GUID *clsid);
typedef BOOL (WINAPI *BASS_SetConfigProc)(DWORD option, DWORD value);
typedef BOOL (WINAPI *BASS_FreeProc)(void);
typedef BOOL (WINAPI *BASS_UpdateProc)(DWORD length);
typedef HSTREAM (WINAPI *BASS_StreamCreateFileProc)(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD flags);
typedef BOOL (WINAPI *BASS_StreamPlayProc)(HSTREAM stream, BOOL flush, DWORD flags);
typedef BOOL (WINAPI *BASS_StreamPreBufProc)(HSTREAM stream);
typedef BOOL (WINAPI *BASS_StreamFreeProc)(HSTREAM stream);
typedef HSAMPLE (WINAPI *BASS_SampleLoadProc)(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD max, DWORD flags);
typedef HCHANNEL (WINAPI *BASS_SamplePlayExProc)(HSAMPLE sample, DWORD start, INT volume, INT pan, BOOL loop);
typedef BOOL (WINAPI *BASS_SampleStopProc)(HSAMPLE sample);
typedef BOOL (WINAPI *BASS_ChannelStopProc)(DWORD channel);
typedef QWORD (WINAPI *BASS_ChannelBytes2SecondsProc)(DWORD channel, DWORD bytes);
typedef DWORD (WINAPI *BASS_ChannelGetLevelProc)(DWORD channel);
typedef DWORD (WINAPI *BASS_ChannelGetDataProc)(DWORD channel, void *buffer, DWORD length);
typedef HSYNC (WINAPI *BASS_ChannelSetSyncProc)(DWORD channel, DWORD sync_type, DWORD parameter, SYNCPROC proc, void *user);
typedef DWORD (WINAPI *BASS_ChannelGetPositionProc)(DWORD channel);
typedef BOOL (WINAPI *BASS_ChannelRemoveSyncProc)(DWORD channel, HSYNC sync);
typedef DWORD (WINAPI *BASS_ChannelIsActiveProc)(DWORD channel);
typedef DWORD (WINAPI *BASS_ErrorGetCodeProc)(void);
typedef BOOL (WINAPI *BASS_StartProc)(void);
typedef BOOL (WINAPI *BASS_StopProc)(void);
typedef BOOL (WINAPI *BASS_PauseProc)(void);

#endif
