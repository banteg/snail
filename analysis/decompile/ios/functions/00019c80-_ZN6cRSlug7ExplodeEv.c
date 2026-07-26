/*
 * mangled: _ZN6cRSlug7ExplodeEv
 * demangled: cRSlug::Explode()
 * address: 00019c80
 * size: 676
 */

/* cRSlug::Explode() */

void __thiscall cRSlug::Explode(cRSlug *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;

  iVar5 = *(int *)PTR__Game_001b60b8;
  if ((((&DAT_00353544)[iVar5] == '\0') && (*(int *)(iVar5 + 100) == 1)) &&
     (*(int *)(iVar5 + 0x72bd0) != 7)) {
    *(int *)(PTR__gConfig_001b60d4 + 0xc) = *(int *)(PTR__gConfig_001b60d4 + 0xc) + 1;
  }
  iVar5 = 0;
  do {
    uVar3 = gRMathRand2();
    fVar10 = 3.0517578e-05;
    fVar8 = 0.55;
    fVar7 = 0.3;
    fVar9 = 0.5;
    fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar11 = fVar6 * 3.0517578e-05 * 0.4 + 0.4;
    uVar3 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar8 = fVar8 + fVar6 * fVar10 * 0.85;
    iVar4 = cRSpriteManager::New((int)PTR__gRSpriteManager_001b61e4,1,0x75,-1);
    *(float *)(iVar4 + 0x84) = fVar8 + fVar8;
    *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x802;
    *(undefined4 *)(iVar4 + 0x68) = 0;
    uVar3 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar7 + fVar6 * fVar10 * fVar9 == 0.0) << 0x1e;
    if (SUB41(in_fpscr >> 0x1e,0)) {
      fVar6 = 0.0;
    }
    else {
      uVar3 = gRMathRand2();
      fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      fVar6 = 1.0 / ((fVar7 + fVar6 * fVar10 * fVar9) * 60.0);
    }
    fVar10 = 3.0517578e-05;
    fVar9 = 0.3;
    iVar5 = iVar5 + 1;
    fVar7 = *(float *)(*(int *)(this + 0x7c) + 0x4c);
    *(undefined4 *)(iVar4 + 0x70) = 0;
    *(undefined4 *)(iVar4 + 0x74) = 0;
    *(float *)(iVar4 + 0x6c) = fVar6 * fVar7;
    uVar3 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    tColour::Grey((tColour *)(iVar4 + 0x2c),fVar6 * fVar10 * fVar9 + 0.7);
    *(float *)(iVar4 + 0x60) = fVar8 * fVar9;
    *(float *)(iVar4 + 100) = fVar8 * 1.2;
    *(float *)(iVar4 + 0x78) =
         *(float *)(*(int *)(this + 0x7c) + 0x4c) * *(float *)(*(int *)(this + 0x7c) + 0x4c) * -0.01
         * 2.2;
    uVar3 = gRMathRand2();
    uVar1 = gRMathRand2();
    uVar2 = gRMathRand2();
    fVar6 = *(float *)(*(int *)(this + 0x7c) + 0x4c);
    fVar7 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar4 + 0x5c) =
         (*(float *)(*(int *)(this + 0x7c) + 0xf850) + fVar7 * fVar10 * fVar11) * fVar6;
    fVar7 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar4 + 0x58) = fVar7 * fVar10 * (fVar11 + fVar9) * fVar6;
    fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar4 + 0x54) = (fVar7 - 16384.0) * 6.1035156e-05 * fVar11 * fVar6;
    uVar3 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar6 = fVar6 * fVar10 * 10.0;
    fVar7 = *(float *)(this + 0x60);
    fVar8 = *(float *)(this + 100);
    *(float *)(iVar4 + 0x48) = *(float *)(this + 0x5c) + fVar6 * *(float *)(iVar4 + 0x54);
    *(float *)(iVar4 + 0x4c) = fVar7 + fVar6 * *(float *)(iVar4 + 0x58);
    *(float *)(iVar4 + 0x50) = fVar8 + fVar6 * *(float *)(iVar4 + 0x5c);
  } while (iVar5 != 0x14);
  return;
}
