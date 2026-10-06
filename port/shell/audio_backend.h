#ifndef SNAIL_PORT_AUDIO_BACKEND_H
#define SNAIL_PORT_AUDIO_BACKEND_H

// What the emulated BASS 2.0 library (shell/bass_emu.cpp) hands to an audio
// presenter: encoded sounds (the game's OGG files, decoded by the presenter)
// and channels playing them on one of two buses. backend_null.cpp plays
// nothing (headless runs); backend_web.cpp forwards to Web Audio.

enum AudioBus {
    AUDIO_BUS_SAMPLE = 0,  // BASS_CONFIG_GVOL_SAMPLE
    AUDIO_BUS_STREAM = 1,  // BASS_CONFIG_GVOL_STREAM
};

void audio_create_sound(int sound, const void* bytes, int size);  // copies the bytes
void audio_destroy_sound(int sound);
// volume 0..1, pan -1..1, frequency in Hz or 0 for the sound's own rate.
void audio_play(int channel, int sound, int bus, float volume, float pan, int frequency, int loop);
void audio_stop(int channel);
int audio_channel_active(int channel);  // still playing (or waiting to decode)
void audio_set_bus_volume(int bus, float volume);
void audio_set_paused(int paused);

#endif
