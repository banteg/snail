// Windows cRTrack owner. iOS symbols preserve cRTrack::Change(int), while the
// Windows object owns the four track/slide texture pairs used by level setup.
#ifndef TRACK_H
#define TRACK_H

#include "object_render_types.h"
#include "sprite.h"

class Track {
public:
    void Change(int texture_set); // @ 0x410730, cRTrack::Change(int)

    TextureRef* track_textures[4]; // +0x00
    TextureRef* slide_textures[4]; // +0x10
    int current_texture_set; // +0x20
};

typedef char Track_must_be_0x24[(sizeof(Track) == 0x24) ? 1 : -1];

#endif
