// rotate_object_facequad_uv_pairs @ 0x430a30 (fastcall)

#include "object_render_types.h"

void __fastcall rotate_object_facequad_uv_pairs(ObjectFaceQuad* quad)
{
    float first_u = quad->uv[0].u;
    quad->uv[0].u = quad->uv[1].u;
    quad->uv[1].u = quad->uv[2].u;
    quad->uv[2].u = quad->uv[3].u;
    quad->uv[3].u = first_u;

    float first_v = quad->uv[0].v;
    quad->uv[0].v = quad->uv[1].v;
    quad->uv[1].v = quad->uv[2].v;
    quad->uv[2].v = quad->uv[3].v;
    quad->uv[3].v = first_v;
}
