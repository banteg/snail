/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_quaternion_from_axis @ 0x44d530 */
/* selector: initialize_quaternion_from_axis */

// Stable Windows harness identity for the exact void `Quaternion::operator=(const AxisAngle&)` conversion. It applies `sin(angle / 2)` to xyz and `cos(angle / 2)` to w. Android exposes the analogous math as `tQuaternian::tQuaternian(const tAxis&)`, but the Windows body does not establish the receiver return required by a constructor.
void __thiscall initialize_quaternion_from_axis(Quaternion *out, const AxisAngle *axis)
{
  double v3; // st7
  float v4; // [esp+0h] [ebp-Ch]
  float v5; // [esp+0h] [ebp-Ch]

  v4 = axis->angle * 0.5;
  v3 = sine(v4);
  out->x = v3 * axis->x;
  out->y = v3 * axis->y;
  out->z = v3 * axis->z;
  v5 = axis->angle * 0.5;
  out->w = cosine(v5);
}
