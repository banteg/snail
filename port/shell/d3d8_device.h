#ifndef SNAIL_PORT_D3D8_DEVICE_H
#define SNAIL_PORT_D3D8_DEVICE_H

#include "direct3d_device8_view.h"

// A texture on the emulated device (shell/d3d8_device.cpp), from A8R8G8B8
// pixels already converted to RGBA bytes, rows top first.
Direct3DTexture8* create_emulated_texture(int width, int height, const unsigned char* rgba);

#endif
