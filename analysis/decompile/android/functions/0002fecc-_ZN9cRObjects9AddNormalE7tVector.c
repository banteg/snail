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
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  fVar1 = DAT_0002ffa4;
  iVar7 = *(int *)(param_1 + 0xc);
  iVar4 = DAT_0002ffa8 + 0x2fef4;
  local_2c = param_2;
  uStack_28 = param_3;
  uStack_24 = param_4;
  if (0 < iVar7) {
    iVar5 = 0;
    iVar6 = 0;
    do {
      iVar6 = iVar6 + 1;
      fVar2 = (float)tVector::Dot((tVector *)&local_2c,(tVector *)(*(int *)(param_1 + 0x10) + iVar5)
                                 );
      if (fVar1 < fVar2) {
        return *(int *)(param_1 + 0x10) + iVar5;
      }
      iVar7 = *(int *)(param_1 + 0xc);
      iVar5 = iVar5 + 0xc;
    } while (iVar6 < iVar7);
  }
  iVar5 = *(int *)(param_1 + 0x10);
  iVar6 = iVar7 + 1;
  *(int *)(param_1 + 0xc) = iVar6;
  puVar3 = (undefined4 *)(iVar5 + iVar7 * 0xc);
  *puVar3 = local_2c;
  puVar3[1] = uStack_28;
  puVar3[2] = uStack_24;
  if (0x7ff < iVar6) {
    RShellError((char *)(iVar4 + DAT_0002ffac),iVar6,0x800);
    iVar5 = *(int *)(param_1 + 0x10);
    iVar6 = *(int *)(param_1 + 0xc);
  }
  return iVar5 + (iVar6 + -1) * 0xc;
}
