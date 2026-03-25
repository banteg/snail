/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_font_text_instance @ 0x44a790 */
/* selector: queue_font_text_instance */

// Copies one text run into the shared font print string buffer and appends the matching queued font-text instance record with its font, position, alignment, colors, and render flags.
char __cdecl sub_44A790(_BYTE *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int *a9, int a10, char a11)
{
  char result; // al
  int v12; // eax
  _BYTE *v13; // ecx
  int *v14; // edx
  _BYTE *v15; // eax

  result = unk_4B7236;
  if ( unk_4B7236 && unk_777B24 != 1024 )
  {
    v12 = 33 * unk_777B24;
    unk_7544E8[v12] = a8 | 1;
    unk_754524[v12] = a2;
    unk_754528[v12] = a3;
    unk_7544EC[v12] = a4;
    unk_7544F0[v12] = a5;
    unk_754530[v12] = a6;
    unk_754534[v12] = a7;
    v13 = (_BYTE *)unk_7772F0;
    unk_75452C[v12] = unk_7772F0;
    v14 = &unk_754554[v12];
    unk_754554[v12] = *a9;
    v14[1] = a9[1];
    v14[2] = a9[2];
    v14[3] = a9[3];
    unk_75451C[v12] = a10;
    unk_754520[v12 * 4] = a11;
    v15 = a1;
    if ( *a1 )
    {
      while ( v13 - (_BYTE *)&unk_753CE8 <= 2046 )
      {
        *v13 = *v15;
        v13 = (_BYTE *)(unk_7772F0 + 1);
        ++v15;
        ++unk_7772F0;
        if ( !*v15 )
          goto LABEL_6;
      }
      *v13 = 0;
      return ++unk_7772F0;
    }
    else
    {
LABEL_6:
      *v13 = 0;
      result = unk_777B24 + 1;
      ++unk_7772F0;
      ++unk_777B24;
    }
  }
  return result;
}

