/*
 * mangled: _ZN18OFBinaryMemorySinkD0Ev
 * demangled: OFBinaryMemorySink::~OFBinaryMemorySink()
 * address: 000c86b8
 * size: 176
 */

/* OFBinaryMemorySink::~OFBinaryMemorySink() */

void __thiscall OFBinaryMemorySink::~OFBinaryMemorySink(OFBinaryMemorySink *this)

{
  undefined1 auStack_9c [4];
  OFBinaryMemorySink *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_9c;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table2;
  local_70 = &LAB_000c8768;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_98 = &PTR_GetRTTI_001b7278;
  if (*(ID *)(local_98 + 8) != 0) {
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_98 + 8),"release");
  }
  *(undefined ***)local_98 = &PTR_GetRTTI_001b72a8;
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_98);
  operator_delete(local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
