/*
 * mangled: _ZN12OFXmlElement22dequeueNextUnreadChildEPKc
 * demangled: OFXmlElement::dequeueNextUnreadChild(char const*)
 * address: 000d68cc
 * size: 240
 */

/* OFXmlElement::dequeueNextUnreadChild(char const*) */

OFXmlElement * __thiscall OFXmlElement::dequeueNextUnreadChild(OFXmlElement *this,char *param_1)

{
  ID IVar1;
  ID IVar2;
  int iVar3;
  int iVar4;
  ID IVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  undefined4 **ppuVar10;
  OFSmartObject *this_00;
  uint uVar11;
  uint uVar12;
  char *pcVar13;
  uint in_r12;
  undefined4 uVar14;
  bool bVar15;
  bool bVar16;
  undefined8 uVar17;
  uint uVar18;
  undefined1 *puVar19;
  OFXmlElement *local_24;

  puVar19 = &stack0xfffffff8;
  local_24 = this;
  IVar1 = NSString::stringWithUTF8String_((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:");
  puVar7 = *(undefined4 **)(param_1 + 0x10);
  uVar18 = *(int *)(param_1 + 0x14) - (int)puVar7 >> 2;
  if (uVar18 != 0) {
    uVar11 = 0;
    pcVar13 = "isEqualToString:";
    while( true ) {
      ppuVar10 = (undefined4 **)puVar7[uVar11];
      if ((*(char *)(ppuVar10 + 8) == '\0') &&
         (IVar2 = _objc_msgSend((ID)ppuVar10[3],"isEqualToString:",IVar1), (IVar2 & 0xff) != 0)) {
        *(undefined1 *)(ppuVar10 + 8) = 1;
        local_24->field0_0x0 = ppuVar10;
        ppuVar10[1] = (undefined4 *)((int)ppuVar10[1] + 1);
        return local_24;
      }
      uVar11 = uVar11 + 1;
      if (uVar11 == uVar18) break;
      puVar7 = *(undefined4 **)(param_1 + 0x10);
      uVar8 = *(int *)(param_1 + 0x14) - (int)puVar7;
      bVar15 = uVar11 == (int)uVar8 >> 2;
      if ((uint)((int)uVar8 >> 2) <= uVar11) {
        uVar14 = 0xd69ac;
        uVar17 = std::__throw_out_of_range("vector::_M_range_check");
        uVar6 = (uint)((ulonglong)uVar17 >> 0x20);
        iVar3 = (int)uVar17;
        bVar16 = false;
        if (bVar15) {
          uVar6 = in_r12 & uVar18 >> ((uint)&local_24 & 0xff);
          bVar16 = uVar6 == 0;
        }
        bVar15 = false;
        if (bVar16) {
          uVar11 = in_r12 & in_r12 << (IVar1 & 0xff);
          bVar15 = uVar11 == 0;
        }
        bVar16 = false;
        if (bVar15) {
          uVar6 = in_r12 & iVar3 >> ((uint)&local_24 & 0xff);
          bVar16 = uVar6 == 0;
        }
        if (bVar16) {
          uVar8 = uVar18 & in_r12 >> 0x18;
        }
        IVar2 = NSString::stringWithUTF8String_
                          ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",uVar6);
        iVar4 = *(int *)(iVar3 + 0x10);
        iVar9 = *(int *)(iVar3 + 0x14) - iVar4;
        uVar6 = iVar9 >> 2;
        if (uVar6 == 0) {
          return (OFXmlElement *)0x0;
        }
        uVar12 = 0;
        if ((uVar8 & 0xff) == 0) goto LAB_000d6ad4;
        uVar12 = 0;
        do {
          this_00 = *(OFSmartObject **)(iVar4 + uVar12 * 4);
          IVar5 = _objc_msgSend(*(ID *)(this_00 + 0xc),"isEqualToString:",IVar2,iVar9,puVar7,uVar18,
                                pcVar13,IVar1,ppuVar10,uVar11,param_1,puVar19,uVar14);
          if (((IVar5 & 0xff) != 0) && (this_00[0x20] == (OFSmartObject)0x0)) {
            *(int *)(this_00 + 4) = *(int *)(this_00 + 4) + 1;
            this_00[0x20] = (OFSmartObject)0x1;
LAB_000d6a90:
            *puVar7 = *(undefined4 *)(this_00 + 8);
            OFSmartObject::Release(this_00);
            return (OFXmlElement *)0x1;
          }
          uVar12 = uVar12 + 1;
          if (uVar12 == uVar6) {
            return (OFXmlElement *)0x0;
          }
          iVar4 = *(int *)(iVar3 + 0x10);
          iVar9 = *(int *)(iVar3 + 0x14) - iVar4;
        } while (uVar12 < (uint)(iVar9 >> 2));
        do {
          iVar4 = std::__throw_out_of_range("vector::_M_range_check");
LAB_000d6ad4:
          do {
            this_00 = *(OFSmartObject **)(iVar4 + uVar12 * 4);
            IVar1 = _objc_msgSend(*(ID *)(this_00 + 0xc),"isEqualToString:",IVar2);
            if ((IVar1 & 0xff) != 0) {
              *(int *)(this_00 + 4) = *(int *)(this_00 + 4) + 1;
              goto LAB_000d6a90;
            }
            uVar12 = uVar12 + 1;
            if (uVar12 == uVar6) {
              return (OFXmlElement *)0x0;
            }
            iVar4 = *(int *)(iVar3 + 0x10);
          } while (uVar12 < (uint)(*(int *)(iVar3 + 0x14) - iVar4 >> 2));
        } while( true );
      }
    }
  }
  local_24->field0_0x0 = (undefined4 **)0x0;
  return local_24;
}
