/*
 * mangled: _ZN17cRSubLazerManager5ShootE7tVectorS0_
 * demangled: cRSubLazerManager::Shoot(tVector, tVector)
 * address: 0001de3c
 * size: 384
 */

/* cRSubLazerManager::Shoot(tVector, tVector) */

void cRSubLazerManager::Shoot
               (int param_1,float param_2,float param_3,float param_4,undefined4 param_5,
               undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;
  undefined4 uVar7;
  float local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float local_34;
  float local_30;
  float local_2c;

  iVar4 = 0;
  iVar1 = param_1;
  do {
    if (*(int *)(iVar1 + 0x74) == 0) {
      uVar7 = 0;
      local_34 = param_2 + 0.0;
      fVar6 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
      local_30 = param_3 + fVar6 * -0.01;
      local_2c = param_4 + 0.0;
      local_40 = param_5;
      uStack_3c = param_6;
      uStack_38 = param_7;
      iVar5 = iVar4 * 0xa4 + param_1;
      iVar1 = iVar4 * 0xa4 + 0x2c;
      *(undefined4 *)(iVar5 + 0x74) = 1;
      local_4c = param_2;
      local_48 = param_3;
      local_44 = param_4;
      tMatrix::Identity((tMatrix *)(param_1 + iVar1));
      *(float *)(iVar5 + 0x5c) = local_34;
      *(float *)(iVar5 + 0x60) = local_30;
      *(float *)(iVar5 + 100) = local_2c;
      *(undefined4 *)(iVar5 + 0x8c) = uVar7;
      *(undefined4 *)(iVar5 + 0x80) = local_40;
      *(undefined4 *)(iVar5 + 0x84) = uStack_3c;
      *(undefined4 *)(iVar5 + 0x88) = uStack_38;
      iVar3 = *(int *)(iVar5 + 0x7c);
      uVar2 = *(uint *)(iVar5 + 4);
      *(float *)(iVar5 + 0x90) = *(float *)(iVar3 + 0x4c) * 0.0055555557;
      if ((uVar2 & 0x200) == 0) {
        *(undefined **)(iVar5 + 8) = &UNK_00002628 + iVar3;
        *(undefined4 *)(iVar5 + 0xc) = *(undefined4 *)(&DAT_00002634 + iVar3);
        *(int *)(&DAT_00002634 + iVar3) = iVar5;
        if (*(int *)(iVar5 + 0xc) != 0) {
          *(int *)(*(int *)(iVar5 + 0xc) + 8) = iVar5;
        }
        *(uint *)(iVar5 + 4) = uVar2 | 0x200;
      }
      else {
        RShellError("List ADDafter");
      }
      tMatrix::SetZDir((tMatrix *)(param_1 + iVar1),(tVector *)(param_1 + iVar4 * 0xa4 + 0x80));
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0xf,(tVector *)&local_4c);
      return;
    }
    iVar4 = iVar4 + 1;
    iVar1 = iVar1 + 0xa4;
  } while (iVar4 != 0x14);
  return;
}
