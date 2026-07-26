/*
 * mangled: _ZN20OFHttpQueryParameterD1Ev
 * demangled: OFHttpQueryParameter::~OFHttpQueryParameter()
 * address: 000caf9c
 * size: 156
 */

/* OFHttpQueryParameter::~OFHttpQueryParameter() */

void __thiscall OFHttpQueryParameter::~OFHttpQueryParameter(OFHttpQueryParameter *this)

{
  undefined1 auStack_9c [4];
  OFHttpQueryParameter *local_98;
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
  local_78 = &::GCC_except_table3;
  local_70 = &LAB_000cb038;
  local_98 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_98 = &PTR_GetRTTI_001b73cc;
  if (*(ID *)(local_98 + 8) != 0) {
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_98 + 8),"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
