/*
 * mangled: _ZN9cRObjects9AddNormalE7tVector
 * demangled: cRObjects::AddNormal(tVector)
 * address: 0002fecc
 * size: 216
 */

/* cRObjects::AddNormal(tVector) */

int cRObjects::AddNormal(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  iVar5 = *(int *)(param_1 + 0xc);
  local_2c = param_2;
  uStack_28 = param_3;
  uStack_24 = param_4;
  if (0 < iVar5) {
    iVar3 = 0;
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      fVar1 = (float)tVector::Dot((tVector *)&local_2c,(tVector *)(*(int *)(param_1 + 0x10) + iVar3)
                                 );
      if (0.99 < fVar1) {
        return *(int *)(param_1 + 0x10) + iVar3;
      }
      iVar5 = *(int *)(param_1 + 0xc);
      iVar3 = iVar3 + 0xc;
    } while (iVar4 < iVar5);
  }
  iVar3 = *(int *)(param_1 + 0x10);
  iVar4 = iVar5 + 1;
  *(int *)(param_1 + 0xc) = iVar4;
  puVar2 = (undefined4 *)(iVar3 + iVar5 * 0xc);
  *puVar2 = local_2c;
  puVar2[1] = uStack_28;
  puVar2[2] = uStack_24;
  if (0x7ff < iVar4) {
    RShellError("Too Many Normals, increase ROBJECTS_NORMALTABLE_SIZE NormalNumber=%i (%i) \n",iVar4
                ,0x800);
    iVar3 = *(int *)(param_1 + 0x10);
    iVar4 = *(int *)(param_1 + 0xc);
  }
  return iVar3 + (iVar4 + -1) * 0xc;
}
