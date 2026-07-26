/*
 * mangled: _ZN10cRSubGoldy12PlayShootSfxEv
 * demangled: cRSubGoldy::PlayShootSfx()
 * address: 0001a05c
 * size: 392
 */

/* cRSubGoldy::PlayShootSfx() */

void __thiscall cRSubGoldy::PlayShootSfx(cRSubGoldy *this)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
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
      fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = (int)(fVar4 * 3.0517578e-05 * 3.0);
      *(int *)(this + 0x1b4) = iVar5;
      iVar5 = iVar5 + 0x16;
    }
    else {
      uVar1 = gRMathRand2();
      fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = (int)(fVar4 * 3.0517578e-05 * 3.0);
      *(int *)(this + 0x1b4) = iVar5;
      iVar5 = iVar5 + 0x13;
    }
  }
  else {
    uVar1 = gRMathRand2();
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    iVar5 = (int)(fVar4 * 3.0517578e-05 + fVar4 * 3.0517578e-05);
    *(int *)(this + 0x1b4) = iVar5;
    iVar5 = iVar5 + 0x11;
  }
  if (iVar5 != -1) {
    if (this[0x40d] == (cRSubGoldy)0x0) {
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,iVar5);
    }
    else {
      iVar3 = *(int *)PTR__Game_001b60b8;
      local_1c = *(float *)(iVar3 + 0x130) - *(float *)(this + 0x5c);
      local_18 = *(float *)(iVar3 + 0x134) - *(float *)(this + 0x60);
      local_14 = *(float *)(iVar3 + 0x138) - *(float *)(this + 100);
      fVar4 = (float)tVector::Normalize((tVector *)&local_1c);
      fVar4 = fVar4 / -60.0 + 1.0;
      if (fVar4 < 0.0) {
        cRSound::PlayVolume((cRSound *)PTR__gRSound_001b61e0,iVar5,0.0);
      }
      else {
        if (1.0 < fVar4) {
          fVar4 = 1.0;
        }
        cRSound::PlayVolume((cRSound *)PTR__gRSound_001b61e0,iVar5,fVar4);
      }
    }
  }
  return;
}
