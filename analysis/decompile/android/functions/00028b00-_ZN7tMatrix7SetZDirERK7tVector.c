/*
 * mangled: _ZN7tMatrix7SetZDirERK7tVector
 * demangled: tMatrix::SetZDir(tVector const&)
 * address: 00028b00
 * size: 188
 */

/* tMatrix::SetZDir(tVector const&) */

void __thiscall tMatrix::SetZDir(tMatrix *this,tVector *param_1)

{
  float fVar1;
  float local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  float local_14;

  fVar1 = (float)tVector::Normalize((tVector *)&local_28,param_1);
  if (fVar1 != 0.0) {
    *(float *)(this + 0x20) = local_28;
    *(undefined4 *)(this + 0x24) = local_24;
    *(float *)(this + 0x28) = local_20;
    if ((local_28 == 0.0) && (local_20 == 0.0)) {
      local_14 = 0.0;
      local_1c = 1.0;
    }
    else {
      local_14 = -local_28;
      local_1c = local_20;
    }
    local_18 = 0;
    tVector::Normalize((tVector *)&local_1c);
    *(float *)this = local_1c;
    *(undefined4 *)(this + 4) = local_18;
    *(float *)(this + 8) = local_14;
    tVector::Cross((tVector *)(this + 0x10),(tVector *)&local_28,(tVector *)&local_1c);
  }
  return;
}
