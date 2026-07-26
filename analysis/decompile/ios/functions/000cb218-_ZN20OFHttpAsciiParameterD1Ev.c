/*
 * mangled: _ZN20OFHttpAsciiParameterD1Ev
 * demangled: OFHttpAsciiParameter::~OFHttpAsciiParameter()
 * address: 000cb218
 * size: 216
 */

/* OFHttpAsciiParameter::~OFHttpAsciiParameter() */

void __thiscall OFHttpAsciiParameter::~OFHttpAsciiParameter(OFHttpAsciiParameter *this)

{
  undefined1 auStack_ac [4];
  OFHttpAsciiParameter *local_a8;
  char *local_a0;
  OFHttpAsciiParameter *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_ac;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table8;
  local_70 = &LAB_000cb2f0;
  local_a8 = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_a8 = &PTR_GetRTTI_001b7384;
  if (*(ID *)(local_a8 + 0xc) != 0) {
    local_a0 = "release";
    local_90 = 3;
    _objc_msgSend(*(ID *)(local_a8 + 0xc),"release");
  }
  local_98 = local_a8;
  *(undefined ***)local_a8 = &PTR_GetRTTI_001b73cc;
  if (*(ID *)(local_a8 + 8) != 0) {
    local_90 = 1;
    _objc_msgSend(*(ID *)(local_a8 + 8),"release");
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_98);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
