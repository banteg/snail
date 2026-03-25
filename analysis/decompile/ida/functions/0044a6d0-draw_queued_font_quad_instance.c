/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_queued_font_quad_instance @ 0x44a6d0 */
/* selector: draw_queued_font_quad_instance */

// Draws one queued explicit font-quad record by forwarding its stored coordinates, UVs, size mode, angle, and color into the shared immediate textured-quad helper.
int __cdecl sub_44A6D0(int a1)
{
  return draw_textured_quad_immediate(
           LODWORD(unk_78FF90[*(_DWORD *)(a1 + 80)]),
           *(float *)(a1 + 4),
           *(float *)(a1 + 8),
           *(float *)(a1 + 16),
           *(float *)(a1 + 20),
           *(float *)(a1 + 28),
           *(float *)(a1 + 32),
           *(float *)(a1 + 40),
           *(float *)(a1 + 44),
           *(float *)(a1 + 84),
           *(float *)(a1 + 88),
           *(float *)(a1 + 92),
           *(float *)(a1 + 96),
           *(float *)(a1 + 100),
           *(float *)(a1 + 104),
           (float *)(a1 + 108),
           *(_DWORD *)(a1 + 124),
           *(float *)(a1 + 128));
}

