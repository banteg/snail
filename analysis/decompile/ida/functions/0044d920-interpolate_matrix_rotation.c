/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: interpolate_matrix_rotation @ 0x44d920 */
/* selector: interpolate_matrix_rotation */

// Exact void `TransformMatrix::interpolate_matrix_rotation(float)` implementation of the authored mobile `tMatrix::Interpolate(float)` member. It extracts and copy-assigns the current rotation as a quaternion, scales its axis angle, and rebuilds the matrix when the rotation is nonzero.
void __thiscall interpolate_matrix_rotation(TransformMatrix *transform, float alpha)
{
  Quaternion self; // [esp+8h] [ebp-70h] BYREF
  Quaternion out; // [esp+18h] [ebp-60h] BYREF
  AxisAngle axis; // [esp+28h] [ebp-50h] BYREF
  TransformMatrix v6; // [esp+38h] [ebp-40h] BYREF

  noop_this_constructor(&self);
  noop_this_constructor(&axis);
  initialize_quaternion_from_matrix(&out, transform);
  self = out;
  if ( out.x > -0.001 && out.x < 0.001 )
    self.x = 0.0;
  if ( self.y > -0.001 && self.y < 0.001 )
    self.y = 0.0;
  if ( self.z > -0.001 && self.z < 0.001 )
    self.z = 0.0;
  if ( self.x == 0.0 && self.y == 0.0 && self.z == 0.0 )
  {
    initialize_matrix_from_quaternion(&v6, &self);
    qmemcpy(transform, &v6, sizeof(TransformMatrix));
  }
  else
  {
    initialize_axis_from_quaternion(&axis, &self);
    if ( axis.angle != 0.0 )
    {
      axis.angle = axis.angle * alpha;
      initialize_quaternion_from_axis(&self, &axis);
      initialize_matrix_from_quaternion(&v6, &self);
      qmemcpy(transform, &v6, sizeof(TransformMatrix));
    }
  }
}
