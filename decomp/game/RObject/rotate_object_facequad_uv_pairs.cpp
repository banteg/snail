// cRFaceQuad::RotateUVCCW() / rotate_object_facequad_uv_pairs @ 0x430a30

#include "object_render_types.h"

void cRFaceQuad::RotateUVCCW()
{
    float first_u = uv[0].u;
    uv[0].u = uv[1].u;
    uv[1].u = uv[2].u;
    uv[2].u = uv[3].u;
    uv[3].u = first_u;

    float first_v = uv[0].v;
    uv[0].v = uv[1].v;
    uv[1].v = uv[2].v;
    uv[2].v = uv[3].v;
    uv[3].v = first_v;
}
