# register_font_texture_sheet_wrapper

Small cdecl wrapper at `0x432d20`, called by `initialize_game_assets_and_world`
for the `Objects/Font/Font-menu-hover.tga` setup path. It forwards the four
stack dwords directly to `register_font_texture_sheet` at `0x449f50`.

The callee scratch names the third parameter `width_scale_bits` because the
atlas registrar stores the raw float bits. This wrapper keeps the public
callsite shape as `float width_scale, float height_scale`, which reproduces the
native forwarding sequence.
