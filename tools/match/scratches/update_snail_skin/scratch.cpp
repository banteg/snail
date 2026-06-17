// update_snail_skin @ 0x445cd0 (thiscall, ret)

#include "player.h"

void PlayerPresentationController::update_snail_skin()
{
    PlayerPresentationController* presentation = this;
    int index = 0;
    Vector3* world_hotspot = snail_hotspots_world;

    while (1) {
        TransformMatrix* source_matrix = &presentation->snail_hotspot_source_matrix_b;

        Vector3 hotspot;
        hotspot.x = world_hotspot[-19].x;
        hotspot.y = world_hotspot[-19].y;
        hotspot.z = world_hotspot[-19].z;

        if (index >= 11)
            source_matrix = &presentation->snail_hotspot_source_matrix_a;

        hotspot.multiply_vector_by_matrix(*source_matrix);

        Vector3* output = world_hotspot;
        ++index;
        ++world_hotspot;
        output->x = hotspot.x;
        output->y = hotspot.y;
        output->z = hotspot.z;

        if (index >= 19)
            break;

        presentation = this;
    }
}
