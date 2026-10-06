// The BASS 2.0 subset the recovered audio code (cRBass, decomp/engine/
// BassPlay and its neighbours) binds at run time, emulated over an audio
// presenter (audio_backend.h). initialize_bass_audio_backend compiles
// unchanged: it extracts Bass.dll from the archive, then LoadLibraryA and
// GetProcAddress (below) hand it these functions instead of the DLL's.
//
// Handles: a sample, each channel played from a sample, and each stream. The
// game relies on BASS 2.0 relating a sample's channels to the sample: it
// stops a looped sound by passing the channel to BASS_SampleStop, and asks
// BASS_ChannelIsActive about a sample to learn whether any of its channels
// still plays. Both are honoured here; the shipped BASS.DLL is packed, so this
// reading of BASS 2.0 is unverified (docs/port/divergences.md).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio_backend.h"
#include "audio_system.h"

namespace {

enum {
    BASS_ACTIVE_STOPPED = 0,
    BASS_ACTIVE_PLAYING = 1,
    BASS_SAMPLE_LOOP = 4,
    BASS_SAMPLE_OVER_MASK = 0x30000,
    BASS_CONFIG_GVOL_SAMPLE = 4,
    BASS_CONFIG_GVOL_STREAM = 5,
    BASS_ERROR_HANDLE = 5,
    BASS_ERROR_FILEOPEN = 2,
    BASS_ERROR_NOCHAN = 18,

    KIND_SHIFT = 24,
    KIND_SAMPLE = 1,
    KIND_CHANNEL = 2,
    KIND_STREAM = 3,
    CAPACITY = 1024,
};

struct Sample {
    bool used;
    int sound;
    unsigned int max;
    unsigned int flags;
};

struct Channel {
    bool used;
    int sample;  // index of its sample
    unsigned int serial;  // play order, for BASS_SAMPLE_OVER_POS
};

struct Stream {
    bool used;
    int sound;
};

Sample g_samples[CAPACITY];
Channel g_channels[CAPACITY];
Stream g_streams[CAPACITY];
int g_next_sound = 1;
unsigned int g_serial = 0;
unsigned int g_error = 0;

unsigned int handle(int kind, int index) { return ((unsigned int)kind << KIND_SHIFT) | (unsigned int)(index + 1); }
int kind_of(unsigned int h) { return (int)(h >> KIND_SHIFT); }
int index_of(unsigned int h) { return (int)(h & 0xffffff) - 1; }

template <typename T>
T* lookup(T* table, int kind, unsigned int h)
{
    int index = index_of(h);
    if (kind_of(h) != kind || index < 0 || index >= CAPACITY || !table[index].used)
        return 0;
    return &table[index];
}

template <typename T>
int allocate(T* table)
{
    for (int i = 0; i < CAPACITY; ++i)
        if (!table[i].used) {
            memset(&table[i], 0, sizeof(T));
            table[i].used = true;
            return i;
        }
    return -1;
}

int fail(unsigned int code)
{
    g_error = code;
    return 0;
}

// Encoded bytes from memory or a file; the presenter copies them.
int create_sound(int from_memory, const void* source, unsigned int offset, unsigned int length)
{
    int sound = g_next_sound++;
    if (from_memory) {
        audio_create_sound(sound, (const char*)source + offset, (int)length);
        return sound;
    }
    FILE* file = fopen((const char*)source, "rb");
    if (!file)
        return 0;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, (long)offset, SEEK_SET);
    long count = length ? (long)length : size - (long)offset;
    char* bytes = (char*)malloc(count > 0 ? count : 1);
    count = (long)fread(bytes, 1, count, file);
    fclose(file);
    audio_create_sound(sound, bytes, (int)count);
    free(bytes);
    return sound;
}

bool channel_active(int index)
{
    return g_channels[index].used && audio_channel_active(handle(KIND_CHANNEL, index));
}

void stop_channel(int index)
{
    audio_stop(handle(KIND_CHANNEL, index));
    g_channels[index].used = false;
}

// --- the BASS functions ---------------------------------------------------------

int __stdcall bass_init(unsigned int, unsigned int, unsigned int, void*, const void*) { return 1; }
int __stdcall bass_free() { return 1; }
int __stdcall bass_update() { return 1; }
unsigned int __stdcall bass_error_get_code() { return g_error; }

unsigned int __stdcall bass_set_config(unsigned int option, unsigned int value)
{
    if (option == BASS_CONFIG_GVOL_SAMPLE)
        audio_set_bus_volume(AUDIO_BUS_SAMPLE, (float)value / 100.0f);
    else if (option == BASS_CONFIG_GVOL_STREAM)
        audio_set_bus_volume(AUDIO_BUS_STREAM, (float)value / 100.0f);
    return value;
}

int __stdcall bass_start()
{
    audio_set_paused(0);
    return 1;
}

int __stdcall bass_pause()
{
    audio_set_paused(1);
    return 1;
}

int __stdcall bass_stop()
{
    for (int i = 0; i < CAPACITY; ++i)
        if (g_channels[i].used)
            stop_channel(i);
    for (int i = 0; i < CAPACITY; ++i)
        if (g_streams[i].used)
            audio_stop(handle(KIND_STREAM, i));
    return 1;
}

BassHandle __stdcall bass_sample_load(int from_memory, const void* source, unsigned int offset, unsigned int length,
    unsigned int max, unsigned int flags)
{
    int index = allocate(g_samples);
    if (index < 0)
        return fail(BASS_ERROR_NOCHAN);
    int sound = create_sound(from_memory, source, offset, length);
    if (!sound) {
        g_samples[index].used = false;
        return fail(BASS_ERROR_FILEOPEN);
    }
    g_samples[index].sound = sound;
    g_samples[index].max = max ? max : 1;
    g_samples[index].flags = flags;
    return handle(KIND_SAMPLE, index);
}

BassHandle __stdcall bass_sample_play_ex(BassHandle sample_handle, unsigned int, int frequency, int volume, int pan,
    int loop)
{
    Sample* sample = lookup(g_samples, KIND_SAMPLE, sample_handle);
    if (!sample)
        return fail(BASS_ERROR_HANDLE);
    int sample_index = (int)(sample - g_samples);

    // Reclaim finished channels; when `max` still play, override one
    // (BASS_SAMPLE_OVER_POS: the longest playing) or fail.
    int playing = 0, oldest = -1;
    for (int i = 0; i < CAPACITY; ++i) {
        if (!g_channels[i].used || g_channels[i].sample != sample_index)
            continue;
        if (!channel_active(i)) {
            g_channels[i].used = false;
            continue;
        }
        ++playing;
        if (oldest < 0 || g_channels[i].serial < g_channels[oldest].serial)
            oldest = i;
    }
    if (playing >= (int)sample->max) {
        if ((sample->flags & BASS_SAMPLE_OVER_MASK) == 0)
            return fail(BASS_ERROR_NOCHAN);
        stop_channel(oldest);
    }

    int index = allocate(g_channels);
    if (index < 0)
        return fail(BASS_ERROR_NOCHAN);
    g_channels[index].sample = sample_index;
    g_channels[index].serial = ++g_serial;
    float gain = volume < 0 ? 1.0f : (volume > 100 ? 100 : volume) / 100.0f;
    float balance = pan < -100 || pan > 100 ? 0.0f : pan / 100.0f;
    bool looped = loop < 0 ? (sample->flags & BASS_SAMPLE_LOOP) != 0 : loop != 0;
    audio_play(handle(KIND_CHANNEL, index), sample->sound, AUDIO_BUS_SAMPLE, gain, balance,
        frequency > 0 ? frequency : 0, looped);
    return handle(KIND_CHANNEL, index);
}

int __stdcall bass_sample_stop(BassHandle h)
{
    int sample_index;
    if (Sample* sample = lookup(g_samples, KIND_SAMPLE, h))
        sample_index = (int)(sample - g_samples);
    else if (Channel* channel = lookup(g_channels, KIND_CHANNEL, h))
        sample_index = channel->sample;
    else
        return fail(BASS_ERROR_HANDLE);
    for (int i = 0; i < CAPACITY; ++i)
        if (g_channels[i].used && g_channels[i].sample == sample_index)
            stop_channel(i);
    return 1;
}

BassHandle __stdcall bass_stream_create_file(int from_memory, const void* source, unsigned int offset,
    unsigned int length, unsigned int)
{
    int index = allocate(g_streams);
    if (index < 0)
        return fail(BASS_ERROR_NOCHAN);
    int sound = create_sound(from_memory, source, offset, length);
    if (!sound) {
        g_streams[index].used = false;
        return fail(BASS_ERROR_FILEOPEN);
    }
    g_streams[index].sound = sound;
    return handle(KIND_STREAM, index);
}

int __stdcall bass_stream_play(BassHandle stream_handle, int, unsigned int flags)
{
    Stream* stream = lookup(g_streams, KIND_STREAM, stream_handle);
    if (!stream)
        return fail(BASS_ERROR_HANDLE);
    audio_play(stream_handle, stream->sound, AUDIO_BUS_STREAM, 1.0f, 0.0f, 0, (flags & BASS_SAMPLE_LOOP) != 0);
    return 1;
}

int __stdcall bass_stream_pre_buf(BassHandle) { return 1; }

void __stdcall bass_stream_free(BassHandle stream_handle)
{
    if (Stream* stream = lookup(g_streams, KIND_STREAM, stream_handle)) {
        audio_stop(stream_handle);
        audio_destroy_sound(stream->sound);
        stream->used = false;
    }
}

int __stdcall bass_channel_stop(BassHandle h)
{
    if (lookup(g_streams, KIND_STREAM, h)) {
        audio_stop(h);
        return 1;
    }
    if (Channel* channel = lookup(g_channels, KIND_CHANNEL, h)) {
        stop_channel((int)(channel - g_channels));
        return 1;
    }
    return fail(BASS_ERROR_HANDLE);
}

unsigned int __stdcall bass_channel_is_active(BassHandle h)
{
    if (lookup(g_streams, KIND_STREAM, h))
        return audio_channel_active(h) ? BASS_ACTIVE_PLAYING : BASS_ACTIVE_STOPPED;
    if (Channel* channel = lookup(g_channels, KIND_CHANNEL, h))
        return channel_active((int)(channel - g_channels)) ? BASS_ACTIVE_PLAYING : BASS_ACTIVE_STOPPED;
    if (Sample* sample = lookup(g_samples, KIND_SAMPLE, h)) {
        int sample_index = (int)(sample - g_samples);
        for (int i = 0; i < CAPACITY; ++i)
            if (g_channels[i].used && g_channels[i].sample == sample_index && channel_active(i))
                return BASS_ACTIVE_PLAYING;
    }
    return BASS_ACTIVE_STOPPED;
}

// Bound by the game but never called; they answer as an idle channel would.
float __stdcall bass_channel_bytes2_seconds(BassHandle, BassQword) { return 0; }
BassQword __stdcall bass_channel_get_position(BassHandle) { return 0; }
unsigned int __stdcall bass_channel_get_level(BassHandle) { return 0; }
unsigned int __stdcall bass_channel_get_data(BassHandle, void*, unsigned int) { return 0; }
BassHandle __stdcall bass_channel_set_sync(BassHandle, unsigned int, BassQword, BassSyncProc, unsigned int) { return 0; }
int __stdcall bass_channel_remove_sync(BassHandle, BassHandle) { return 1; }

struct Export {
    const char* name;
    void* function;
};

const Export kExports[] = {
    {"BASS_Init", (void*)(BassInitFn)bass_init},
    {"BASS_SetConfig", (void*)(BassSetConfigFn)bass_set_config},
    {"BASS_Free", (void*)(BassFreeFn)bass_free},
    {"BASS_Update", (void*)(BassUpdateFn)bass_update},
    {"BASS_StreamCreateFile", (void*)(BassStreamCreateFileFn)bass_stream_create_file},
    {"BASS_StreamPlay", (void*)(BassStreamPlayFn)bass_stream_play},
    {"BASS_StreamPreBuf", (void*)(BassStreamPreBufFn)bass_stream_pre_buf},
    {"BASS_ChannelStop", (void*)(BassChannelStopFn)bass_channel_stop},
    {"BASS_StreamFree", (void*)(BassStreamFreeFn)bass_stream_free},
    {"BASS_SampleLoad", (void*)(BassSampleLoadFn)bass_sample_load},
    {"BASS_SamplePlayEx", (void*)(BassSamplePlayExFn)bass_sample_play_ex},
    {"BASS_SampleStop", (void*)(BassSampleStopFn)bass_sample_stop},
    {"BASS_Stop", (void*)(BassStopFn)bass_stop},
    {"BASS_Start", (void*)(BassStartFn)bass_start},
    {"BASS_Pause", (void*)(BassPauseFn)bass_pause},
    {"BASS_ChannelBytes2Seconds", (void*)(BassChannelBytes2SecondsFn)bass_channel_bytes2_seconds},
    {"BASS_ChannelGetLevel", (void*)(BassChannelGetLevelFn)bass_channel_get_level},
    {"BASS_ChannelGetData", (void*)(BassChannelGetDataFn)bass_channel_get_data},
    {"BASS_ChannelSetSync", (void*)(BassChannelSetSyncFn)bass_channel_set_sync},
    {"BASS_ChannelGetPosition", (void*)(BassChannelGetPositionFn)bass_channel_get_position},
    {"BASS_ErrorGetCode", (void*)(BassErrorGetCodeFn)bass_error_get_code},
    {"BASS_ChannelRemoveSync", (void*)(BassChannelRemoveSyncFn)bass_channel_remove_sync},
    {"BASS_ChannelIsActive", (void*)(BassChannelIsActiveFn)bass_channel_is_active},
};

char g_bass_library;  // the module handle LoadLibraryA returns

}  // namespace

// The Win32 loader calls initialize_bass_audio_backend makes. Only the
// extracted BASS DLL is ever loaded.
extern "C" void* __stdcall LoadLibraryA(char*)
{
    return &g_bass_library;
}

extern "C" void* __stdcall GetProcAddress(void* module, char* name)
{
    if (module != &g_bass_library)
        return 0;
    for (const Export& entry : kExports)
        if (strcmp(entry.name, name) == 0)
            return entry.function;
    fprintf(stderr, "snail: BASS function %s is not emulated\n", name);
    return 0;
}

extern "C" int __stdcall FreeLibrary(void* module)
{
    return module == &g_bass_library;
}
