/*
 * mangled: _ZN13cRStarManager4InitEv
 * demangled: cRStarManager::Init()
 * address: 00066c60
 * size: 1020
 */

/* cRStarManager::Init() */

void __thiscall cRStarManager::Init(cRStarManager *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  puVar1 = PTR__gRSpriteManager_001b61e4;
  iVar4 = *(int *)(this + 0x34);
  if (0 < iVar4) {
    iVar6 = 0;
    iVar5 = 0;
    do {
      iVar4 = iVar5 + *(int *)(this + 0x30);
      uVar2 = cRSpriteManager::New((int)puVar1,2,0x12,-1);
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x2c;
      *(undefined4 *)(iVar4 + 0x1c) = uVar2;
      iVar4 = *(int *)(this + 0x34);
    } while (iVar6 < iVar4);
  }
  *(undefined4 *)(this + 0x38) = 0x3f800000;
  if (0 < iVar4) {
    iVar4 = 0;
    local_3c = 0;
    do {
      *(undefined4 *)(*(int *)(this + 0x30) + iVar4) = 1;
      if (local_3c == 0) {
        *(undefined4 *)(*(int *)(this + 0x30) + iVar4 + 0x28) = 0x3ecccccd;
      }
      else {
        iVar5 = *(int *)(this + 0x30);
        uVar2 = gRMathRand2();
        fVar10 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(iVar4 + iVar5 + 0x28) = (fVar10 - 16384.0) * 6.1035156e-05 * 0.1 + 0.4;
      }
      fVar11 = 3.0517578e-05;
      iVar5 = iVar4 + *(int *)(this + 0x30);
      iVar6 = *(int *)PTR__Game_001b60b8;
      fVar8 = *(float *)(iVar6 + 0x444);
      fVar7 = *(float *)(iVar6 + 0x454);
      *(float *)(iVar5 + 4) = *(float *)(iVar6 + 0x450) + *(float *)(iVar6 + 0x440) * 50.0;
      fVar10 = *(float *)(iVar6 + 0x448);
      fVar9 = *(float *)(iVar6 + 0x458);
      *(float *)(iVar5 + 8) = fVar7 + fVar8 * 50.0;
      *(float *)(iVar5 + 0xc) = fVar9 + fVar10 * 50.0;
      uVar2 = gRMathRand2();
      iVar5 = iVar4 + *(int *)(this + 0x30);
      fVar10 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = fVar10 * fVar11 * 6.2831855;
      uVar2 = Sin(fVar10);
      uVar3 = Cos(fVar10);
      *(undefined4 *)(iVar5 + 0x10) = uVar2;
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(undefined4 *)(iVar5 + 0x14) = uVar3;
      tVector::Normalize((tVector *)(iVar4 + *(int *)(this + 0x30) + 0x10));
      iVar5 = iVar4 + *(int *)(this + 0x30);
      uVar2 = gRMathRand2();
      fVar10 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = fVar10 * fVar11 * 0.6 + 0.3;
      *(float *)(iVar5 + 0x10) = *(float *)(iVar5 + 0x10) * fVar10;
      *(float *)(iVar5 + 0x14) = *(float *)(iVar5 + 0x14) * fVar10;
      *(float *)(iVar5 + 0x18) = *(float *)(iVar5 + 0x18) * fVar10;
      *(undefined4 *)(*(int *)(this + 0x30) + iVar4 + 0x18) = 0;
      iVar5 = *(int *)(this + 0x30);
      uVar2 = tVector::Magnitude((tVector *)(iVar4 + iVar5 + 0x10));
      *(undefined4 *)(iVar4 + iVar5 + 0x20) = uVar2;
      iVar5 = *(int *)(this + 0x30);
      uVar2 = gRMathRand2();
      fVar10 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar4 + iVar5 + 0x24) = fVar10 * fVar11 * 35.0;
      iVar5 = iVar4 + *(int *)(this + 0x30);
      fVar10 = *(float *)(iVar5 + 0x24);
      fVar7 = *(float *)(iVar5 + 0x20);
      *(float *)(iVar5 + 4) = (fVar10 * *(float *)(iVar5 + 0x10)) / fVar7 + *(float *)(iVar5 + 4);
      *(float *)(iVar5 + 8) = (fVar10 * *(float *)(iVar5 + 0x14)) / fVar7 + *(float *)(iVar5 + 8);
      *(float *)(iVar5 + 0xc) =
           *(float *)(iVar5 + 0xc) + (fVar10 * *(float *)(iVar5 + 0x18)) / fVar7;
      iVar5 = *(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c);
      *(uint *)(iVar5 + 4) = *(uint *)(iVar5 + 4) | 0x402;
      *(undefined4 *)(*(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c) + 0x68) = 0;
      *(undefined4 *)(*(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c) + 0x6c) = 0;
      *(undefined4 *)(*(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c) + 0x78) = 0;
      iVar5 = *(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c);
      tColour::tColour((tColour *)&local_38,0.8,0.8,1.0,0.4);
      *(undefined4 *)(iVar5 + 0x2c) = local_38;
      *(undefined4 *)(iVar5 + 0x30) = uStack_34;
      *(undefined4 *)(iVar5 + 0x34) = uStack_30;
      *(undefined4 *)(iVar5 + 0x38) = uStack_2c;
      *(undefined4 *)(*(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c) + 0x60) = 0x3f4ccccd;
      iVar5 = *(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c);
      *(undefined4 *)(iVar5 + 100) = *(undefined4 *)(iVar5 + 0x60);
      *(float *)(*(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c) + 0x84) =
           *(float *)(iVar4 + *(int *)(this + 0x30) + 0x20) * 4.0 + 4.0;
      iVar5 = iVar4 + *(int *)(this + 0x30);
      iVar6 = *(int *)(iVar5 + 0x1c);
      uVar2 = *(undefined4 *)(iVar5 + 0x14);
      uVar3 = *(undefined4 *)(iVar5 + 0x18);
      *(undefined4 *)(iVar6 + 0x54) = *(undefined4 *)(iVar5 + 0x10);
      *(undefined4 *)(iVar6 + 0x58) = uVar2;
      *(undefined4 *)(iVar6 + 0x5c) = uVar3;
      iVar5 = iVar4 + *(int *)(this + 0x30);
      iVar6 = *(int *)(iVar5 + 0x1c);
      uVar2 = *(undefined4 *)(iVar5 + 8);
      uVar3 = *(undefined4 *)(iVar5 + 0xc);
      *(undefined4 *)(iVar6 + 0x48) = *(undefined4 *)(iVar5 + 4);
      *(undefined4 *)(iVar6 + 0x4c) = uVar2;
      *(undefined4 *)(iVar6 + 0x50) = uVar3;
      *(undefined4 *)(*(int *)(iVar4 + *(int *)(this + 0x30) + 0x1c) + 0x88) = 0;
      iVar5 = iVar4 + *(int *)(this + 0x30);
      iVar4 = iVar4 + 0x2c;
      *(undefined4 *)(*(int *)(iVar5 + 0x1c) + 0x28) = 1;
      local_3c = local_3c + 1;
    } while (local_3c < *(int *)(this + 0x34));
  }
  (*(code *)**(undefined4 **)this)(this);
  return;
}
