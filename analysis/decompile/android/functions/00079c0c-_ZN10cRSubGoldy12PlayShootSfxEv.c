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
  uint in_fpscr;
  float extraout_s0;
  float fVar3;
  int iVar4;
  int iVar5;
  float local_1c;
  float local_18;
  float local_14;

  uVar2 = *(uint *)(this + 0x324);
  if ((uVar2 & 7) == 0) {
    if ((uVar2 & 0x18) == 0) {
      if ((uVar2 & 0x60) == 0) {
        return;
      }
      uVar1 = gRMathRand2();
      fVar3 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = (int)(fVar3 * 3.0517578e-05 * 3.0);
      *(int *)(this + 0x1b4) = iVar5;
      iVar5 = iVar5 + 0x16;
    }
    else {
      uVar1 = gRMathRand2();
      fVar3 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = (int)(fVar3 * 3.0517578e-05 * 3.0);
      *(int *)(this + 0x1b4) = iVar5;
      iVar5 = iVar5 + 0x13;
    }
  }
  else {
    uVar1 = gRMathRand2();
    fVar3 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    iVar4 = (int)(fVar3 * 3.0517578e-05 + fVar3 * 3.0517578e-05);
    iVar5 = iVar4 + 0x11;
    *(int *)(this + 0x1b4) = iVar4;
  }
  if (iVar5 != -1) {
    if (this[0x415] == (cRSubGoldy)0x0) {
      cRSound::Play((int)&gRSound);
    }
    else {
      local_1c = *(float *)(Game + 0x130) - *(float *)(this + 0x5c);
      local_14 = *(float *)(Game + 0x138) - *(float *)(this + 100);
      local_18 = *(float *)(Game + 0x134) - *(float *)(this + 0x60);
      tVector::Normalize((tVector *)&local_1c);
      cRSound::PlayVolume((int)&gRSound,extraout_s0);
    }
  }
  return;
}
