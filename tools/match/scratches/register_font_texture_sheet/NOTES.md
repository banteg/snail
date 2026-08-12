# FontLoad

`FontLoad(char*, int, float, float)` owns the Windows routine at `0x449f50`.
The recovery is semantic-complete at 75.41%: 275 candidate versus 274 target
instructions, with all 57 references clean.

The Windows version scans marker pixels, fills the 128 glyph lanes, handles a
split texture page, stores scale/shadow metadata, and returns the registered
font index. Android and iOS export the same authored `Font.o` name but use a
metadata-driven `0xa28` sheet and a void return; Windows locally proves its
integer result and `0x828` sheet. The remaining delta is compiler allocation
of the glyph slot versus split coordinate, not missing behavior.

The directory and manifest retain `register_font_texture_sheet` as the stable
matcher identifier.
