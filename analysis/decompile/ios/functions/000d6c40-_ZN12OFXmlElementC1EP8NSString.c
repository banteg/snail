/*
 * mangled: _ZN12OFXmlElementC1EP8NSString
 * demangled: OFXmlElement::OFXmlElement(NSString*)
 * address: 000d6c40
 * size: 4
 */

/* OFXmlElement::OFXmlElement(NSString*) */

void __thiscall OFXmlElement::OFXmlElement(OFXmlElement *this,NSString *param_1)

{
  OFRetainedPtr<NSString> OStack_a0;
  OFXmlElement *pOStack_9c;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = (undefined1 *)&OStack_a0;
  puStack_7c = PTR_001b615c;
  puStack_78 = &::GCC_except_table0;
  puStack_70 = &LAB_000d6bdc;
  OStack_a0.field0_0x0 = (ID)param_1;
  pOStack_9c = this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFSmartObject::OFSmartObject((OFSmartObject *)pOStack_9c);
  pOStack_9c->field0_0x0 = (undefined4 **)&PTR_GetRTTI_001b75e4;
  (pOStack_9c->field2_0x8).field0_0x0 = 0;
  (pOStack_9c->field3_0xc).field0_0x0 = OStack_a0.field0_0x0;
  if ((NSString *)OStack_a0.field0_0x0 != (NSString *)0x0) {
    uStack_90 = 1;
    _objc_msgSend(OStack_a0.field0_0x0,"retain");
  }
  (pOStack_9c->field4_0x10).field0_0x0.field0_0x0 = (OFPointer<OFXmlElement> *)0x0;
  (pOStack_9c->field4_0x10).field0_0x0.field1_0x4 = (OFPointer<OFXmlElement> *)0x0;
  (pOStack_9c->field4_0x10).field0_0x0.field2_0x8 = (OFPointer<OFXmlElement> *)0x0;
  (pOStack_9c->field5_0x1c).field0_0x0 = 0;
  *(undefined1 *)&pOStack_9c->field6_0x20 = 0;
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
