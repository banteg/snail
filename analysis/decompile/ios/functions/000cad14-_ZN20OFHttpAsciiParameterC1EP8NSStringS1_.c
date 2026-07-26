/*
 * mangled: _ZN20OFHttpAsciiParameterC1EP8NSStringS1_
 * demangled: OFHttpAsciiParameter::OFHttpAsciiParameter(NSString*, NSString*)
 * address: 000cad14
 * size: 224
 */

/* OFHttpAsciiParameter::OFHttpAsciiParameter(NSString*, NSString*) */

void __thiscall
OFHttpAsciiParameter::OFHttpAsciiParameter
          (OFHttpAsciiParameter *this,NSString *param_1,NSString *param_2)

{
  undefined1 auStack_ac [4];
  NSString *local_a8;
  NSString *local_a4;
  OFSmartObject *local_a0;
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
  local_78 = &::GCC_except_table5;
  local_70 = &LAB_000cadf4;
  local_a8 = param_2;
  local_a4 = param_1;
  local_a0 = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(local_a0);
  *(undefined ***)local_a0 = &PTR_GetRTTI_001b73cc;
  *(NSString **)(local_a0 + 8) = local_a4;
  if (local_a4 != (NSString *)0x0) {
    local_90 = 2;
    _objc_msgSend((ID)local_a4,"retain");
  }
  *(undefined ***)local_a0 = &PTR_GetRTTI_001b7384;
  *(NSString **)(local_a0 + 0xc) = local_a8;
  if (local_a8 != (NSString *)0x0) {
    local_90 = 3;
    _objc_msgSend((ID)local_a8,"retain");
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
