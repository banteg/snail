#ifndef SNAIL_PORT_RENDER_BACKEND_H
#define SNAIL_PORT_RENDER_BACKEND_H

// What the emulated Direct3D 8 device (shell/d3d8_device.cpp) hands to a
// presenter: textures, clears and fully transformed draws. Vertices stay in
// Direct3D conventions (clip-space z in [0, w], ARGB colours); each backend
// converts to its API. backend_null.cpp drops everything (headless runs),
// backend_web.cpp forwards to WebGL2 in port/web/.

struct RenderVertex {
    float x, y, z, w;    // clip space after world, view and projection
    unsigned int color;  // D3DCOLOR (0xAARRGGBB)
    float u, v;          // after the texture transform
    float fog;           // vertex fog factor: 1 keeps the colour, 0 is fog colour
};

typedef char RenderVertex_must_be_32[(sizeof(RenderVertex) == 32) ? 1 : -1];

// Direct3D 8 enumerant values throughout (D3DBLEND, D3DCMP, D3DCULL, D3DTOP,
// D3DTA, D3DTADDRESS), as the game set them.
struct RenderState {
    int texture;  // backend texture id, 0 for none
    int color_op, color_arg1, color_arg2;
    int alpha_op, alpha_arg1, alpha_arg2;
    unsigned int texture_factor;
    int address_u, address_v;
    int alpha_blend, src_blend, dest_blend;
    int alpha_test, alpha_func, alpha_ref;
    int z_enable, z_write, z_func;
    int cull;
    int fog;
    unsigned int fog_color;
    int viewport_x, viewport_y, viewport_width, viewport_height;
    float viewport_min_z, viewport_max_z;
};

// port/web/renderer.js reads this layout field by field.
typedef char RenderState_must_be_112[(sizeof(RenderState) == 112) ? 1 : -1];

enum RenderPrimitive {
    RENDER_TRIANGLES = 0,
    RENDER_LINES = 1,
};

enum RenderClearFlags {
    RENDER_CLEAR_TARGET = 1,
    RENDER_CLEAR_Z = 2,
};

void backend_create_texture(int id, int width, int height, const unsigned char* rgba);  // rows top first
void backend_destroy_texture(int id);
void backend_clear(int flags, unsigned int color, float z, const RenderState* state);
void backend_draw(int primitive, const RenderVertex* vertices, int count, const RenderState* state);
void backend_present();

#endif
