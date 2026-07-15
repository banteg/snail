// Authored cRLoadingBar global owner. Windows keeps the exact 0x0c-byte
// controller at data_503290; function names retain the loading_screen harness.
#ifndef LOADING_BAR_H
#define LOADING_BAR_H

class Direct3DTexture8;
struct ObjectRenderBuffers;

struct LoadingBar {
    void initialize_loading_screen(); // @ 0x418b50, cRLoadingBar::Init
    void destroy_loading_screen();    // @ 0x418e50, cRLoadingBar::UnInit
    void update_loading_screen();     // @ 0x418e80, cRLoadingBar::AI

    int active;              // +0x00
    int previous_percent;    // +0x04
    int last_loading_budget; // +0x08
};

typedef char LoadingBar_must_be_0x0c[
    (sizeof(LoadingBar) == 0x0c) ? 1 : -1];

extern LoadingBar g_loading_bar; // data_503290, cross-port gLoadingBar
extern Direct3DTexture8* g_loading_bar_on_texture; // data_503280
extern ObjectRenderBuffers* g_loading_background_vertex_buffer; // data_503284
extern Direct3DTexture8* g_loading_background_texture; // data_503288
extern ObjectRenderBuffers* g_loading_bar_vertex_buffer; // data_5032a4

#endif
