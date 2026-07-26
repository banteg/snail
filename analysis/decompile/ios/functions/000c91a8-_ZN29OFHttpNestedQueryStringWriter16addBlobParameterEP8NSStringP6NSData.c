/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter16addBlobParameterEP8NSStringP6NSData
 * demangled: OFHttpNestedQueryStringWriter::addBlobParameter(NSString*, NSData*)
 * address: 000c91a8
 * size: 388
 */

/* OFHttpNestedQueryStringWriter::addBlobParameter(NSString*, NSData*) */

void __thiscall
OFHttpNestedQueryStringWriter::addBlobParameter
          (OFHttpNestedQueryStringWriter *this,NSString *param_1,NSData *param_2)

{
  OFHttpBinaryParameter *pOVar1;
  OFHttpBinaryParameter *pOVar2;
  undefined1 auStack_bc [4];
  NSData *local_b8;
  NSString *local_b4;
  OFHttpNestedQueryStringWriter *local_b0;
  OFBinaryMemorySink *local_ac;
  OFHttpBinaryParameter *local_a8;
  OFHttpBinaryParameter *local_a4;
  OFBinaryMemorySink *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  OFHttpBinaryParameter *local_68;
  OFBinaryMemorySink *local_64 [17];

  local_7c = &stack0xfffffff8;
  local_74 = auStack_bc;
  local_84 = PTR_001b615c;
  local_80 = &::GCC_except_table5;
  local_78 = &LAB_000c932c;
  local_b8 = param_2;
  local_b4 = param_1;
  local_b0 = this;
  __Unwind_SjLj_Register(auStack_9c);
  local_98 = 0xffffffff;
  local_ac = operator_new(0xc);
  local_98 = 4;
  local_a0 = local_ac;
  OFBinaryMemorySink::OFBinaryMemorySink(local_ac,local_b8);
  local_64[0] = local_a0;
  if (local_ac != (OFBinaryMemorySink *)0x0) {
    *(int *)(local_a0 + 4) = *(int *)(local_a0 + 4) + 1;
  }
  local_98 = 3;
  local_a8 = operator_new(0x14);
  local_98 = 2;
  local_a4 = local_a8;
  OFHttpBinaryParameter::OFHttpBinaryParameter(local_a8,local_b4,local_64,&cf_blob);
  local_68 = local_a8;
  if (local_a4 != (OFHttpBinaryParameter *)0x0) {
    *(int *)(local_a8 + 4) = *(int *)(local_a8 + 4) + 1;
  }
  pOVar2 = *(OFHttpBinaryParameter **)(local_b0 + 0x1c);
  if (pOVar2 == *(OFHttpBinaryParameter **)(local_b0 + 0x20)) {
    local_98 = 1;
    std::vector<OFPointer<OFHttpQueryParameter>,std::allocator<OFPointer<OFHttpQueryParameter>>>::
    _M_insert_aux((vector<OFPointer<OFHttpQueryParameter>,std::allocator<OFPointer<OFHttpQueryParameter>>>
                   *)(local_b0 + 0x18),pOVar2,&local_68);
  }
  else {
    pOVar1 = *(OFHttpBinaryParameter **)(local_b0 + 0x20);
    if (pOVar2 != (OFHttpBinaryParameter *)0x0) {
      *(OFHttpBinaryParameter **)pOVar2 = local_a8;
      pOVar1 = local_a8;
    }
    if (pOVar2 != (OFHttpBinaryParameter *)0x0 && pOVar1 != (OFHttpBinaryParameter *)0x0) {
      *(int *)(pOVar1 + 4) = *(int *)(pOVar1 + 4) + 1;
    }
    *(int *)(local_b0 + 0x1c) = *(int *)(local_b0 + 0x1c) + 4;
  }
  if (local_68 != (OFHttpBinaryParameter *)0x0) {
    local_98 = 3;
    OFSmartObject::Release((OFSmartObject *)local_68);
  }
  if (local_64[0] != (OFBinaryMemorySink *)0x0) {
    local_98 = 0xffffffff;
    OFSmartObject::Release((OFSmartObject *)local_64[0]);
  }
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
