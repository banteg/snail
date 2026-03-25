/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_quaternion_from_axis @ 0x44d530 */
/* selector: initialize_quaternion_from_axis */

// Builds a quaternion from an axis-angle record by applying `sin(angle / 2)` to the xyz axis and `cos(angle / 2)` to `w`. Android symbols match this helper to `tQuaternian::tQuaternian(const tAxis&)`.
void __thiscall sub_44D530(float *this, float *a2)
{
  double v3; // st7
  float v4; // [esp+0h] [ebp-Ch]
  float v5; // [esp+0h] [ebp-Ch]

  v4 = a2[3] * 0.5;
  v3 = sine(v4);
  *this = v3 * *a2;
  *(this + 1) = v3 * a2[1];
  *(this + 2) = v3 * a2[2];
  v5 = a2[3] * 0.5;
  *(this + 3) = cosine(v5);
}

