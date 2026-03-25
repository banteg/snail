/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: open_logo @ 0x419110 */
/* selector: open_logo */

int __thiscall open_logo(int **this)
{
  int **v1; // esi
  int v2; // edi
  _DWORD *v3; // eax
  int *v4; // eax
  int result; // eax
  int v6; // esi
  int *v7; // edi
  int *texture_ref; // eax
  int v9; // ecx
  int v10; // [esp+8h] [ebp-4084h] BYREF
  char Buffer[128]; // [esp+Ch] [ebp-4080h] BYREF
  int v12[4096]; // [esp+8Ch] [ebp-4000h] BYREF

  v1 = this + 36879;
  v2 = 32;
  do
  {
    v3 = add_object_to_list(unk_4B7648);
    set_bod_object(v1 - 9, (int)v3);
    load_object_definition(aObjectsFont3d, *v1);
    v4 = *v1;
    v1 += 36;
    --v2;
    v4[4] |= 4u;
  }
  while ( v2 );
  enumerate_matching_archive_or_fs_entries(aIntro, aTga, &v10, v12);
  result = v10;
  v6 = 0;
  if ( v10 > 0 )
  {
    v7 = v12;
    do
    {
      sprintf(Buffer, "Intro/%s", (const char *)v7);
      texture_ref = (int *)get_or_create_texture_ref(dword_4B7790, Buffer, 0, 0);
      v9 = *texture_ref;
      v7 += 32;
      BYTE1(v9) = BYTE1(*texture_ref) | 4;
      ++v6;
      *texture_ref = v9;
      result = v10;
    }
    while ( v6 < v10 );
  }
  return result;
}

