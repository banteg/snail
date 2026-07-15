#ifndef SNAIL_DINPUT8_MIN_H
#define SNAIL_DINPUT8_MIN_H

#include "win32_min.h"

/*
 * Minimal DirectInput 8 declarations for the recovered keyboard, mouse, and
 * controller initialization paths. This keeps the vtable offsets used by the
 * game readable in Binary Ninja without importing the full SDK surface.
 */

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

#endif
