/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_overlay @ 0x40a240 */
/* selector: initialize_overlay */

int __thiscall sub_40A240(int this)
{
  float *v2; // edi

  v2 = (float *)(this + 56);
  *(_DWORD *)(this + 324) = 0;
  *(_DWORD *)(this + 328) = 968858832;
  set_matrix_identity((_DWORD *)(this + 56));
  *(_DWORD *)(this + 320) = 1108869120;
  set_matrix_identity((_DWORD *)(this + 184));
  return invert_matrix_from_source((float *)(this + 256), v2);
}

