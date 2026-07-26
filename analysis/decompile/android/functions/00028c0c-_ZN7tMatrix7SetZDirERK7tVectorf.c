/*
 * mangled: _ZN7tMatrix7SetZDirERK7tVectorf
 * demangled: tMatrix::SetZDir(tVector const&, float)
 * address: 00028c0c
 * size: 32
 */

/* tMatrix::SetZDir(tVector const&, float) */

void tMatrix::SetZDir(tVector *param_1,float param_2)

{
  tVector *in_r1;
  float fVar1;

  fVar1 = (float)SetZDir((tMatrix *)param_1,in_r1);
  RotLocalZ((tMatrix *)param_1,fVar1);
  return;
}
