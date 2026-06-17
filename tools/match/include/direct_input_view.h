#ifndef DIRECT_INPUT_VIEW_H
#define DIRECT_INPUT_VIEW_H

// Partial SDK-style C++ COM views for IDirectInput8A/IDirectInputDevice8A.
struct DirectInputDevice {
    virtual int __stdcall QueryInterface(void* iid, void** out_object) = 0;
    virtual int __stdcall AddRef() = 0;
    virtual int __stdcall Release() = 0;
    virtual int __stdcall GetCapabilities(void* capabilities) = 0;
    virtual int __stdcall EnumObjects(void* callback, void* ref, unsigned int flags) = 0;
    virtual int __stdcall GetProperty(void* guid, void* property) = 0;
    virtual int __stdcall SetProperty(void* guid, void* property) = 0;
    virtual int __stdcall Acquire() = 0;
    virtual int __stdcall Unacquire() = 0;
    virtual int __stdcall GetDeviceState(unsigned int size, void* data) = 0;
    virtual int __stdcall GetDeviceData(unsigned int size, void* data, unsigned int* count, unsigned int flags) = 0;
    virtual int __stdcall SetDataFormat(void* data_format) = 0;
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
    virtual int __stdcall CreateDevice(void* guid, DirectInputDevice** out_device, void* outer_unknown) = 0;
    virtual int __stdcall EnumDevices(
        unsigned int device_type,
        void* callback,
        void* ref,
        unsigned int flags) = 0;
};

#endif
