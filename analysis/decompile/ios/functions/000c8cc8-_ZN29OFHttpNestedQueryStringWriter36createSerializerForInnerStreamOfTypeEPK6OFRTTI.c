/*
 * mangled: _ZN29OFHttpNestedQueryStringWriter36createSerializerForInnerStreamOfTypeEPK6OFRTTI
 * demangled: OFHttpNestedQueryStringWriter::createSerializerForInnerStreamOfType(OFRTTI const*)
 * address: 000c8cc8
 * size: 276
 */

/* OFHttpNestedQueryStringWriter::createSerializerForInnerStreamOfType(OFRTTI const*) */

OFRTTI * OFHttpNestedQueryStringWriter::createSerializerForInnerStreamOfType(OFRTTI *param_1)

{
  OFBinaryMemorySink *pOVar1;
  undefined1 auStack_b4 [4];
  OFRTTI *local_b0;
  OFBinaryMemorySink *local_ac;
  OFBinaryMemorySink *local_a8;
  OFBinarySdbmKeyedWriter *local_a4;
  OFBinarySdbmKeyedWriter *local_a0;
  OFRTTI *local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFBinaryMemorySink *local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = auStack_b4;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table2;
  local_74 = &LAB_000c8ddc;
  local_b0 = param_1;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  local_9c = local_b0;
  local_ac = operator_new(0xc);
  local_94 = 3;
  local_a8 = local_ac;
  OFBinaryMemorySink::OFBinaryMemorySink(local_ac);
  pOVar1 = (OFBinaryMemorySink *)0x0;
  if (local_a8 != (OFBinaryMemorySink *)0x0) {
    pOVar1 = local_ac;
  }
  local_64[0] = local_ac;
  if (local_a8 != (OFBinaryMemorySink *)0x0) {
    *(int *)(pOVar1 + 4) = *(int *)(pOVar1 + 4) + 1;
  }
  local_94 = 2;
  local_a4 = operator_new(0x1c);
  local_94 = 1;
  local_a0 = local_a4;
  OFBinarySdbmKeyedWriter::OFBinarySdbmKeyedWriter(local_a4,local_64,0);
  *(OFBinarySdbmKeyedWriter **)local_9c = local_a4;
  if (local_a0 != (OFBinarySdbmKeyedWriter *)0x0) {
    *(int *)(local_a4 + 4) = *(int *)(local_a4 + 4) + 1;
  }
  if (local_64[0] != (OFBinaryMemorySink *)0x0) {
    local_94 = 0xffffffff;
    OFSmartObject::Release((OFSmartObject *)local_64[0]);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return local_b0;
}
