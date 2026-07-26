/*
 * mangled: _ZN12OFXmlElement16getChildWithNameEP8NSStringb
 * demangled: OFXmlElement::getChildWithName(NSString*, bool)
 * address: 000d673c
 * size: 280
 */

/* OFXmlElement::getChildWithName(NSString*, bool) */

NSString * OFXmlElement::getChildWithName(NSString *param_1,bool param_2)

{
  uint uVar1;
  ID IVar2;
  NSString *pNVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  char in_r3;
  uint uVar9;
  uint in_r12;
  int *piVar10;
  bool bVar11;
  undefined8 uVar12;

  uVar4 = (uint)param_2;
  iVar7 = *(int *)(uVar4 + 0x10);
  uVar5 = *(int *)(uVar4 + 0x14) - iVar7 >> 2;
  if (uVar5 == 0) {
LAB_000d67d0:
    *(undefined4 *)param_1 = 0;
    return param_1;
  }
  if (in_r3 == '\0') {
    uVar9 = 0;
    do {
      iVar7 = *(int *)(iVar7 + uVar9 * 4);
      IVar2 = _objc_msgSend(*(ID *)(iVar7 + 0xc),"isEqualToString:");
      if ((IVar2 & 0xff) != 0) goto LAB_000d67ec;
      uVar9 = uVar9 + 1;
      if (uVar9 == uVar5) goto LAB_000d67d0;
      iVar7 = *(int *)(uVar4 + 0x10);
      uVar1 = *(int *)(uVar4 + 0x14) - iVar7 >> 2;
      bVar11 = uVar9 == uVar1;
    } while (uVar9 < uVar1);
  }
  else {
    uVar9 = 0;
    do {
      iVar7 = *(int *)(iVar7 + uVar9 * 4);
      IVar2 = _objc_msgSend(*(ID *)(iVar7 + 0xc),"isEqualToString:");
      if (((IVar2 & 0xff) != 0) && (*(char *)(iVar7 + 0x20) == '\0')) {
LAB_000d67ec:
        *(int *)param_1 = iVar7;
        *(int *)(iVar7 + 4) = *(int *)(iVar7 + 4) + 1;
        return param_1;
      }
      uVar9 = uVar9 + 1;
      if (uVar9 == uVar5) goto LAB_000d67d0;
      iVar7 = *(int *)(uVar4 + 0x10);
      uVar1 = *(int *)(uVar4 + 0x14) - iVar7 >> 2;
      bVar11 = uVar9 == uVar1;
    } while (uVar9 < uVar1);
  }
  uVar12 = std::__throw_out_of_range("vector::_M_range_check");
  uVar5 = (uint)((ulonglong)uVar12 >> 0x20);
  pNVar3 = (NSString *)uVar12;
  if (bVar11) {
    uVar5 = in_r12 & (int)pNVar3 >> 0xdc;
  }
  piVar10 = *(int **)(uVar5 + 0x10);
  iVar7 = *(int *)(uVar5 + 0x14) - (int)piVar10 >> 2;
  if (iVar7 != 0) {
    iVar8 = *piVar10;
    if (*(char *)(iVar8 + 0x20) != '\0') {
      iVar6 = 0;
      do {
        iVar6 = iVar6 + 1;
        if (iVar6 == iVar7) goto LAB_000d68a4;
        iVar8 = piVar10[iVar6];
      } while (*(char *)(iVar8 + 0x20) != '\0');
    }
    *(undefined1 *)(iVar8 + 0x20) = 1;
    *(int *)pNVar3 = iVar8;
    *(int *)(iVar8 + 4) = *(int *)(iVar8 + 4) + 1;
    return pNVar3;
  }
LAB_000d68a4:
  *(int *)pNVar3 = 0;
  return pNVar3;
}
