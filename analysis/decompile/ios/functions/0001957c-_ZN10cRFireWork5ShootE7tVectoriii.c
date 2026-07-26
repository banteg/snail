/*
 * mangled: _ZN10cRFireWork5ShootE7tVectoriii
 * demangled: cRFireWork::Shoot(tVector, int, int, int)
 * address: 0001957c
 * size: 464
 */

/* cRFireWork::Shoot(tVector, int, int, int) */

void cRFireWork::Shoot(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      int param_5,int param_6,int param_7)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  uint in_fpscr;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  if (((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) && (0 < param_7)) {
    iVar5 = 0;
    do {
      iVar3 = cRSpriteManager::New((int)PTR__gRSpriteManager_001b61e4,param_5,param_6,-1);
      fVar8 = 0.8;
      *(undefined4 *)(iVar3 + 0x68) = 0;
      *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x802;
      *(undefined4 *)(iVar3 + 0x28) = 5;
      *(undefined1 **)(iVar3 + 0x84) = &DAT_40800000;
      fVar4 = (float)RAND(0.5,(char *)0x0);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar4 + fVar8 == 0.0) << 0x1e;
      if (SUB41(in_fpscr >> 0x1e,0)) {
        fVar4 = 0.0;
      }
      else {
        fVar4 = (float)RAND(0.5,(char *)0x0);
        fVar4 = 1.0 / ((fVar4 + fVar8) * 60.0);
      }
      fVar9 = 0.3;
      *(float *)(iVar3 + 0x6c) = fVar4;
      *(undefined4 *)(iVar3 + 0x74) = 0x3e8e38e4;
      *(undefined4 *)(iVar3 + 0x70) = 0;
      fVar4 = (float)RAND(0.3,(char *)0x0);
      uVar6 = 0x3f000000;
      iVar5 = iVar5 + 1;
      tColour::Set((tColour *)(iVar3 + 0x2c),fVar4 + 0.7,(fVar4 + 0.7) * 0.5,0.0);
      *(undefined4 *)(iVar3 + 0x60) = uVar6;
      fVar7 = 0.1;
      *(undefined4 *)(iVar3 + 100) = 0x3dcccccd;
      uVar6 = gRMathRand2();
      uVar1 = gRMathRand2();
      uVar2 = gRMathRand2();
      *(undefined4 *)(iVar3 + 0x90) = 0;
      fVar4 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar3 + 0x5c) = (fVar4 - 16384.0) * 6.1035156e-05 * 0.2;
      fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      fVar8 = (float)VectorSignedToFloat(uVar6,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar3 + 0x58) = fVar7 + (fVar4 - 16384.0) * 6.1035156e-05 * fVar9;
      *(float *)(iVar3 + 0x54) = (fVar8 - 16384.0) * 6.1035156e-05 * 0.2;
      *(undefined4 *)(iVar3 + 0x48) = param_2;
      *(undefined4 *)(iVar3 + 0x4c) = param_3;
      *(undefined4 *)(iVar3 + 0x50) = param_4;
    } while (iVar5 != param_7);
  }
  return;
}
