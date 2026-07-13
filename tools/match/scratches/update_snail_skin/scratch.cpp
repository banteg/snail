// update_snail_skin @ 0x445cd0 (thiscall, ret)

#include "player.h"

void Snail::update_snail_skin()
{
    for (int index = 0; index < SNAIL_HOTSPOT_COUNT; ++index) {
        TransformMatrix* source_matrix = &snail_hotspot_body.transform;
        Vector3 hotspot = snail_hotspots_local[index];
        if (index >= SNAIL_HOTSPOT_PARCEL_POINT)
            source_matrix = &snail_hotspot_source_matrix_a;

        hotspot.multiply_vector_by_matrix(*source_matrix);
        snail_hotspots_world[index] = hotspot;
    }
}
