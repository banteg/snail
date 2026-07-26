/*
 * mangled: _ZN7tMatrix6LookAtERK7tVector
 * demangled: tMatrix::LookAt(tVector const&)
 * address: 00028bc4
 * size: 72
 */

/* tMatrix::LookAt(tVector const&) */

void __thiscall tMatrix::LookAt(tMatrix *this,tVector *param_1)

{
  float local_14;
  float local_10;
  float local_c;

  local_c = *(float *)(param_1 + 8) - *(float *)(this + 0x38);
  local_14 = *(float *)param_1 - *(float *)(this + 0x30);
  local_10 = *(float *)(param_1 + 4) - *(float *)(this + 0x34);
  SetZDir(this,(tVector *)&local_14);
  return;
}
