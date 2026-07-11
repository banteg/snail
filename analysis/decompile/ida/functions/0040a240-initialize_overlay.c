/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_overlay @ 0x40a240 */
/* selector: initialize_overlay */

TransformMatrix *__thiscall initialize_overlay(int this)
{
  TransformMatrix *v2; // edx

  *(_DWORD *)(this + 324) = 0;
  *(_DWORD *)(this + 328) = 968858832;
  set_matrix_identity((TransformMatrix *)(this + 56));
  *(_DWORD *)(this + 320) = 1108869120;
  set_matrix_identity((TransformMatrix *)(this + 184));
  return invert_matrix_from_source((TransformMatrix *)(this + 256), v2);
}

