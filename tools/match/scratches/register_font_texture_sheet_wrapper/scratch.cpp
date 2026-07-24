// register_font_texture_sheet_wrapper @ 0x432d20 (cdecl)

#include "font_system.h"

int register_font_texture_sheet_wrapper(
    char* texture_path,
    int shadow_offset_pixels,
    float width_scale,
    float height_scale)
{
    return register_font_texture_sheet(
        texture_path, shadow_offset_pixels, width_scale, height_scale);
}
