// Direct3DRenderer::release_direct3d_device_interfaces @ 0x411960

#include "direct3d_renderer.h"

struct Direct3DDevice8ReleaseView;
struct Direct3D8ReleaseView;

struct Direct3DDevice8ReleaseVtbl {
    char unknown_00[0x08];
    int (__stdcall* Release)(Direct3DDevice8ReleaseView* self);
};

struct Direct3DDevice8ReleaseView {
    Direct3DDevice8ReleaseVtbl* vtbl;
};

struct Direct3D8ReleaseVtbl {
    char unknown_00[0x08];
    int (__stdcall* Release)(Direct3D8ReleaseView* self);
};

struct Direct3D8ReleaseView {
    Direct3D8ReleaseVtbl* vtbl;
};

void Direct3DRenderer::release_direct3d_device_interfaces()
{
    Direct3DDevice8ReleaseView* device_view =
        (Direct3DDevice8ReleaseView*)device;
    if (device_view != 0) {
        device_view->vtbl->Release(device_view);
        device = 0;
    }

    Direct3D8ReleaseView* d3d8 = (Direct3D8ReleaseView*)d3d;
    if (d3d8 != 0) {
        d3d8->vtbl->Release(d3d8);
        d3d = 0;
    }
}
