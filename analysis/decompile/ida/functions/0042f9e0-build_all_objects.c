/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_all_objects @ 0x42f9e0 */
/* selector: build_all_objects */

void __usercall sub_42F9E0(int *a1@<ecx>, int a2@<edi>, double a3@<st0>)
{
  int v4; // ebx
  int v5; // edi
  _DWORD *v6; // ecx
  int *v7; // ecx
  int v8; // [esp-4h] [ebp-Ch]

  v4 = 0;
  if ( *a1 > 0 )
  {
    v8 = a2;
    v5 = 0;
    do
    {
      if ( !(v4 % 4) )
        update_loading_screen(MEMORY[0x503290]);
      v6 = (_DWORD *)(v5 + a1[2]);
      if ( v6[11] )
      {
        calc_object_bounding_box(v6);
        sort_object_faces_by_texture_group(v5 + a1[2]);
        calc_object_texture_groups(v5 + a1[2]);
        v7 = (int *)(a1[2] + v5);
        if ( (v7[4] & 0x4000) != 0 )
        {
          calc_object_facequad_normals(v7);
          calc_object_edges(v5 + a1[2], a3);
        }
        build_object_texture_group_buffers((int)a1, (_DWORD *)(v5 + a1[2]), v8);
      }
      ++v4;
      v5 += 220;
    }
    while ( v4 < *a1 );
  }
}

