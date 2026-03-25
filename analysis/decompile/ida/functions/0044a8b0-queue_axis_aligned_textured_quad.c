/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_axis_aligned_textured_quad @ 0x44a8b0 */
/* selector: queue_axis_aligned_textured_quad */

// Appends one axis-aligned textured quad with default `[0,1]` UVs into the shared 2D render queue, using the supplied texture, authored rectangle, tint, and render flags.
void __cdecl sub_44A8B0(int a1, int a2, int a3, int a4, int a5, int a6, int *a7, int a8)
{
  int v8; // ecx
  int v9; // eax
  int *v10; // esi
  int v11; // edi

  if ( unk_4B7236 )
  {
    v8 = unk_777B24;
    if ( unk_777B24 == 1024 )
    {
      report_errorf(aFontPrintBuffe);
    }
    else if ( *(float *)&a4 != 0.0 && *(float *)&a5 != 0.0 )
    {
      v9 = 33 * unk_777B24;
      unk_7544E8[v9] = a6 | 2;
      unk_754538[v9] = a1;
      v10 = &unk_754554[33 * v8];
      *v10 = *a7;
      v10[1] = a7[1];
      v10[2] = a7[2];
      v11 = a7[3];
      unk_777B24 = v8 + 1;
      v10[3] = v11;
      unk_7544EC[v9] = a2;
      unk_7544F0[v9] = a3;
      unk_75453C[v9] = a4;
      unk_754540[v9] = a5;
      unk_754544[v9] = 0;
      unk_754548[v9] = 0;
      unk_75454C[v9] = 1065353216;
      unk_754550[v9] = 1065353216;
      unk_754564[v9] = a8;
      unk_754568[v9] = 0;
    }
  }
}

