/*
 * mangled: _ZN10cRFireWork5ShootE7tVectoriii
 * demangled: cRFireWork::Shoot(tVector, int, int, int)
 * address: 00075b6c
 * size: 460
 */

/* cRFireWork::Shoot(tVector, int, int, int) */

void cRFireWork::Shoot(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      int param_5,int param_6,int param_7)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s1;
  float extraout_s2;
  float fVar5;

  if (((gConfig._28_4_ & 0x10) != 0) && (0 < param_7)) {
    iVar4 = 0;
    do {
      iVar2 = cRSpriteManager::New((int)&gRSpriteManager,param_5,param_6,-1);
      *(undefined4 *)(iVar2 + 0x84) = 0x40800000;
      *(undefined4 *)(iVar2 + 0x68) = 0;
      *(undefined4 *)(iVar2 + 0x28) = 5;
      *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x802;
      fVar3 = (float)RAND(extraout_s0_00,(char *)0x3f000000);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar3 + 0.8 == 0.0) << 0x1e;
      fVar3 = extraout_s0_01;
      fVar5 = 0.0;
      if (!SUB41(in_fpscr >> 0x1e,0)) {
        fVar3 = (float)RAND(extraout_s0_01,(char *)0x3f000000);
        fVar5 = 1.0 / ((fVar3 + 0.8) * 60.0);
        fVar3 = extraout_s0_02;
      }
      *(float *)(iVar2 + 0x6c) = fVar5;
      *(undefined4 *)(iVar2 + 0x70) = 0;
      *(undefined4 *)(iVar2 + 0x74) = 0x3e8e38e4;
      RAND(fVar3,(char *)0x3e99999a);
      iVar4 = iVar4 + 1;
      tColour::Set((tColour *)(iVar2 + 0x2c),extraout_s0,extraout_s1,extraout_s2);
      *(undefined4 *)(iVar2 + 0x60) = 0x3f000000;
      *(undefined4 *)(iVar2 + 100) = 0x3dcccccd;
      uVar1 = gRMathRand2();
      fVar3 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      uVar1 = gRMathRand2();
      fVar5 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      uVar1 = gRMathRand2();
      *(float *)(iVar2 + 0x54) = (fVar3 - 16384.0) * 6.1035156e-05 * 0.2;
      *(undefined4 *)(iVar2 + 0x90) = 0;
      *(float *)(iVar2 + 0x58) = (fVar5 - 16384.0) * 6.1035156e-05 * 0.3 + 0.1;
      fVar3 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar2 + 0x5c) = (fVar3 - 16384.0) * 6.1035156e-05 * 0.2;
      *(undefined4 *)(iVar2 + 0x48) = param_2;
      *(undefined4 *)(iVar2 + 0x4c) = param_3;
      *(undefined4 *)(iVar2 + 0x50) = param_4;
    } while (iVar4 < param_7);
  }
  return;
}
