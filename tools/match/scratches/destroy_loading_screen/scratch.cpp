// destroy_loading_screen @ 0x418e50 (thiscall)

#include "loading_screen.h"

class Direct3DTexture8;

class Direct3DTexture8Vtbl {
public:
    void* query_interface;
    void* add_ref;
    int(__stdcall* release)(Direct3DTexture8* texture);
};

class Direct3DTexture8 {
public:
    Direct3DTexture8Vtbl* vtbl;
};

extern int g_last_loading_budget; // data_4df9c4
extern Direct3DTexture8* g_loading_background_texture; // data_503288
extern Direct3DTexture8* g_loading_bar_on_texture;     // data_503280

int LoadingScreen::destroy_loading_screen()
{
    g_last_loading_budget = last_loading_budget;
    g_loading_background_texture->vtbl->release(g_loading_background_texture);
    int result = g_loading_bar_on_texture->vtbl->release(g_loading_bar_on_texture);
    active = 0;
    return result;
}
