/*
 * mangled: _ZN21OFHttpBinaryParameterC2EP8NSString9OFPointerI18OFBinaryMemorySinkES1_
 * demangled: OFHttpBinaryParameter::OFHttpBinaryParameter(NSString*, OFPointer<OFBinaryMemorySink>, NSString*)
 * address: 000cab44
 * size: 260
 */

/* OFHttpBinaryParameter::OFHttpBinaryParameter(NSString*, OFPointer<OFBinaryMemorySink>, NSString*)
    */

void __thiscall
OFHttpBinaryParameter::OFHttpBinaryParameter
          (OFHttpBinaryParameter *this,ID param_1,int *param_3,ID param_4)

{
  int iVar1;
  undefined1 auStack_b0 [4];
  ID local_ac;
  int *local_a8;
  ID local_a4;
  OFSmartObject *local_a0;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_b0;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table4;
  local_70 = &LAB_000cac48;
  local_ac = param_4;
  local_a8 = param_3;
  local_a4 = param_1;
  local_a0 = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(local_a0);
  *(undefined ***)local_a0 = &PTR_GetRTTI_001b73cc;
  *(ID *)(local_a0 + 8) = local_a4;
  if (local_a4 != 0) {
    local_90 = 2;
    _objc_msgSend(local_a4,"retain");
  }
  *(undefined ***)local_a0 = &PTR_GetRTTI_001b7360;
  *(ID *)(local_a0 + 0xc) = local_ac;
  if (local_ac != 0) {
    local_90 = 3;
    _objc_msgSend(local_ac,"retain");
  }
  iVar1 = *local_a8;
  *(int *)(local_a0 + 0x10) = iVar1;
  if (iVar1 != 0) {
    *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
