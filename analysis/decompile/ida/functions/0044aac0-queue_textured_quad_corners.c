/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_textured_quad_corners @ 0x44aac0 */
/* selector: queue_textured_quad_corners */

// Appends one arbitrary four-corner textured quad with explicit per-corner positions and UV bounds into the shared 2D render queue. The backdrop and galaxy-line renderers use this helper.
char __cdecl sub_44AAC0(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int *a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19)
{
  unsigned int v19; // eax
  int v20; // ecx
  int *v21; // esi
  int v22; // edi

  LOBYTE(v19) = unk_4B7236;
  if ( unk_4B7236 )
  {
    v20 = unk_777B24;
    if ( unk_777B24 == 1024 )
    {
      LOBYTE(v19) = report_errorf(aFontPrintBuffe);
    }
    else
    {
      v19 = 132 * unk_777B24;
      unk_7544E8[v19 / 4] = a12 | 2;
      unk_754538[v19 / 4] = a1;
      v21 = &unk_754554[33 * v20];
      *v21 = *a13;
      v21[1] = a13[1];
      v21[2] = a13[2];
      v22 = a13[3];
      unk_777B24 = v20 + 1;
      v21[3] = v22;
      unk_7544EC[v19 / 4] = a2;
      unk_7544F0[v19 / 4] = a3;
      unk_7544F8[v19 / 4] = a4;
      unk_7544FC[v19 / 4] = a5;
      unk_754504[v19 / 4] = a6;
      unk_754508[v19 / 4] = a7;
      unk_754510[v19 / 4] = a8;
      unk_754514[v19 / 4] = a9;
      unk_75453C[v19 / 4] = 0;
      unk_754540[v19 / 4] = 0;
      unk_754544[v19 / 4] = a14;
      unk_754548[v19 / 4] = a15;
      unk_75454C[v19 / 4] = a16;
      unk_754550[v19 / 4] = a17;
      unk_754564[v19 / 4] = a18;
      unk_754568[v19 / 4] = a19;
    }
  }
  return v19;
}

