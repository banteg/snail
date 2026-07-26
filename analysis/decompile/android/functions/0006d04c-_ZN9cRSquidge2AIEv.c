/*
 * mangled: _ZN9cRSquidge2AIEv
 * demangled: cRSquidge::AI()
 * address: 0006d04c
 * size: 412
 */

/* cRSquidge::AI() */

void __thiscall cRSquidge::AI(cRSquidge *this)

{
  bool bVar1;
  float fVar2;
  float fVar3;

  fVar3 = *(float *)(this + 4);
  if (fVar3 != 0.0) {
    fVar2 = fVar3 + *(float *)(this + 8);
    *(float *)(this + 8) = fVar2;
    fVar3 = (fVar3 + fVar2 * -0.15) * 0.82;
    fVar2 = -fVar2;
    *(float *)(this + 4) = fVar3;
    *(float *)this = fVar2;
    if (fVar3 < 0.0) {
      bVar1 = -0.001 < fVar3;
    }
    else if (0.001 <= fVar3) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      if (fVar2 < 0.0) {
        bVar1 = -0.001 < fVar2;
      }
      else if (0.001 <= fVar2) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      if (bVar1) {
        *(undefined4 *)this = 0;
        *(undefined4 *)(this + 4) = 0;
      }
    }
  }
  fVar3 = *(float *)(this + 0x10);
  if (fVar3 == 0.0) {
    return;
  }
  fVar2 = fVar3 + *(float *)(this + 0x14);
  *(float *)(this + 0x14) = fVar2;
  fVar3 = (fVar3 + fVar2 * -0.15) * 0.82;
  fVar2 = -fVar2;
  *(float *)(this + 0x10) = fVar3;
  *(float *)(this + 0xc) = fVar2;
  if (fVar3 < 0.0) {
    if (fVar3 <= -0.001) {
      return;
    }
  }
  else if (0.001 <= fVar3) {
    return;
  }
  if (0.0 <= fVar2) {
    if (fVar2 < 0.001) {
      *(undefined4 *)(this + 0xc) = 0;
      *(undefined4 *)(this + 0x10) = 0;
    }
    return;
  }
  if (-0.001 < fVar2) {
    *(undefined4 *)(this + 0xc) = 0;
    *(undefined4 *)(this + 0x10) = 0;
  }
  return;
}
