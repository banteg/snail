#ifndef DIRECT_INPUT_VIEW_H
#define DIRECT_INPUT_VIEW_H

enum {
    DIRECT_INPUT_JOYSTICK_CAPACITY = 4,
    DIRECT_INPUT_KEY_COUNT = 0x100,
    DIRECT_INPUT_BUTTON_COUNT = 128,
};

// DirectInput 8 SDK records used by the controller enumeration and polling
// family. Keeping the complete public layouts here makes the stack objects and
// callback arguments SDK-owned values rather than scratch-local byte windows.
struct DirectInputGuid {
    unsigned int data1;
    unsigned short data2;
    unsigned short data3;
    unsigned char data4[8];
};

struct DIOBJECTDATAFORMAT {
    const DirectInputGuid* pguid;
    unsigned int dwOfs;
    unsigned int dwType;
    unsigned int dwFlags;
};

struct DIDATAFORMAT {
    unsigned int dwSize;
    unsigned int dwObjSize;
    unsigned int dwFlags;
    unsigned int dwDataSize;
    unsigned int dwNumObjs;
    const DIOBJECTDATAFORMAT* rgodf;
};

struct DIDEVICEINSTANCEA {
    unsigned int dwSize;
    DirectInputGuid guidInstance;
    DirectInputGuid guidProduct;
    unsigned int dwDevType;
    char tszInstanceName[260];
    char tszProductName[260];
    DirectInputGuid guidFFDriver;
    unsigned short wUsagePage;
    unsigned short wUsage;
};

struct DIDEVICEOBJECTINSTANCEA {
    unsigned int dwSize;
    DirectInputGuid guidType;
    unsigned int dwOfs;
    unsigned int dwType;
    unsigned int dwFlags;
    char tszName[260];
    unsigned int dwFFMaxForce;
    unsigned int dwFFForceResolution;
    unsigned short wCollectionNumber;
    unsigned short wDesignatorIndex;
    unsigned short wUsagePage;
    unsigned short wUsage;
    unsigned int dwDimension;
    unsigned short wExponent;
    unsigned short wReportId;
};

struct DIPROPHEADER {
    unsigned int dwSize;
    unsigned int dwHeaderSize;
    unsigned int dwObj;
    unsigned int dwHow;
};

struct DIPROPRANGE {
    DIPROPHEADER diph;
    int lMin;
    int lMax;
};

struct DIJOYSTATE2 {
    int lX;
    int lY;
    int lZ;
    int lRx;
    int lRy;
    int lRz;
    int rglSlider[2];
    unsigned int rgdwPOV[4];
    unsigned char rgbButtons[DIRECT_INPUT_BUTTON_COUNT];
    int lVX;
    int lVY;
    int lVZ;
    int lVRx;
    int lVRy;
    int lVRz;
    int rglVSlider[2];
    int lAX;
    int lAY;
    int lAZ;
    int lARx;
    int lARy;
    int lARz;
    int rglASlider[2];
    int lFX;
    int lFY;
    int lFZ;
    int lFRx;
    int lFRy;
    int lFRz;
    int rglFSlider[2];
};

typedef char DirectInputGuid_must_be_0x10[
    (sizeof(DirectInputGuid) == 0x10) ? 1 : -1];
typedef char DIOBJECTDATAFORMAT_must_be_0x10[
    (sizeof(DIOBJECTDATAFORMAT) == 0x10) ? 1 : -1];
typedef char DIDATAFORMAT_must_be_0x18[
    (sizeof(DIDATAFORMAT) == 0x18) ? 1 : -1];
typedef char DIDEVICEINSTANCEA_must_be_0x244[
    (sizeof(DIDEVICEINSTANCEA) == 0x244) ? 1 : -1];
typedef char DIDEVICEOBJECTINSTANCEA_must_be_0x13c[
    (sizeof(DIDEVICEOBJECTINSTANCEA) == 0x13c) ? 1 : -1];
typedef char DIPROPRANGE_must_be_0x18[
    (sizeof(DIPROPRANGE) == 0x18) ? 1 : -1];
typedef char DIJOYSTATE2_must_be_0x110[
    (sizeof(DIJOYSTATE2) == 0x110) ? 1 : -1];

// SDK DIMOUSESTATE2 layout passed to GetDeviceState for the mouse device.
struct DirectInputMouseState {
    int x;
    int y;
    int wheel;
    unsigned char buttons[8];
};

typedef char DirectInputMouseState_must_be_0x14[
    (sizeof(DirectInputMouseState) == 0x14) ? 1 : -1];

// Partial SDK-style C++ COM views for IDirectInput8A/IDirectInputDevice8A.
struct DirectInputDevice;

typedef int (__stdcall* DirectInputEnumDevicesCallback)(
    DIDEVICEINSTANCEA* instance,
    void* context);
typedef int (__stdcall* DirectInputEnumObjectsCallback)(
    DIDEVICEOBJECTINSTANCEA* instance,
    void* context);

struct DirectInputDevice {
    virtual int __stdcall QueryInterface(void* iid, void** out_object) = 0;
    virtual int __stdcall AddRef() = 0;
    virtual int __stdcall Release() = 0;
    virtual int __stdcall GetCapabilities(void* capabilities) = 0;
    virtual int __stdcall EnumObjects(
        DirectInputEnumObjectsCallback callback,
        void* ref,
        unsigned int flags) = 0;
    virtual int __stdcall GetProperty(void* guid, void* property) = 0;
    virtual int __stdcall SetProperty(void* guid, DIPROPHEADER* property) = 0;
    virtual int __stdcall Acquire() = 0;
    virtual int __stdcall Unacquire() = 0;
    virtual int __stdcall GetDeviceState(unsigned int size, void* data) = 0;
    virtual int __stdcall GetDeviceData(unsigned int size, void* data, unsigned int* count, unsigned int flags) = 0;
    virtual int __stdcall SetDataFormat(const DIDATAFORMAT* data_format) = 0;
    virtual int __stdcall SetEventNotification(void* event_handle) = 0;
    virtual int __stdcall SetCooperativeLevel(int hwnd, unsigned int flags) = 0;
    virtual int __stdcall GetObjectInfo(void* object_instance, unsigned int object_id, unsigned int how) = 0;
    virtual int __stdcall GetDeviceInfo(void* device_instance) = 0;
    virtual int __stdcall RunControlPanel(int owner, unsigned int flags) = 0;
    virtual int __stdcall Initialize(void* instance, unsigned int version, void* guid) = 0;
    virtual int __stdcall CreateEffect(void* guid, void* effect, void** out_effect, void* outer_unknown) = 0;
    virtual int __stdcall EnumEffects(void* callback, void* ref, unsigned int type) = 0;
    virtual int __stdcall GetEffectInfo(void* effect_info, void* guid) = 0;
    virtual int __stdcall GetForceFeedbackState(unsigned int* out_state) = 0;
    virtual int __stdcall SendForceFeedbackCommand(unsigned int flags) = 0;
    virtual int __stdcall EnumCreatedEffectObjects(void* callback, void* ref, unsigned int flags) = 0;
    virtual int __stdcall Escape(void* escape) = 0;
    virtual int __stdcall Poll() = 0;
};

struct DirectInput {
    virtual int __stdcall QueryInterface(void* iid, void** out_object) = 0;
    virtual int __stdcall AddRef() = 0;
    virtual int __stdcall Release() = 0;
    virtual int __stdcall CreateDevice(
        DirectInputGuid* guid,
        DirectInputDevice** out_device,
        void* outer_unknown) = 0;
    virtual int __stdcall EnumDevices(
        unsigned int device_type,
        DirectInputEnumDevicesCallback callback,
        void* ref,
        unsigned int flags) = 0;
};

// Process-owned joystick enumeration state. The callback appends into the
// fixed device bank; the remaining DirectInput helpers borrow those entries.
extern int g_joystick_count; // data_777b2c
extern DirectInput* g_joystick_input; // data_777b30
extern DirectInputDevice*
    g_joystick_devices[DIRECT_INPUT_JOYSTICK_CAPACITY]; // data_777b34

// Process-owned keyboard state. Initialization creates the two COM objects;
// polling advances the fixed previous/current SDK key-state pair; teardown
// releases the interfaces.
extern DirectInput* g_keyboard_input; // data_777d4c
extern DirectInputDevice* g_keyboard_device; // data_777d50
extern unsigned char
    g_keyboard_previous_state[DIRECT_INPUT_KEY_COUNT]; // data_777b4c
extern unsigned char
    g_keyboard_current_state[DIRECT_INPUT_KEY_COUNT]; // data_777c4c

// Process-owned mouse interfaces. The authored pointer coordinates and Win32
// clipping state have separate owners; only the DirectInput lifetime lives
// here.
extern DirectInput* g_mouse_input; // data_777d98
extern DirectInputDevice* g_mouse_device; // data_777d9c

// Borrowed static DirectInput SDK identifiers and data-format descriptors.
// The keyboard, mouse, and joystick setup paths all consume this one bank.
extern DirectInputGuid g_directinput_keyboard_guid; // data_49b010
extern DirectInputGuid g_directinput_mouse_guid; // data_49b020
extern DirectInputGuid g_directinput8_iid; // data_49b0c0
extern DIDATAFORMAT g_directinput_joystick_data_format; // data_49b2fc
extern DIDATAFORMAT g_directinput_keyboard_data_format; // data_49b504
extern DIDATAFORMAT g_directinput_mouse_data_format; // data_49b70c

#endif
