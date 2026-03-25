/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_axis_aligned_textured_quad_uv @ 0x44a9b0 */
/* selector: queue_axis_aligned_textured_quad_uv */

// Appends one axis-aligned textured quad with explicit UV bounds into the shared 2D render queue. Front-end widgets, progress bars, and the damage gauge all use this helper.
void __cdecl sub_44A9B0(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int *a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13)
{
  int v13; // ecx
  int v14; // eax
  int *v15; // edx
  int v16; // esi

  if ( unk_4B7236 )
  {
    v13 = unk_777B24;
    if ( unk_777B24 == 1024 )
    {
      report_errorf(aFontPrintBuffe);
    }
    else if ( *(float *)&a4 != 0.0 && *(float *)&a5 != 0.0 )
    {
      v14 = 33 * unk_777B24;
      unk_7544E8[v14] = a6 | 2;
      unk_754538[v14] = a1;
      v15 = &unk_754554[33 * v13];
      *v15 = *a7;
      v15[1] = a7[1];
      v15[2] = a7[2];
      v16 = a7[3];
      unk_777B24 = v13 + 1;
      v15[3] = v16;
      unk_7544EC[v14] = a2;
      unk_7544F0[v14] = a3;
      unk_75453C[v14] = a4;
      unk_754540[v14] = a5;
      unk_754544[v14] = a8;
      unk_754548[v14] = a9;
      unk_75454C[v14] = a10;
      unk_754550[v14] = a11;
      unk_754564[v14] = a12;
      unk_754568[v14] = a13;
    }
  }
}

