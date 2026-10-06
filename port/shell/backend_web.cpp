// Browser presenters: drawing goes to WebGL2 in port/web/renderer.js, which reads the
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

// Audio goes to Web Audio in port/web/audio.js.
#include "audio_backend.h"

WEB_IMPORT("sound_create") void web_sound_create(int sound, const void* bytes, int size);
WEB_IMPORT("sound_destroy") void web_sound_destroy(int sound);
WEB_IMPORT("channel_play") void web_channel_play(int channel, int sound, int bus, float volume, float pan, int frequency, int loop);
WEB_IMPORT("channel_stop") void web_channel_stop(int channel);
WEB_IMPORT("channel_active") int web_channel_active(int channel);
WEB_IMPORT("bus_volume") void web_bus_volume(int bus, float volume);
WEB_IMPORT("set_paused") void web_set_paused(int paused);

void audio_create_sound(int sound, const void* bytes, int size) { web_sound_create(sound, bytes, size); }
void audio_destroy_sound(int sound) { web_sound_destroy(sound); }
void audio_play(int channel, int sound, int bus, float volume, float pan, int frequency, int loop)
{
    web_channel_play(channel, sound, bus, volume, pan, frequency, loop);
}
void audio_stop(int channel) { web_channel_stop(channel); }
int audio_channel_active(int channel) { return web_channel_active(channel); }
void audio_set_bus_volume(int bus, float volume) { web_bus_volume(bus, volume); }
void audio_set_paused(int paused) { web_set_paused(paused); }
