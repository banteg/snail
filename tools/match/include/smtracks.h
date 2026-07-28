// Animated SMTrack height-field owner embedded between LandscapeManager and
// cRSMTracks. The inherited BodBase borrows the active mesh object; its
// Movie selects replacement textures for that mesh.
#ifndef SMTRACKS_H
#define SMTRACKS_H

#include "bod_types.h"
#include "movie.h"

void __cdecl sample_smtrack_heightmap(
    Object* source,
    float base,
    float scale,
    TextureRef* replacement,
    bool cubic); // @ 0x41a360; mobile ObjectProcLandScapeUpdate

// Windows layout of the authored cross-port cRFace owner. This is the animated
// landscape-height face, not an ObjectFaceQuad.
class Face : public BodBase {
public:
    void update_smtracks(); // @ 0x441f60

    Movie movie; // +0x38
};

typedef char Face_must_be_0x128[
    (sizeof(Face) == 0x128) ? 1 : -1];

#endif
