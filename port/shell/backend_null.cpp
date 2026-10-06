// Headless presenters: nothing to show or hear.

#include "render_backend.h"

void backend_create_texture(int, int, int, const unsigned char*) {}
void backend_destroy_texture(int) {}
void backend_clear(int, unsigned int, float, const RenderState*) {}
void backend_draw(int, const RenderVertex*, int, const RenderState*) {}
void backend_present() {}

// Headless audio: nothing plays, so no channel is ever active.
#include "audio_backend.h"

void audio_create_sound(int, const void*, int) {}
void audio_destroy_sound(int) {}
void audio_play(int, int, int, float, float, int, int) {}
void audio_stop(int) {}
int audio_channel_active(int) { return 0; }
void audio_set_bus_volume(int, float) {}
void audio_set_paused(int) {}
