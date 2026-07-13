// Narrow renderer member view used only by the fullscreen device-reset pair.
#ifndef DIRECT3D_RENDERER_RESET_VIEW_H
#define DIRECT3D_RENDERER_RESET_VIEW_H

#include "direct3d_renderer.h"

struct Direct3DDevice8ResetView;

struct Direct3DDevice8ResetVtbl {
    char unknown_000[0x38];
    int (__stdcall* Reset)(
        Direct3DDevice8ResetView* self, D3DPresentParameters* parameters);
};

struct Direct3DDevice8ResetView {
    Direct3DDevice8ResetVtbl* vtbl;
};

class Direct3DRendererResetView : public Direct3DRenderer {
public:
    void direct3d_renderer_set_fullscreen_mode(int enabled); // @ 0x414270
    void restore_texture_ref_stage_states(); // @ 0x4143c0
};

typedef char Direct3DRendererResetView_must_be_0xbcc0[
    (sizeof(Direct3DRendererResetView) == 0xbcc0) ? 1 : -1];
typedef char Direct3DDevice8ResetVtbl_must_cover_0x3c[
    (sizeof(Direct3DDevice8ResetVtbl) == 0x3c) ? 1 : -1];

#endif
