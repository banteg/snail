/*
 * mangled: _ZN18OFBinaryMemorySinkC1EP6NSData
 * demangled: OFBinaryMemorySink::OFBinaryMemorySink(NSData*)
 * address: 000c88b0
 * size: 168
 */

/* OFBinaryMemorySink::OFBinaryMemorySink(NSData*) */

void __thiscall OFBinaryMemorySink::OFBinaryMemorySink(OFBinaryMemorySink *this,NSData *param_1)

{
  undefined1 auStack_a0 [4];
  NSData *local_9c;
  OFSmartObject *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a0;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table8;
  local_70 = &LAB_000c8958;
  local_9c = param_1;
  local_98 = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(local_98);
  *(undefined ***)local_98 = &PTR_GetRTTI_001b7278;
  *(NSData **)(local_98 + 8) = local_9c;
  if (local_9c != (NSData *)0x0) {
    local_90 = 1;
    _objc_msgSend((ID)local_9c,"retain");
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
