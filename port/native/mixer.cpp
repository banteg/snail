// SDL3_mixer presenter for the emulated BASS library (port/shell/
// audio_backend.h), the native counterpart of port/web/audio.js. Sounds are
// the archive's OGG files; each channel is a mixer track tagged with its bus,
// so the game's two global volumes are tag gains.

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string.h>

#include <unordered_map>

#include "host.h"

namespace {
const char* const kBusTags[] = {"sample", "stream"};

struct Sound {
    MIX_Audio* audio;
    void* bytes;  // kept for audio decoded on demand
    int frequency;
};
}  // namespace

struct MixerPresenter {
    MIX_Mixer* mixer;
    std::unordered_map<int, Sound> sounds;
    std::unordered_map<int, MIX_Track*> tracks;
};

MixerPresenter* mixer_create(bool muted)
{
    MixerPresenter* presenter = new MixerPresenter;
    presenter->mixer = nullptr;
    if (!MIX_Init() || !(presenter->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr))) {
        SDL_Log("snail: no audio: %s", SDL_GetError());
        return presenter;
    }
    if (muted)
        MIX_SetMixerGain(presenter->mixer, 0.0f);
    return presenter;
}

extern "C" {

void w2c_snail_sound_create(w2c_snail* host, uint32_t id, uint32_t pointer, uint32_t size)
{
    MixerPresenter* presenter = host->mixer;
    if (!presenter->mixer)
        return;
    // Short effects decode up front; music streams from a copy of its bytes.
    bool predecode = size < (1u << 20);
    void* bytes = SDL_malloc(size);
    memcpy(bytes, linear_memory(host->game) + pointer, size);
    SDL_IOStream* io = SDL_IOFromConstMem(bytes, size);
    MIX_Audio* audio = MIX_LoadAudio_IO(presenter->mixer, io, predecode, true);
    if (!audio) {
        SDL_Log("snail: sound %u: %s", id, SDL_GetError());
        SDL_free(bytes);
        return;
    }
    if (predecode) {
        SDL_free(bytes);
        bytes = nullptr;
    }
    SDL_AudioSpec spec = {};
    MIX_GetAudioFormat(audio, &spec);
    presenter->sounds[(int)id] = Sound{audio, bytes, spec.freq};
}

void w2c_snail_sound_destroy(w2c_snail* host, uint32_t id)
{
    MixerPresenter* presenter = host->mixer;
    auto it = presenter->sounds.find((int)id);
    if (it == presenter->sounds.end())
        return;
    for (auto& track : presenter->tracks)
        if (MIX_GetTrackAudio(track.second) == it->second.audio)
            MIX_SetTrackAudio(track.second, nullptr);
    MIX_DestroyAudio(it->second.audio);
    SDL_free(it->second.bytes);
    presenter->sounds.erase(it);
}

void w2c_snail_channel_play(w2c_snail* host, uint32_t channel, uint32_t sound, uint32_t bus, float volume, float pan,
    uint32_t frequency, uint32_t loop)
{
    MixerPresenter* presenter = host->mixer;
    auto found = presenter->sounds.find((int)sound);
    if (!presenter->mixer || found == presenter->sounds.end())
        return;
    MIX_Track*& track = presenter->tracks[(int)channel];
    if (!track)
        track = MIX_CreateTrack(presenter->mixer);
    MIX_StopTrack(track, 0);
    MIX_UntagTrack(track, nullptr);
    MIX_TagTrack(track, kBusTags[bus ? 1 : 0]);
    MIX_SetTrackAudio(track, found->second.audio);
    MIX_SetTrackGain(track, volume);
    MIX_StereoGains gains = {pan > 0 ? 1.0f - pan : 1.0f, pan < 0 ? 1.0f + pan : 1.0f};
    MIX_SetTrackStereo(track, &gains);
    float ratio = frequency && found->second.frequency ? (float)frequency / (float)found->second.frequency : 1.0f;
    MIX_SetTrackFrequencyRatio(track, ratio);
    SDL_PropertiesID options = SDL_CreateProperties();
    SDL_SetNumberProperty(options, MIX_PROP_PLAY_LOOPS_NUMBER, loop ? -1 : 0);
    MIX_PlayTrack(track, options);
    SDL_DestroyProperties(options);
}

void w2c_snail_channel_stop(w2c_snail* host, uint32_t channel)
{
    auto it = host->mixer->tracks.find((int)channel);
    if (it != host->mixer->tracks.end())
        MIX_StopTrack(it->second, 0);
}

uint32_t w2c_snail_channel_active(w2c_snail* host, uint32_t channel)
{
    auto it = host->mixer->tracks.find((int)channel);
    return it != host->mixer->tracks.end() && MIX_TrackPlaying(it->second) ? 1 : 0;
}

void w2c_snail_bus_volume(w2c_snail* host, uint32_t bus, float volume)
{
    if (host->mixer->mixer)
        MIX_SetTagGain(host->mixer->mixer, kBusTags[bus ? 1 : 0], volume);
}

void w2c_snail_set_paused(w2c_snail* host, uint32_t paused)
{
    if (!host->mixer->mixer)
        return;
    if (paused)
        MIX_PauseAllTracks(host->mixer->mixer);
    else
        MIX_ResumeAllTracks(host->mixer->mixer);
}

}  // extern "C"
