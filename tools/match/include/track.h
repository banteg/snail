// Windows cRTrack owner. Android and iOS preserve cRTrack::Change(int), while
// the Windows object independently proves this exact four-pair layout.
#ifndef TRACK_H
#define TRACK_H

#include "object_render_types.h"
#include "sprite.h"

class cRTrack {
public:
    void Change(int texture_set); // @ 0x410730, cRTrack::Change(int)

    cRTexture* track_textures[4]; // +0x00
    cRTexture* slide_textures[4]; // +0x10
    int current_texture_set; // +0x20
};

typedef cRTrack Track;
typedef char cRTrack_must_be_0x24[(sizeof(cRTrack) == 0x24) ? 1 : -1];

#endif
