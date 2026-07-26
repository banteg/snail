/*
 * mangled: _ZNK23OFResourceControllerMap17getControllerNameEP10objc_class
 * demangled: OFResourceControllerMap::getControllerName(objc_class*) const
 * address: 000fa01c
 * size: 332
 */

/* OFResourceControllerMap::getControllerName(objc_class*) const */

undefined4 __thiscall
OFResourceControllerMap::getControllerName(OFResourceControllerMap *this,objc_class *param_1)

{
  undefined4 uVar1;
  int iVar2;
  ResourceDescription *pRVar3;
  ResourceDescription *pRVar4;
  ResourceDescription *pRVar5;
  ResourceDescription *pRVar6;
  int iVar7;

  pRVar4 = (this->field2_0x8).field0_0x0.field1_0x4;
  pRVar5 = (this->field2_0x8).field0_0x0.field0_0x0;
  iVar2 = (int)pRVar4 - (int)pRVar5;
  iVar7 = iVar2 >> 5;
  if (0 < iVar7) {
    if (*(objc_class **)pRVar5 == param_1) goto LAB_000fa12c;
    pRVar6 = pRVar5 + 8;
    if (*(objc_class **)(pRVar5 + 8) != param_1) {
      pRVar6 = pRVar5 + 0x10;
      if (*(objc_class **)(pRVar5 + 0x10) == param_1) {
LAB_000fa140:
        if (pRVar4 == pRVar6) {
          uVar1 = 0;
        }
        else {
          uVar1 = *(undefined4 *)(pRVar6 + 4);
        }
        return uVar1;
      }
      pRVar3 = pRVar5 + 0x18;
      if (*(objc_class **)(pRVar5 + 0x18) != param_1) {
        pRVar5 = pRVar5 + 0x38;
        do {
          pRVar3 = pRVar5;
          iVar7 = iVar7 + -1;
          pRVar5 = pRVar3 + -0x18;
          if (iVar7 == 0) {
            iVar2 = (int)pRVar4 - (int)pRVar5;
            goto LAB_000fa0d4;
          }
          if (*(objc_class **)(pRVar3 + -0x18) == param_1) goto LAB_000fa12c;
          pRVar6 = pRVar3 + -0x10;
          if (*(objc_class **)(pRVar3 + -0x10) == param_1) goto LAB_000fa0f0;
          pRVar6 = pRVar3 + -8;
          if (*(objc_class **)(pRVar3 + -8) == param_1) goto LAB_000fa140;
          pRVar5 = pRVar3 + 0x20;
        } while (*(objc_class **)pRVar3 != param_1);
      }
      if (pRVar4 == pRVar3) {
        uVar1 = 0;
      }
      else {
        uVar1 = *(undefined4 *)(pRVar3 + 4);
      }
      return uVar1;
    }
    goto LAB_000fa0f0;
  }
LAB_000fa0d4:
  iVar2 = iVar2 >> 3;
  pRVar6 = pRVar4;
  if (iVar2 == 2) {
LAB_000fa110:
    if (*(objc_class **)pRVar5 == param_1) goto LAB_000fa12c;
    pRVar5 = pRVar5 + 8;
  }
  else {
    if (iVar2 == 3) {
      if (*(objc_class **)pRVar5 == param_1) goto LAB_000fa12c;
      pRVar5 = pRVar5 + 8;
      goto LAB_000fa110;
    }
    if (iVar2 != 1) goto LAB_000fa0f0;
  }
  if (*(objc_class **)pRVar5 != param_1) {
LAB_000fa0f0:
    if (pRVar4 == pRVar6) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(undefined4 *)(pRVar6 + 4);
    }
    return uVar1;
  }
LAB_000fa12c:
  if (pRVar4 == pRVar5) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(pRVar5 + 4);
  }
  return uVar1;
}
