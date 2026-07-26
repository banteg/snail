/*
 * mangled: _ZN12OFXmlElement16getValueWithNameEPKcRP8NSStringb
 * demangled: OFXmlElement::getValueWithName(char const*, NSString*&, bool)
 * address: 000d69bc
 * size: 324
 */

/* OFXmlElement::getValueWithName(char const*, NSString*&, bool) */

undefined4 __thiscall
OFXmlElement::getValueWithName(OFXmlElement *this,char *param_1,NSString **param_2,bool param_3)

{
  uint uVar1;
  ID IVar2;
  OFPointer<OFXmlElement> *pOVar3;
  ID IVar4;
  OFSmartObject *this_00;
  uint uVar5;

  IVar2 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",param_1);
  pOVar3 = (this->field4_0x10).field0_0x0.field0_0x0;
  uVar1 = (int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar3 >> 2;
  if (uVar1 == 0) {
    return 0;
  }
  uVar5 = 0;
  if (!param_3) goto LAB_000d6ad4;
  uVar5 = 0;
  do {
    this_00 = *(OFSmartObject **)(pOVar3 + uVar5 * 4);
    IVar4 = _objc_msgSend(*(ID *)(this_00 + 0xc),"isEqualToString:",IVar2);
    if (((IVar4 & 0xff) != 0) && (this_00[0x20] == (OFSmartObject)0x0)) {
      *(int *)(this_00 + 4) = *(int *)(this_00 + 4) + 1;
      this_00[0x20] = (OFSmartObject)0x1;
LAB_000d6a90:
      *param_2 = *(NSString **)(this_00 + 8);
      OFSmartObject::Release(this_00);
      return 1;
    }
    uVar5 = uVar5 + 1;
    if (uVar5 == uVar1) {
      return 0;
    }
    pOVar3 = (this->field4_0x10).field0_0x0.field0_0x0;
  } while (uVar5 < (uint)((int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar3 >> 2));
  do {
    pOVar3 = (OFPointer<OFXmlElement> *)std::__throw_out_of_range("vector::_M_range_check");
LAB_000d6ad4:
    do {
      this_00 = *(OFSmartObject **)(pOVar3 + uVar5 * 4);
      IVar4 = _objc_msgSend(*(ID *)(this_00 + 0xc),"isEqualToString:",IVar2);
      if ((IVar4 & 0xff) != 0) {
        *(int *)(this_00 + 4) = *(int *)(this_00 + 4) + 1;
        goto LAB_000d6a90;
      }
      uVar5 = uVar5 + 1;
      if (uVar5 == uVar1) {
        return 0;
      }
      pOVar3 = (this->field4_0x10).field0_0x0.field0_0x0;
    } while (uVar5 < (uint)((int)(this->field4_0x10).field0_0x0.field1_0x4 - (int)pOVar3 >> 2));
  } while( true );
}
