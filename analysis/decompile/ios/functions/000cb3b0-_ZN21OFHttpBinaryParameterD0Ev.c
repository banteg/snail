/*
 * mangled: _ZN21OFHttpBinaryParameterD0Ev
 * demangled: OFHttpBinaryParameter::~OFHttpBinaryParameter()
 * address: 000cb3b0
 * size: 244
 */

/* OFHttpBinaryParameter::~OFHttpBinaryParameter() */

void __thiscall OFHttpBinaryParameter::~OFHttpBinaryParameter(OFHttpBinaryParameter *this)

{
  undefined1 auStack_a8 [4];
  OFHttpBinaryParameter *local_a4;
  OFHttpBinaryParameter *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a8;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table9;
  local_70 = &LAB_000cb4a4;
  local_a4 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_a4 = &PTR_GetRTTI_001b7360;
  if (*(OFSmartObject **)(local_a4 + 0x10) != (OFSmartObject *)0x0) {
    local_90 = 3;
    OFSmartObject::Release(*(OFSmartObject **)(local_a4 + 0x10));
  }
  if (*(ID *)(local_a4 + 0xc) != 0) {
    local_90 = 4;
    _objc_msgSend(*(ID *)(local_a4 + 0xc),"release");
  }
  local_98 = local_a4;
  *(undefined ***)local_a4 = &PTR_GetRTTI_001b73cc;
  if (*(ID *)(local_a4 + 8) != 0) {
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_a4 + 8),"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_98);
  operator_delete(local_a4);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
