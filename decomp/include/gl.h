// Shared GL.o functions, partial.
#ifndef GL_H
#define GL_H

#include "object_fwd.h"
#include "texture_fwd.h"
#include "transform_matrix_fwd.h"

struct tColour;

void render_object_toon(Object* object, TransformMatrix* matrix); // @ 0x4123e0
char initialize_direct3d_renderer(); // @ 0x4129c0
void load_registered_texture_refs(int legacy_mode); // @ 0x412a00
void load_registered_texture_ref(int texture_index, int unused_legacy_mode); // @ 0x412a70
void set_blend_mode(int blend_mode); // @ 0x412d00
void set_immediate_blend_mode(int blend_mode); // @ 0x412e50
int present_backbuffer(); // @ 0x413520
void begin_sprite_depth_render_state(); // @ 0x413540
void end_sprite_depth_render_state(); // @ 0x413650
void set_object_color(Object* object, tColour color); // @ 0x4141d0
void set_fullscreen_mode(char enabled); // @ 0x414260
void bind_texture_ref(cRTexture* texture); // @ 0x414500
int reset_render_counters(); // @ 0x414650

#endif
