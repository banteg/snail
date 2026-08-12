// update_smtracks @ 0x441f60 (thiscall, ret)

#include "smtracks.h"

void cRFace::AI()
{
    movie.AI();
    object->facequads[0].texture_ref = movie.current_texture_ref;
    ObjectProcLandScapeUpdate(
        object,
        0.0f,
        5.0f,
        movie.current_texture_ref,
        0);
}
