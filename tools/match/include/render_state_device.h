// Minimal Direct3D device view for render-state setup helpers.
#ifndef RENDER_STATE_DEVICE_H
#define RENDER_STATE_DEVICE_H

#include "transform_matrix.h"

struct RenderStateDevice;

struct RenderStateDeviceVtbl {
    char unknown_000[0x94];
    int (__stdcall* SetTransform)(RenderStateDevice* self, int state, TransformMatrix* matrix);
    int (__stdcall* GetTransform)(RenderStateDevice* self, int state, TransformMatrix* matrix);
    char unknown_09c[0xc8 - 0x9c];
    int (__stdcall* SetRenderState)(RenderStateDevice* self, int state, int value);
    char unknown_0cc[0xfc - 0xcc];
    int (__stdcall* SetTextureStageState)(RenderStateDevice* self, int stage, int type, int value);
};

struct RenderStateDevice {
    RenderStateDeviceVtbl* vtbl;
};

extern RenderStateDevice* g_d3d_device; // data_502fec

#endif
