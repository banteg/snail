// Browser presenter: forwards to WebGL2 in port/web/snail.js, which reads the
// vertices and state straight out of linear memory.

#include "render_backend.h"

#define WEB_IMPORT(name) __attribute__((import_module("snail"), import_name(name)))

WEB_IMPORT("texture_create") void web_texture_create(int id, int width, int height, const unsigned char* rgba);
WEB_IMPORT("texture_destroy") void web_texture_destroy(int id);
WEB_IMPORT("clear") void web_clear(int flags, unsigned int color, float z, const RenderState* state);
WEB_IMPORT("draw") void web_draw(int primitive, const RenderVertex* vertices, int count, const RenderState* state);

void backend_create_texture(int id, int width, int height, const unsigned char* rgba)
{
    web_texture_create(id, width, height, rgba);
}

void backend_destroy_texture(int id) { web_texture_destroy(id); }

void backend_clear(int flags, unsigned int color, float z, const RenderState* state)
{
    web_clear(flags, color, z, state);
}

void backend_draw(int primitive, const RenderVertex* vertices, int count, const RenderState* state)
{
    web_draw(primitive, vertices, count, state);
}

// The browser shows the canvas when the animation-frame callback returns.
void backend_present() {}
