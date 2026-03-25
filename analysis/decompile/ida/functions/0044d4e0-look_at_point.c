/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: look_at_point @ 0x44d4e0 */
/* selector: look_at_point */

void __thiscall sub_44D4E0(float *this, float *a2)
{
  double v2; // st7
  float v3; // [esp+0h] [ebp-18h]
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+8h] [ebp-10h]
  _DWORD v6[3]; // [esp+Ch] [ebp-Ch] BYREF

  v3 = *a2 - *(this + 12);
  v4 = a2[1] - *(this + 13);
  v2 = a2[2] - *(this + 14);
  *(float *)&v6[1] = v4;
  *(float *)v6 = v3;
  v5 = v2;
  *(float *)&v6[2] = v5;
  set_matrix_z_direction((int)this, v2, v6);
}

