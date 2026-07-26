/*
 * mangled: _ZN12OFXmlElementC2EP8NSString
 * demangled: OFXmlElement::OFXmlElement(NSString*)
 * address: 000d6b10
 * size: 204
 */

/* OFXmlElement::OFXmlElement(NSString*) */

void __thiscall OFXmlElement::OFXmlElement(OFXmlElement *this,NSString *param_1)

{
  OFRetainedPtr<NSString> local_a0;
  OFXmlElement *local_9c;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_a0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000d6bdc;
  local_a0.field0_0x0 = (ID)param_1;
  local_9c = this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject((OFSmartObject *)local_9c);
  local_9c->field0_0x0 = (undefined4 **)&PTR_GetRTTI_001b75e4;
  (local_9c->field2_0x8).field0_0x0 = 0;
  (local_9c->field3_0xc).field0_0x0 = local_a0.field0_0x0;
  if ((NSString *)local_a0.field0_0x0 != (NSString *)0x0) {
    local_90 = 1;
    _objc_msgSend(local_a0.field0_0x0,"retain");
  }
  (local_9c->field4_0x10).field0_0x0.field0_0x0 = (OFPointer<OFXmlElement> *)0x0;
  (local_9c->field4_0x10).field0_0x0.field1_0x4 = (OFPointer<OFXmlElement> *)0x0;
  (local_9c->field4_0x10).field0_0x0.field2_0x8 = (OFPointer<OFXmlElement> *)0x0;
  (local_9c->field5_0x1c).field0_0x0 = 0;
  *(undefined1 *)&local_9c->field6_0x20 = 0;
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
