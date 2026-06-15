// set_backdrop_texture_target @ 0x410f40 (thiscall, ret 0x4)

class BackdropRenderer {
public:
    int set_backdrop_texture_target(int texture_id);

    char unknown_000[0x68c];
    float primary_blend; // +0x68c
    int field_690;
    int previous_primary_texture; // +0x694
    int current_primary_texture; // +0x698
    char unknown_69c[0x6ac - 0x69c];
    float secondary_blend; // +0x6ac
    int field_6b0;
    int previous_secondary_texture; // +0x6b4
    int current_secondary_texture; // +0x6b8
};

int BackdropRenderer::set_backdrop_texture_target(int texture_id)
{
    primary_blend = 1.0f - primary_blend;
    previous_primary_texture = current_primary_texture;
    int old_secondary = current_secondary_texture;
    current_primary_texture = texture_id;
    previous_secondary_texture = old_secondary;
    secondary_blend = 1.0f - secondary_blend;
    current_secondary_texture = texture_id;
    return texture_id;
}
