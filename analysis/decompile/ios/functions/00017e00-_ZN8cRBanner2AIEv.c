/*
 * mangled: _ZN8cRBanner2AIEv
 * demangled: cRBanner::AI()
 * address: 00017e00
 * size: 188
 */

/* cRBanner::AI() */

void __thiscall cRBanner::AI(cRBanner *this)

{
  float fVar1;
  float fVar2;

  if (*(int *)(this + 0x2c) == 0) {
    if (40.0 <= *(float *)(*(int *)(this + 0x48) + 100)) {
LAB_00017eac:
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
      goto LAB_00017e3c;
    }
  }
  else {
    if (*(int *)(this + 0x2c) != 1) goto LAB_00017e3c;
    if (48.0 <= *(float *)(this + 0x18) - *(float *)(*(int *)(this + 0x48) + 100))
    goto LAB_00017eac;
  }
  *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
LAB_00017e3c:
  fVar1 = *(float *)(this + 0x4c) + *(float *)(this + 0x50);
  *(float *)(this + 0x4c) = fVar1;
  fVar2 = fVar1;
  if (1.0 < fVar1) {
    fVar2 = fVar1 - 1.0;
  }
  if (1.0 < fVar1) {
    *(float *)(this + 0x4c) = fVar2;
  }
  fVar2 = (float)Sin(fVar2 * 6.2831855);
  *(float *)(this + 0x14) = fVar2 * 0.26;
  return;
}
