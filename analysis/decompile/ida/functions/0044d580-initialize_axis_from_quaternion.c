/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_axis_from_quaternion @ 0x44d580 */
/* selector: initialize_axis_from_quaternion */

// Converts a quaternion into axis-angle form by normalizing xyz against `sin(theta / 2)` and storing `angle = 2 * acos(w)`. Android symbols match this helper to `tAxis::operator=(const tQuaternian&)`.
void __thiscall sub_44D580(float *this, float *a2)
{
  float v4; // [esp+10h] [ebp+4h]

  v4 = arccosine(a2[3]);
  *this = *a2 / sine(v4);
  *(this + 1) = a2[1] / sine(v4);
  *(this + 2) = a2[2] / sine(v4);
  *(this + 3) = v4 + v4;
}

