/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: sample_tga_pixel_rgb @ 0x44e780 */
/* selector: sample_tga_pixel_rgb */

// Exact Windows spelling of `GetTgaColour(cTgaHeader*, int, int)`: samples a bottom-up TGA row, expands 8-bit grayscale, or packs the first three 24-bit pixel bytes as RGB. Android preserves the complete authored helper and begins its RTexture.o run with it; both Windows callsites are the atlas-marker probes in register_font_texture_sheet.
int32_t __cdecl sample_tga_pixel_rgb(TgaImageView *image, int32_t x, int32_t y)
{
  int v3; // ecx

  v3 = (image->bits_per_pixel >> 3) * (x + image->width * (image->height - y - 1));
  if ( image->bits_per_pixel == 8 )
    return image->pixels[v3] | ((image->pixels[v3] | (image->pixels[v3] << 8)) << 8);
  else
    return *(&image[1].id_length + v3) | ((image->pixels[v3 + 1] | (image->pixels[v3] << 8)) << 8);
}
