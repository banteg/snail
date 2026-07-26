/*
 * mangled: _ZN17cRSubLazerManager5ShootE7tVectorS0_
 * demangled: cRSubLazerManager::Shoot(tVector, tVector)
 * address: 000760ac
 * size: 180
 */

/* cRSubLazerManager::Shoot(tVector, tVector) */

void cRSubLazerManager::Shoot
               (int param_1,float param_2,float param_3,float param_4,undefined4 param_5,
               undefined4 param_6,undefined4 param_7)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float local_2c;
  float local_28;
  float local_24;
  float local_1c;
  float local_18;
  float local_14;

  iVar3 = 0;
  iVar2 = param_1;
  do {
    piVar1 = (int *)(iVar2 + 0x74);
    iVar2 = iVar2 + 0xa4;
    if (*piVar1 == 0) {
      fVar4 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
      local_18 = param_3 + fVar4 * -0.01;
      local_14 = param_4 + 0.0;
      local_1c = param_2 + 0.0;
      local_2c = param_2;
      local_28 = param_3;
      local_24 = param_4;
      cRSubLazer::Shoot(iVar3 * 0xa4 + param_1,local_1c,local_18,local_14,param_5,param_6,param_7);
      cRSound::Play((cRSound *)&gRSound,0xf,(tVector *)&local_2c);
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x14);
  return;
}
