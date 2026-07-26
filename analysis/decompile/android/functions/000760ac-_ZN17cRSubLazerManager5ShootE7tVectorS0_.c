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
  int iVar4;
  uint in_fpscr;
  float fVar5;
  float local_2c;
  float local_28;
  float local_24;
  float local_1c;
  float local_18;
  float local_14;

  iVar4 = 0;
  iVar3 = DAT_00076168 + 0x760cc;
  iVar2 = param_1;
  do {
    piVar1 = (int *)(iVar2 + 0x74);
    iVar2 = iVar2 + 0xa4;
    if (*piVar1 == 0) {
      fVar5 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
      local_18 = param_3 + fVar5 * DAT_00076160;
      local_14 = param_4 + DAT_00076164;
      local_1c = param_2 + DAT_00076164;
      local_2c = param_2;
      local_28 = param_3;
      local_24 = param_4;
      cRSubLazer::Shoot(iVar4 * 0xa4 + param_1,local_1c,local_18,local_14,param_5,param_6,param_7);
      cRSound::Play(*(cRSound **)(iVar3 + DAT_0007616c),0xf,(tVector *)&local_2c);
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x14);
  return;
}
