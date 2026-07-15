// destroy_loading_screen @ 0x418e50 (thiscall)

#include "direct3d_device8_view.h"
#include "loading_bar.h"
#include "runtime_config.h"

void LoadingBar::destroy_loading_screen()
{
    g_runtime_config.last_loading_budget = last_loading_budget;
    g_loading_background_texture->vtbl->Release(g_loading_background_texture);
    g_loading_bar_on_texture->vtbl->Release(g_loading_bar_on_texture);
    active = 0;
}
