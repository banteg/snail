/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sample_tga_pixel_rgb @ 0x44e780 */

0044e784        int32_t ecx = 0
0044e78b        ecx.w = image->height
0044e78f        uint8_t bits_per_pixel = image->bits_per_pixel
0044e794        int32_t esi_1 = 0
0044e796        esi_1.w = image->width
0044e7b0        int32_t ecx_5 = ((ecx - y - 1) * esi_1 + x) * (zx.d(bits_per_pixel) u>> 3)
0044e7b5        if (bits_per_pixel == 8)
0044e7b7        int32_t eax = 0
0044e7b9        eax.b = (&image->pixels)[ecx_5]
0044e7cf        return (eax << 8 | eax) << 8 | eax
0044e7d0        int32_t eax_5 = 0
0044e7d2        eax_5.b = (&image->pixels)[ecx_5]
0044e7d8        int32_t eax_6 = 0
0044e7da        eax_6.b = *(ecx_5 + image + 0x13)
0044e7e0        int32_t eax_7 = 0
0044e7e2        eax_7.b = *(ecx_5 + image + 0x14)
0044e7f6        return (eax_5 << 8 | eax_6) << 8 | eax_7
