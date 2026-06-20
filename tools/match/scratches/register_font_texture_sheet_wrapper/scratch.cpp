// register_font_texture_sheet_wrapper @ 0x432d20 (cdecl)

int register_font_texture_sheet(char* texture_path, int font_kind, float width_scale, float height_scale); // @ 0x449f50

int register_font_texture_sheet_wrapper(
    char* texture_path,
    int font_kind,
    float width_scale,
    float height_scale)
{
    return register_font_texture_sheet(texture_path, font_kind, width_scale, height_scale);
}
