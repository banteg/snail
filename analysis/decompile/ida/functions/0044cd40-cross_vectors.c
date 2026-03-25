/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: cross_vectors @ 0x44cd40 */
/* selector: cross_vectors */

// Computes the 3D cross product of two vectors into a destination output. Android symbols match this helper to `tVector::Cross(const tVector&, const tVector&)`.
int32_t __thiscall cross_vectors(Vec3 *out, Vec3 *lhs, Vec3 *rhs)
{
  int32_t result; // eax

  if ( (dword_777B2C[259] & 1) == 0 )
  {
    LOBYTE(dword_777B2C[259]) |= 1u;
    atexit(nullsub_2);
  }
  *(float *)&dword_777B2C[8469] = lhs->y * rhs->z - rhs->y * lhs->z;
  *(float *)&dword_777B2C[8470] = lhs->z * rhs->x - lhs->x * rhs->z;
  result = dword_777B2C[8469];
  *(float *)&dword_777B2C[8471] = rhs->y * lhs->x - lhs->y * rhs->x;
  LODWORD(out->x) = dword_777B2C[8469];
  LODWORD(out->y) = dword_777B2C[8470];
  LODWORD(out->z) = dword_777B2C[8471];
  return result;
}

