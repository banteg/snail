// Registered texture descriptor slice used by startup texture loading.
#ifndef TEXTURE_REGISTRY_H
#define TEXTURE_REGISTRY_H

#include "direct3d_device8_view.h"
#include "sprite.h"

extern int g_estimated_texture_vram_bytes; // data_4b7644
extern TextureRef* g_current_texture_ref; // data_503174
extern Direct3DTexture8** g_d3d_texture_slots; // data_5031c8

#endif
