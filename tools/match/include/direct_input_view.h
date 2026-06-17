#ifndef DIRECT_INPUT_VIEW_H
#define DIRECT_INPUT_VIEW_H

struct DirectInputDevice;
struct DirectInputDeviceVtbl {
    char unknown_00[0x08];
    int (__stdcall* Release)(DirectInputDevice* self);
    char unknown_0c[0x20 - 0x0c];
    int (__stdcall* Unacquire)(DirectInputDevice* self);
};

struct DirectInputDevice {
    DirectInputDeviceVtbl* vtbl;
};

struct DirectInput;
struct DirectInputVtbl {
    char unknown_00[0x08];
    int (__stdcall* Release)(DirectInput* self);
};

struct DirectInput {
    DirectInputVtbl* vtbl;
};

#endif
