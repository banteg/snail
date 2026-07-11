/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_overlay @ 0x40a1b0 */
/* selector: update_overlay */

TransformMatrix *__thiscall update_overlay(float *this)
{
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  float *v6; // ebp
  TransformMatrix *v7; // edx

  v2 = *(this + 82) + *(this + 81);
  *(this + 81) = v2;
  if ( v4 | v5 )
  {
    if ( v2 < 0.0 )
      *(this + 81) = v2 + 6.2831855;
  }
  else
  {
    *(this + 81) = v2 - 6.2831855;
  }
  v6 = this + 14;
  set_matrix_identity((TransformMatrix *)(this + 14));
  rotate_matrix_world_z((TransformMatrix *)(this + 14), *(this + 81));
  qmemcpy(this + 46, v6, 0x40u);
  return invert_matrix_from_source((TransformMatrix *)this + 4, v7);
}

