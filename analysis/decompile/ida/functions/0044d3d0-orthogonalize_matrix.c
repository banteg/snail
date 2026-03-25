/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: orthogonalize_matrix @ 0x44d3d0 */
/* selector: orthogonalize_matrix */

int __thiscall sub_44D3D0(float *this)
{
  float *v2; // edi
  float *v3; // ebx

  v2 = this + 4;
  v3 = this + 8;
  normalize_vector(this);
  normalize_vector(v2);
  normalize_vector(v3);
  cross_vectors(this, v2, v3);
  return cross_vectors(v3, this, v2);
}

