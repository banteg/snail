# register_font_texture_sheet_wrapper

Small cdecl wrapper at `0x432d20`, called by `initialize_game_assets_and_world`
for the `Objects/Font/Font-menu-hover.tga` setup path. It forwards the four
stack dwords directly to `register_font_texture_sheet` at `0x449f50`.

The shared callee signature now keeps both scale arguments as floats. The atlas
registrar's direct `FontSheet::width_scale` store is codegen-identical to the
old raw-bit workaround, and this wrapper remains exact while consuming the
shared declaration from `font_system.h`.
