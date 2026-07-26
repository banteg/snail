/*
 * mangled: _ZN6cRSlug7ExplodeEv
 * demangled: cRSlug::Explode()
 * address: 00077b08
 * size: 732
 */

/* cRSlug::Explode() */

void __thiscall cRSlug::Explode(cRSlug *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint in_fpscr;
  float extraout_s0;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  if (((gDirectory[Game + 0x2544] == '\0') && (*(int *)(Game + 100) == 1)) &&
     (*(int *)(Game + 0x71900) != 7)) {
    if (gOFORef != -1) {
      *(int *)(gOFOData + gOFORef * 0x168 + 0x28) = *(int *)(gOFOData + gOFORef * 0x168 + 0x28) + 1;
    }
    gConfig._12_4_ = gConfig._12_4_ + 1;
  }
  iVar4 = 0;
  do {
    uVar1 = gRMathRand2();
    fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar5 = fVar9 * 3.0517578e-05 * 0.4 + 0.4;
    uVar1 = gRMathRand2();
    fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar6 = fVar9 * 3.0517578e-05 * 0.85 + 0.55;
    iVar2 = cRSpriteManager::New((int)&gRSpriteManager,1,0x75,-1);
    *(float *)(iVar2 + 0x84) = fVar6 + fVar6;
    *(undefined4 *)(iVar2 + 0x68) = 0;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x802;
    uVar1 = gRMathRand2();
    fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar9 * 3.0517578e-05 * 0.5 + 0.3 == 0.0) << 0x1e;
    fVar9 = 0.0;
    if (!SUB41(in_fpscr >> 0x1e,0)) {
      uVar1 = gRMathRand2();
      fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      fVar9 = 1.0 / ((fVar9 * 3.0517578e-05 * 0.5 + 0.3) * 60.0);
    }
    fVar7 = *(float *)(*(int *)(this + 0x7c) + 0x54);
    *(undefined4 *)(iVar2 + 0x70) = 0;
    *(undefined4 *)(iVar2 + 0x74) = 0;
    iVar4 = iVar4 + 1;
    *(float *)(iVar2 + 0x6c) = fVar9 * fVar7;
    uVar1 = gRMathRand2();
    VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    tColour::Grey((tColour *)(iVar2 + 0x2c),extraout_s0);
    iVar3 = *(int *)(this + 0x7c);
    *(float *)(iVar2 + 100) = fVar6 * 1.2;
    *(float *)(iVar2 + 0x60) = fVar6 * 0.3;
    *(float *)(iVar2 + 0x78) = *(float *)(iVar3 + 0x54) * *(float *)(iVar3 + 0x54) * -0.01 * 2.2;
    uVar1 = gRMathRand2();
    fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    uVar1 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    uVar1 = gRMathRand2();
    fVar8 = *(float *)(*(int *)(this + 0x7c) + 0x54);
    fVar7 = *(float *)(*(int *)(this + 0x7c) + 0xfed4);
    *(float *)(iVar2 + 0x54) = (fVar9 - 16384.0) * 6.1035156e-05 * fVar5 * fVar8;
    fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar2 + 0x58) = fVar6 * 3.0517578e-05 * (fVar5 + 0.3) * fVar8;
    *(float *)(iVar2 + 0x5c) = (fVar7 + fVar9 * 3.0517578e-05 * fVar5) * fVar8;
    uVar1 = gRMathRand2();
    fVar5 = *(float *)(this + 0x5c);
    fVar6 = *(float *)(this + 0x60);
    fVar9 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar9 = fVar9 * 3.0517578e-05 * 10.0;
    *(float *)(iVar2 + 0x50) = *(float *)(this + 100) + fVar9 * *(float *)(iVar2 + 0x5c);
    *(float *)(iVar2 + 0x48) = fVar5 + fVar9 * *(float *)(iVar2 + 0x54);
    *(float *)(iVar2 + 0x4c) = fVar6 + fVar9 * *(float *)(iVar2 + 0x58);
  } while (iVar4 != 0x14);
  return;
}
