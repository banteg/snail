/*
 * mangled: _ZN9cRSquidge2AIEv
 * demangled: cRSquidge::AI()
 * address: 0006d04c
 * size: 412
 */

/* cRSquidge::AI() */

void __thiscall cRSquidge::AI(cRSquidge *this)

{
  float fVar1;
  bool bVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;

  fVar6 = DAT_0006d1ec;
  fVar5 = *(float *)(this + 4);
  if (fVar5 != 0.0) {
    fVar4 = fVar5 + *(float *)(this + 8);
    fVar1 = fVar4 * DAT_0006d1e8;
    *(float *)(this + 8) = fVar4;
    fVar6 = (fVar5 + fVar1) * fVar6;
    fVar4 = -fVar4;
    *(float *)(this + 4) = fVar6;
    *(float *)this = fVar4;
    uVar3 = DAT_0006d1f4;
    if (fVar6 < 0.0) {
      bVar2 = DAT_0006d1f8 < fVar6;
    }
    else if (DAT_0006d1f0 <= fVar6) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (bVar2) {
      if (fVar4 < 0.0) {
        bVar2 = DAT_0006d1f8 < fVar4;
      }
      else if (DAT_0006d1f0 <= fVar4) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        *(undefined4 *)this = DAT_0006d1f4;
        *(undefined4 *)(this + 4) = uVar3;
      }
    }
  }
  fVar6 = DAT_0006d1ec;
  fVar5 = *(float *)(this + 0x10);
  if (fVar5 == 0.0) {
    return;
  }
  fVar4 = fVar5 + *(float *)(this + 0x14);
  fVar1 = fVar4 * DAT_0006d1e8;
  *(float *)(this + 0x14) = fVar4;
  fVar6 = (fVar5 + fVar1) * fVar6;
  fVar4 = -fVar4;
  *(float *)(this + 0x10) = fVar6;
  *(float *)(this + 0xc) = fVar4;
  uVar3 = DAT_0006d1f4;
  if (fVar6 < 0.0) {
    if (fVar6 <= DAT_0006d1f8) {
      return;
    }
  }
  else if (DAT_0006d1f0 <= fVar6) {
    return;
  }
  if (0.0 <= fVar4) {
    if (fVar4 < DAT_0006d1f0) {
      *(undefined4 *)(this + 0xc) = DAT_0006d1f4;
      *(undefined4 *)(this + 0x10) = uVar3;
    }
    return;
  }
  if (DAT_0006d1f8 < fVar4) {
    *(undefined4 *)(this + 0xc) = DAT_0006d1f4;
    *(undefined4 *)(this + 0x10) = uVar3;
  }
  return;
}
