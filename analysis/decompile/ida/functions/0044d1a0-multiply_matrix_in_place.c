/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrix_in_place @ 0x44d1a0 */
/* selector: multiply_matrix_in_place */

float *__thiscall sub_44D1A0(void *this, float *a2)
{
  float v3[16]; // [esp+8h] [ebp-40h] BYREF

  qmemcpy(v3, this, sizeof(v3));
  return multiply_matrices((float *)this, v3, a2);
}

