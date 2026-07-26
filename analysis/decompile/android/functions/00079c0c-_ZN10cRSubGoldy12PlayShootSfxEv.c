/*
 * mangled: _ZN10cRSubGoldy12PlayShootSfxEv
 * demangled: cRSubGoldy::PlayShootSfx()
 * address: 00079c0c
 * size: 380
 */

/* cRSubGoldy::PlayShootSfx() */

void __thiscall cRSubGoldy::PlayShootSfx(cRSubGoldy *this)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint in_fpscr;
  float extraout_s0;
  float fVar4;
  int iVar5;
  int iVar6;
  float local_1c;
  float local_18;
  float local_14;

  uVar2 = *(uint *)(this + 0x324);
  iVar3 = DAT_00079d9c + 0x79c2c;
  if ((uVar2 & 7) == 0) {
    if ((uVar2 & 0x18) == 0) {
      if ((uVar2 & 0x60) == 0) {
        return;
      }
      uVar1 = gRMathRand2();
      fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = (int)(fVar4 * DAT_00079d88 * DAT_00079d98);
      *(int *)(this + 0x1b4) = iVar6;
      iVar6 = iVar6 + 0x16;
    }
    else {
      uVar1 = gRMathRand2();
      fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      iVar6 = (int)(fVar4 * DAT_00079d88 * DAT_00079d98);
      *(int *)(this + 0x1b4) = iVar6;
      iVar6 = iVar6 + 0x13;
    }
  }
  else {
    uVar1 = gRMathRand2();
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    iVar5 = (int)(fVar4 * DAT_00079d88 + fVar4 * DAT_00079d88);
    iVar6 = iVar5 + 0x11;
    *(int *)(this + 0x1b4) = iVar5;
  }
  if (iVar6 != -1) {
    if (this[0x415] == (cRSubGoldy)0x0) {
      cRSound::Play(*(int *)(iVar3 + DAT_00079da4));
    }
    else {
      iVar6 = **(int **)(iVar3 + DAT_00079da0);
      local_1c = *(float *)(iVar6 + 0x130) - *(float *)(this + 0x5c);
      local_14 = *(float *)(iVar6 + 0x138) - *(float *)(this + 100);
      local_18 = *(float *)(iVar6 + 0x134) - *(float *)(this + 0x60);
      tVector::Normalize((tVector *)&local_1c);
      cRSound::PlayVolume(*(int *)(iVar3 + DAT_00079da4),extraout_s0);
    }
  }
  return;
}
