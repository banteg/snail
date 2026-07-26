/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_font_texture_sheet_wrapper @ 0x432d20 */
/* selector: register_font_texture_sheet_wrapper */

// Exact Windows cdecl forwarding wrapper for the FONT-MENU-HOVER path, shadow offset, and two scales; it preserves the registrar's Windows integer result even though the sole startup caller discards it.
int32_t __cdecl register_font_texture_sheet_wrapper(
        char *texture_path,
        int32_t shadow_offset_pixels,
        float width_scale,
        float height_scale)
{
  return register_font_texture_sheet(texture_path, shadow_offset_pixels, width_scale, height_scale);
}
