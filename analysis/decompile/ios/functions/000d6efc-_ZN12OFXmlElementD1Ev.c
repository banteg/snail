/*
 * mangled: _ZN12OFXmlElementD1Ev
 * demangled: OFXmlElement::~OFXmlElement()
 * address: 000d6efc
 * size: 344
 */

/* OFXmlElement::~OFXmlElement() */

void __thiscall OFXmlElement::~OFXmlElement(OFXmlElement *this)

{
  ID IVar1;
  OFPointer<OFXmlElement> *pOVar2;
  undefined1 auStack_b8 [4];
  OFXmlElement *local_b4;
  vector<OFPointer<OFXmlElement>,std::allocator<OFPointer<OFXmlElement>_>_> *local_a4;
  OFPointer<OFXmlElement> *local_a0;
  OFPointer<OFXmlElement> *local_9c;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_b8;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &LAB_000d7054;
  local_b4 = this;
  __Unwind_SjLj_Register(auStack_94);
  IVar1 = (local_b4->field5_0x1c).field0_0x0;
  local_b4->field0_0x0 = (undefined4 **)&PTR_GetRTTI_001b75e4;
  if (IVar1 != 0) {
    local_90 = 3;
    _objc_msgSend(IVar1,"release");
  }
  local_a4 = &local_b4->field4_0x10;
  pOVar2 = (local_b4->field4_0x10).field0_0x0.field0_0x0;
  local_a0 = (local_b4->field4_0x10).field0_0x0.field1_0x4;
  if (pOVar2 != local_a0) {
    do {
      local_9c = pOVar2;
      if (*(OFSmartObject **)pOVar2 != (OFSmartObject *)0x0) {
        local_90 = 1;
        OFSmartObject::Release(*(OFSmartObject **)pOVar2);
      }
      pOVar2 = local_9c + 4;
      local_9c = pOVar2;
    } while (local_a0 != pOVar2);
  }
  pOVar2 = (local_a4->field0_0x0).field0_0x0;
  if (pOVar2 != (OFPointer<OFXmlElement> *)0x0) {
    operator_delete(pOVar2);
  }
  IVar1 = (local_b4->field3_0xc).field0_0x0;
  if (IVar1 != 0) {
    local_90 = 4;
    _objc_msgSend(IVar1,"release");
  }
  IVar1 = (local_b4->field2_0x8).field0_0x0;
  if (IVar1 != 0) {
    local_90 = 5;
    _objc_msgSend(IVar1,"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_b4);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
