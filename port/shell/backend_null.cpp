// Headless presenter: nothing to show.

#include "render_backend.h"

void backend_create_texture(int, int, int, const unsigned char*) {}
void backend_destroy_texture(int) {}
void backend_clear(int, unsigned int, float, const RenderState*) {}
void backend_draw(int, const RenderVertex*, int, const RenderState*) {}
void backend_present() {}
