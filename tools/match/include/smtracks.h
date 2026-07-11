// Animated SMTrack height-field owner embedded between LandscapeManager and
// SegmentCatalog. The inherited BodBase borrows the active mesh object; its
// FrameSequence selects replacement textures for that mesh.
#ifndef SMTRACKS_H
#define SMTRACKS_H

#include "bod_types.h"
#include "frame_sequence.h"

void __cdecl sample_smtrack_heightmap(
    Object* source,
    float base,
    float scale,
    TextureRef* replacement,
    char cubic); // @ 0x41a360

class SmtrackHeightfieldAnimator : public BodBase {
public:
    void update_smtracks(); // @ 0x441f60

    FrameSequence frame_sequence; // +0x38
};

typedef char SmtrackHeightfieldAnimator_must_be_0x128[
    (sizeof(SmtrackHeightfieldAnimator) == 0x128) ? 1 : -1];

#endif
