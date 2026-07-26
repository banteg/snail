/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter17addAsciiParameterEP8NSStringS1_
 * demangled: OFHttpNestedQueryStringWriter::addAsciiParameter(NSString*, NSString*)
 * address: 000c93c4
 * size: 292
 */

/* OFHttpNestedQueryStringWriter::addAsciiParameter(NSString*, NSString*) */

void __thiscall
OFHttpNestedQueryStringWriter::addAsciiParameter
          (OFHttpNestedQueryStringWriter *this,NSString *param_1,NSString *param_2)

{
  OFHttpAsciiParameter *pOVar1;
  OFHttpAsciiParameter *pOVar2;
  undefined1 auStack_b0 [4];
  NSString *local_ac;
  NSString *local_a8;
  OFHttpNestedQueryStringWriter *local_a4;
  OFHttpAsciiParameter *local_a0;
  OFHttpAsciiParameter *local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFHttpAsciiParameter *local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = auStack_b0;
  local_80 = PTR_001b615c;
  local_7c = &GCC_except_table6;
  local_74 = &LAB_000c94e8;
  local_ac = param_2;
  local_a8 = param_1;
  local_a4 = this;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  local_a0 = operator_new(0x10);
  local_94 = 2;
  local_9c = local_a0;
  OFHttpAsciiParameter::OFHttpAsciiParameter(local_a0,local_a8,local_ac);
  local_64[0] = local_a0;
  if (local_9c != (OFHttpAsciiParameter *)0x0) {
    *(int *)(local_a0 + 4) = *(int *)(local_a0 + 4) + 1;
  }
  pOVar2 = *(OFHttpAsciiParameter **)(local_a4 + 0x1c);
  if (pOVar2 == *(OFHttpAsciiParameter **)(local_a4 + 0x20)) {
    local_94 = 1;
    std::vector<OFPointer<OFHttpQueryParameter>,std::allocator<OFPointer<OFHttpQueryParameter>>>::
    _M_insert_aux((vector<OFPointer<OFHttpQueryParameter>,std::allocator<OFPointer<OFHttpQueryParameter>>>
                   *)(local_a4 + 0x18),pOVar2,local_64);
  }
  else {
    pOVar1 = *(OFHttpAsciiParameter **)(local_a4 + 0x20);
    if (pOVar2 != (OFHttpAsciiParameter *)0x0) {
      *(OFHttpAsciiParameter **)pOVar2 = local_a0;
      pOVar1 = local_a0;
    }
    if (pOVar2 != (OFHttpAsciiParameter *)0x0 && pOVar1 != (OFHttpAsciiParameter *)0x0) {
      *(int *)(pOVar1 + 4) = *(int *)(pOVar1 + 4) + 1;
    }
    *(int *)(local_a4 + 0x1c) = *(int *)(local_a4 + 0x1c) + 4;
  }
  if (local_64[0] != (OFHttpAsciiParameter *)0x0) {
    local_94 = 0xffffffff;
    OFSmartObject::Release((OFSmartObject *)local_64[0]);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
