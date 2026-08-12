// cRBodPos::cRBodPos @ 0x42f650

#include "bod_types.h"

cRBodPos::cRBodPos()
{
    vtable = &g_renderable_bod_vtable;
    list_flags = RENDER_SCENE_PLAYER_0 | BOD_FLAG_USE_TRANSFORM
        | BOD_FLAG_RENDER_ENABLED;
    transform.Identity();
}
