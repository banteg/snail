// initialize_overlay @ 0x40a240 (thiscall, ret)

#include "transform_matrix.h"

class Overlay {
public:
    void initialize_overlay();

    char unknown_000[0x38];
    TransformMatrix screen_matrix; // +0x38
    char unknown_078[0xb8 - 0x078];
    TransformMatrix world_matrix; // +0xb8
    char unknown_0f8[0x100 - 0x0f8];
    TransformMatrix inverse_screen_matrix; // +0x100
    float field_140; // +0x140
    int field_144; // +0x144
    float field_148; // +0x148
};

void Overlay::initialize_overlay()
{
    field_144 = 0;
    *(int*)&field_148 = 0x39bf9cd0;
    set_matrix_identity(&screen_matrix);
    field_140 = 38.0f;
    set_matrix_identity(&world_matrix);
    inverse_screen_matrix.invert_matrix_from_source(&screen_matrix);
}
