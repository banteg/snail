// update_intro_logo_renderable @ 0x419a90 (thiscall)

#include "intro_screen_runtime.h"
#include "object_render_types.h"

void IntroLogoRenderable::update_intro_logo_renderable()
{
    transform.position += velocity;
    Vector3* position = &transform.position;

    if (position->z > 8.0f) {
        color.a = (1.0f - ((position->z - 8.0f) * 0.125f)) * 0.99900001f;
    } else {
        color.a = 0.99900001f;
    }

    object->flags |= 0x10;

    if (position->z > 16.0f || position->z < -4.0f) {
        list_flags &= 0xffffffdf;
    } else {
        list_flags |= 0x20;
    }
}
