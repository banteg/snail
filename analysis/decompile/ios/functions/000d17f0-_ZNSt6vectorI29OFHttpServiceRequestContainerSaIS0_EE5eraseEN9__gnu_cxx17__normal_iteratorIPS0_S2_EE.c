/*
 * mangled: _ZNSt6vectorI29OFHttpServiceRequestContainerSaIS0_EE5eraseEN9__gnu_cxx17__normal_iteratorIPS0_S2_EE
 * demangled: std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer>>::erase(__gnu_cxx::__normal_iterator<OFHttpServiceRequestContainer*, std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer>>>)
 * address: 000d17f0
 * size: 560
 */

/* std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer>
   >::erase(__gnu_cxx::__normal_iterator<OFHttpServiceRequestContainer*,
   std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer> > >) */

int __thiscall
std::vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>::erase
          (vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>> *this
          ,int param_2)

{
  ID IVar1;
  OFSmartObject *this_00;
  int iVar2;
  ID IVar3;
  OFSmartObject *pOVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar2 = *(int *)(this + 4);
  iVar6 = param_2 + 0x24;
  if ((iVar6 != iVar2) && (iVar7 = (iVar2 - iVar6 >> 2) * 0x38e38e39, iVar5 = param_2, 0 < iVar7)) {
    do {
      IVar1 = *(ID *)(iVar5 + 8);
      *(undefined4 *)(iVar5 + 4) = *(undefined4 *)(iVar6 + 4);
      IVar3 = *(ID *)(iVar6 + 8);
      if (IVar1 != IVar3) {
        if (IVar1 != 0) {
          _objc_msgSend(IVar1,"release");
          IVar3 = *(ID *)(iVar6 + 8);
        }
        *(ID *)(iVar5 + 8) = IVar3;
        if (IVar3 != 0) {
          _objc_msgSend(IVar3,"retain");
        }
      }
      IVar1 = *(ID *)(iVar5 + 0xc);
      IVar3 = *(ID *)(iVar6 + 0xc);
      if (IVar1 != IVar3) {
        if (IVar1 != 0) {
          _objc_msgSend(IVar1,"release");
          IVar3 = *(ID *)(iVar6 + 0xc);
        }
        *(ID *)(iVar5 + 0xc) = IVar3;
        if (IVar3 != 0) {
          _objc_msgSend(IVar3,"retain");
        }
      }
      IVar1 = *(ID *)(iVar5 + 0x10);
      IVar3 = *(ID *)(iVar6 + 0x10);
      if (IVar1 != IVar3) {
        if (IVar1 != 0) {
          _objc_msgSend(IVar1,"release");
          IVar3 = *(ID *)(iVar6 + 0x10);
        }
        *(ID *)(iVar5 + 0x10) = IVar3;
        if (IVar3 != 0) {
          _objc_msgSend(IVar3,"retain");
        }
      }
      IVar1 = *(ID *)(iVar5 + 0x14);
      IVar3 = *(ID *)(iVar6 + 0x14);
      if (IVar1 != IVar3) {
        if (IVar1 != 0) {
          _objc_msgSend(IVar1,"release");
          IVar3 = *(ID *)(iVar6 + 0x14);
        }
        *(ID *)(iVar5 + 0x14) = IVar3;
        if (IVar3 != 0) {
          _objc_msgSend(IVar3,"retain");
        }
      }
      IVar1 = *(ID *)(iVar5 + 0x18);
      IVar3 = *(ID *)(iVar6 + 0x18);
      if (IVar1 != IVar3) {
        if (IVar1 != 0) {
          _objc_msgSend(IVar1,"release");
          IVar3 = *(ID *)(iVar6 + 0x18);
        }
        *(ID *)(iVar5 + 0x18) = IVar3;
        if (IVar3 != 0) {
          _objc_msgSend(IVar3,"retain");
        }
      }
      IVar1 = *(ID *)(iVar5 + 0x1c);
      IVar3 = *(ID *)(iVar6 + 0x1c);
      if (IVar1 != IVar3) {
        if (IVar1 != 0) {
          _objc_msgSend(IVar1,"release");
          IVar3 = *(ID *)(iVar6 + 0x1c);
        }
        *(ID *)(iVar5 + 0x1c) = IVar3;
        if (IVar3 != 0) {
          _objc_msgSend(IVar3,"retain");
        }
      }
      this_00 = *(OFSmartObject **)(iVar5 + 0x20);
      pOVar4 = *(OFSmartObject **)(iVar6 + 0x20);
      if (this_00 != pOVar4) {
        if (this_00 != (OFSmartObject *)0x0) {
          OFSmartObject::Release(this_00);
          pOVar4 = *(OFSmartObject **)(iVar6 + 0x20);
        }
        *(OFSmartObject **)(iVar5 + 0x20) = pOVar4;
        if (pOVar4 != (OFSmartObject *)0x0) {
          *(int *)(pOVar4 + 4) = *(int *)(pOVar4 + 4) + 1;
        }
      }
      iVar7 = iVar7 + -1;
      iVar6 = iVar6 + 0x24;
      iVar5 = iVar5 + 0x24;
    } while (iVar7 != 0);
    iVar2 = *(int *)(this + 4);
  }
  *(int *)(this + 4) = iVar2 + -0x24;
  (**(code **)(*(int *)(iVar2 + -0x24) + 4))();
  return param_2;
}
