// update_intro_logo_renderable @ 0x419a90 (thiscall)

#include "bod_types.h"

struct IntroRenderableObjectView {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
};

class IntroLogoRenderable : public RenderableBod {
public:
    void update_intro_logo_renderable();

    char unknown_078[0x80 - 0x78];
    Vector3 velocity; // +0x80
    char unknown_08c[0x90 - 0x8c];
};

void IntroLogoRenderable::update_intro_logo_renderable()
{
    Vector3* position = &transform.position;
    position->x += velocity.x;
    position->y += velocity.y;
    position->z += velocity.z;

    if (position->z > 8.0f) {
        color.a = (1.0f - ((position->z - 8.0f) * 0.125f)) * 0.99900001f;
    } else {
        color.a = 0.99900001f;
    }

    ((IntroRenderableObjectView*)object)->flags |= 0x10;

    if (position->z > 16.0f || position->z < -4.0f) {
        list_flags &= 0xffffffdf;
    } else {
        list_flags |= 0x20;
    }
}
