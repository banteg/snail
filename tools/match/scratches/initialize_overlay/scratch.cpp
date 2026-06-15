// initialize_overlay @ 0x40a240 (thiscall, ret)

class TransformMatrix {
public:
    void set_matrix_identity();
    void invert_matrix_from_source(TransformMatrix* source);
};

class Overlay {
public:
    void initialize_overlay();

    char unknown_000[0x38];
    char screen_matrix[0x40]; // +0x38
    char unknown_078[0xb8 - 0x078];
    char world_matrix[0x40]; // +0xb8
    char unknown_0f8[0x100 - 0x0f8];
    char inverse_screen_matrix[0x40]; // +0x100
    float field_140; // +0x140
    int field_144; // +0x144
    float field_148; // +0x148
};

void Overlay::initialize_overlay()
{
    field_144 = 0;
    *(int*)&field_148 = 0x39bf9cd0;
    ((TransformMatrix*)screen_matrix)->set_matrix_identity();
    field_140 = 38.0f;
    ((TransformMatrix*)world_matrix)->set_matrix_identity();
    ((TransformMatrix*)inverse_screen_matrix)->invert_matrix_from_source((TransformMatrix*)screen_matrix);
}
