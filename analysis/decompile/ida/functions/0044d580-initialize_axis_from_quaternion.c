/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_axis_from_quaternion @ 0x44d580 */
/* selector: initialize_axis_from_quaternion */

// Stable Windows harness identity for the exact void `AxisAngle::operator=(const Quaternion&)` conversion retained by Android as `tAxis::operator=(const tQuaternian&)`. It normalizes xyz against `sin(theta / 2)` and stores `angle = 2 * acos(w)`.
void __thiscall initialize_axis_from_quaternion(AxisAngle *out, const Quaternion *quaternion)
{
  float quaterniona; // [esp+10h] [ebp+4h]

  quaterniona = arccosine(quaternion->w);
  out->x = quaternion->x / sine(quaterniona);
  out->y = quaternion->y / sine(quaterniona);
  out->z = quaternion->z / sine(quaterniona);
  out->angle = quaterniona + quaterniona;
}
