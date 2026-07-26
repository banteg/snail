/*
 * mangled: _ZN11cRSubTracks4LoadEii
 * demangled: cRSubTracks::Load(int, int)
 * address: 00074888
 * size: 488
 */

/* cRSubTracks::Load(int, int) */

void __thiscall cRSubTracks::Load(cRSubTracks *this,int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined2 local_8c;
  undefined1 local_8a;
  int local_1c;

  iVar1 = DAT_00074a74;
  iVar4 = DAT_00074a70 + 0x748a0;
  local_1c = **(int **)(iVar4 + DAT_00074a74);
  switch(param_1) {
  case 0:
    iVar2 = *(int *)(gOFOData + **(int **)(iVar4 + DAT_00074a7c) + 0x1ebc);
    if (*(int *)(gOFOData + iVar2 * 0x8e6c + **(int **)(iVar4 + DAT_00074a7c) + 0x1ed8) + 1 <
        param_2) {
      if (*(int *)(gOFOData + iVar2 * 0x8e6c + **(int **)(iVar4 + DAT_00074a7c) + 0x1ed8) + 2 ==
          param_2) {
        puVar3 = (undefined4 *)(iVar4 + DAT_00074a94);
        local_9c = *puVar3;
        uStack_98 = puVar3[1];
        uStack_94 = puVar3[2];
        local_90 = puVar3[3];
        local_8c = (undefined2)puVar3[4];
        local_8a = (undefined1)((uint)puVar3[4] >> 0x10);
      }
      break;
    }
    if (iVar2 != 0) {
      if (iVar2 == 1) {
        sprintf((char *)&local_9c,(char *)(iVar4 + DAT_00074a80));
      }
      break;
    }
    goto LAB_00074a28;
  case 1:
    puVar3 = (undefined4 *)(iVar4 + DAT_00074a84);
    local_9c = *puVar3;
    uStack_98 = puVar3[1];
    uStack_94 = puVar3[2];
    local_90 = puVar3[3];
    local_8c = CONCAT11(local_8c._1_1_,(char)puVar3[4]);
    break;
  case 2:
    goto LAB_000749b4;
  case 3:
LAB_000749b4:
    puVar3 = (undefined4 *)(iVar4 + DAT_00074a88);
    local_9c = *puVar3;
    uStack_98 = puVar3[1];
    uStack_94 = puVar3[2];
    local_90 = CONCAT22(local_90._2_2_,(short)puVar3[3]);
    break;
  case 4:
    if (*(int *)(gOFOData +
                *(int *)(gOFOData + **(int **)(iVar4 + DAT_00074a7c) + 0x1ebc) * 0x8e6c +
                **(int **)(iVar4 + DAT_00074a7c) + 0x1ed8) + 1 < param_2) {
      sprintf((char *)&local_9c,(char *)(iVar4 + DAT_00074a8c),
              param_2 - *(int *)(gOFOData +
                                *(int *)(gOFOData + **(int **)(iVar4 + DAT_00074a7c) + 0x1ebc) *
                                0x8e6c + **(int **)(iVar4 + DAT_00074a7c) + 0x1ed8));
      break;
    }
LAB_00074a28:
    sprintf((char *)&local_9c,(char *)(iVar4 + DAT_00074a90));
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    puVar3 = (undefined4 *)(iVar4 + DAT_00074a78);
    local_9c = *puVar3;
    uStack_98 = puVar3[1];
    uStack_94 = puVar3[2];
    local_90 = CONCAT31(local_90._1_3_,(char)puVar3[3]);
  }
  Init(this,(char *)&local_9c);
  if (local_1c != **(int **)(iVar4 + iVar1)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
