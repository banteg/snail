/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_runtime_cell_at_world_z @ 0x43d480 */
/* selector: get_track_runtime_cell_at_world_z */

// Clamps world z into the generated row array and returns the current runtime cell.
char *__thiscall sub_43D480(void *this, int a2)
{
  __int64 v2; // rax

  v2 = (__int64)*(float *)(a2 + 8);
  if ( (int)v2 < 0 )
    return (char *)byte_5CCAC8 + (_DWORD)this;
  if ( (int)v2 > 3199 )
    LODWORD(v2) = 3199;
  return (char *)byte_5CCAC8 + (_DWORD)this + 244 * v2;
}

