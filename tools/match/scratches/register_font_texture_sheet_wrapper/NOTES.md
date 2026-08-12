# register_font_texture_sheet_wrapper

Small cdecl wrapper at `0x432d20`, called by `initialize_game_assets_and_world`
for the `Objects/Font/Font-menu-hover.tga` setup path. It forwards the four
stack dwords directly to `register_font_texture_sheet` at `0x449f50`.

The shared callee signature now keeps both scale arguments as floats. The atlas
registrar's direct `FontSheet::width_scale` store is codegen-identical to the
old raw-bit workaround, and this wrapper remains exact while consuming the
shared declaration from `font_system.h`.

The integer argument is now `shadow_offset_pixels`: the only caller supplies
2, the registrar stores it at `FontSheet +0x824`, and the renderer adds that
value to both coordinates of the offset black glyph pass. The forwarding
wrapper remains exact.

## 2026-08-12 authored RShell owner

The mobile symbol records recover this wrapper's authored public name as
`RShellFontLoad(char*, int, float, float)` in `RShell.o`. iOS preserves a
16-byte wrapper which directly calls `FontLoad` with the same four arguments;
Android preserves the exact demangled symbol as a four-byte tail alias into its
`FontLoad` implementation. Live Windows disassembly likewise shows only the
four argument pushes and call to `register_font_texture_sheet`/`FontLoad`, and
its sole xref remains the `initialize_game_assets_and_world` startup call.

The mobile functions are void, while Windows naturally propagates its
registrar's pre-increment font index in EAX. That return is kept because the
integer transcription is instruction-exact and the sole Windows caller simply
discards it. The authored name and owner transfer without imposing the mobile
return ABI or atlas layout on Windows. The focused scratch remains exact at
11/11 instructions with its call operand resolved.

2026-07-26 cross-port boundary: both mobile `FontLoad` bodies are void, but
changing the Windows registrar to void disrupted its full VC6 allocation and
worsened the registrar's masked-operand residuals. The exact Windows wrapper
naturally forwards the pre-increment sheet index in EAX, even though its sole
startup caller discards it, so the Windows integer contract remains locally
authoritative.
