// update_smtracks @ 0x441f60 (thiscall, ret)

#include "smtracks.h"

void cRFace::update_smtracks()
{
    movie.advance_frame_sequence();
    object->facequads[0].texture_ref = movie.current_texture_ref;
    sample_smtrack_heightmap(
        object,
        0.0f,
        5.0f,
        movie.current_texture_ref,
        0);
}
