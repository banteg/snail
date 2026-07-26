/*
 * mangled: _ZN21OFHttpBinaryParameterC1EP8NSString9OFPointerI18OFBinaryMemorySinkES1_
 * demangled: OFHttpBinaryParameter::OFHttpBinaryParameter(NSString*, OFPointer<OFBinaryMemorySink>, NSString*)
 * address: 000cad10
 * size: 4
 */

/* OFHttpBinaryParameter::OFHttpBinaryParameter(NSString*, OFPointer<OFBinaryMemorySink>, NSString*)
    */

void __thiscall
OFHttpBinaryParameter::OFHttpBinaryParameter
          (OFHttpBinaryParameter *this,ID param_1,int *param_3,ID param_4)

{
  int iVar1;
  undefined1 auStack_b0 [4];
  ID IStack_ac;
  int *piStack_a8;
  ID IStack_a4;
  OFSmartObject *pOStack_a0;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = auStack_b0;
  puStack_7c = PTR_001b615c;
  puStack_78 = &::GCC_except_table4;
  puStack_70 = &LAB_000cac48;
  IStack_ac = param_4;
  piStack_a8 = param_3;
  IStack_a4 = param_1;
  pOStack_a0 = (OFSmartObject *)this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFSmartObject::OFSmartObject(pOStack_a0);
  *(undefined ***)pOStack_a0 = &PTR_GetRTTI_001b73cc;
  *(ID *)(pOStack_a0 + 8) = IStack_a4;
  if (IStack_a4 != 0) {
    uStack_90 = 2;
    _objc_msgSend(IStack_a4,"retain");
  }
  *(undefined ***)pOStack_a0 = &PTR_GetRTTI_001b7360;
  *(ID *)(pOStack_a0 + 0xc) = IStack_ac;
  if (IStack_ac != 0) {
    uStack_90 = 3;
    _objc_msgSend(IStack_ac,"retain");
  }
  iVar1 = *piStack_a8;
  *(int *)(pOStack_a0 + 0x10) = iVar1;
  if (iVar1 != 0) {
    *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
