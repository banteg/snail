/*
 * mangled: _ZN13OFHttpServiceC2E13OFRetainedPtrI8NSStringEb
 * demangled: OFHttpService::OFHttpService(OFRetainedPtr<NSString>, bool)
 * address: 000cfdd8
 * size: 216
 */

/* OFHttpService::OFHttpService(OFRetainedPtr<NSString>, bool) */

void __thiscall OFHttpService::OFHttpService(OFHttpService *this,ID *param_2,uint param_3)

{
  ID self;
  undefined1 auStack_a4 [4];
  uint local_a0;
  ID *local_9c;
  OFHttpService *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a4;
  local_a0 = param_3 & 0xff;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000cfeb0;
  local_9c = param_2;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject((OFSmartObject *)local_98);
  local_98->field0_0x0 = (undefined4 **)&PTR_GetRTTI_001b7528;
  local_98->field2_0x8 = (undefined4 **)&PTR__OFHttpService_001b7550;
  self = *local_9c;
  (local_98->field3_0xc).field0_0x0 = self;
  if (self != 0) {
    local_90 = 1;
    _objc_msgSend(self,"retain");
  }
  *(char *)&local_98->field4_0x10 = (char)local_a0;
  (local_98->field5_0x14).field0_0x0.field0_0x0 = (OFHttpServiceRequestContainer *)0x0;
  (local_98->field5_0x14).field0_0x0.field1_0x4 = (OFHttpServiceRequestContainer *)0x0;
  (local_98->field5_0x14).field0_0x0.field2_0x8 = (OFHttpServiceRequestContainer *)0x0;
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
