// update_smtracks @ 0x441f60 (thiscall, ret)

#include "smtracks.h"

void SmtrackHeightfieldAnimator::update_smtracks()
{
    frame_sequence.advance_frame_sequence();
    object->facequads[0].texture_ref = frame_sequence.current_texture_ref;
    sample_smtrack_heightmap(
        object,
        0.0f,
        5.0f,
        frame_sequence.current_texture_ref,
        0);
}
