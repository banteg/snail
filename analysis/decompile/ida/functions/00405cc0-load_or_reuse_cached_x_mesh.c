/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_or_reuse_cached_x_mesh @ 0x405cc0 */
/* selector: load_or_reuse_cached_x_mesh */

// Searches the shared runtime X-mesh bank by name and returns the existing index on a hit; on a miss it appends a new entry, allocates its backing object from the global object list, loads the mesh, and returns the new index.
int __thiscall load_or_reuse_cached_x_mesh(char *this, char *ArgList)
{
  int v3; // edi
  char *v4; // ebx
  _DWORD *v5; // eax
  int v6; // eax

  v3 = 0;
  if ( *((int *)this + 1) <= 0 )
  {
LABEL_5:
    rstrcpy_checked_ascii(this + 188 * *((_DWORD *)this + 1) + 68, ArgList);
    v5 = add_object_to_list(unk_4B7648);
    set_bod_object((_DWORD *)this + 47 * *((_DWORD *)this + 1) + 2, (int)v5);
    load_x_mesh(ArgList, *((int **)this + 47 * v3 + 11), 1);
    v6 = *((_DWORD *)this + 1) + 1;
    *((_DWORD *)this + 1) = v6;
    return v6 - 1;
  }
  else
  {
    v4 = this + 68;
    while ( !sub_44E6C0(ArgList, v4) )
    {
      ++v3;
      v4 += 188;
      if ( v3 >= *((_DWORD *)this + 1) )
        goto LABEL_5;
    }
    return v3;
  }
}

