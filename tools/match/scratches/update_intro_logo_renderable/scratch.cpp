// update_intro_logo_renderable @ 0x419a90 (thiscall)

#include "intro_screen_runtime.h"
#include "object_render_types.h"

void LogoLetter::update_intro_logo_renderable()
{
    transform.position += velocity;
    Vector3* position = &transform.position;

    if (position->z > 8.0f) {
        color.a = (1.0f - ((position->z - 8.0f) * 0.125f)) * 0.99900001f;
    } else {
        color.a = 0.99900001f;
    }

    object->flags |= OBJECT_FLAG_REFRESH_TINT_EACH_DRAW;

    if (position->z > 16.0f || position->z < -4.0f) {
        list_flags &= 0xffffffdf;
    } else {
        list_flags |= BOD_FLAG_RENDER_ENABLED;
    }
}
