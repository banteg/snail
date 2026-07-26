/*
 * mangled: _ZN29OFHttpNestedQueryStringWriterC2Ev
 * demangled: OFHttpNestedQueryStringWriter::OFHttpNestedQueryStringWriter()
 * address: 000c9548
 * size: 160
 */

/* OFHttpNestedQueryStringWriter::OFHttpNestedQueryStringWriter() */

void __thiscall
OFHttpNestedQueryStringWriter::OFHttpNestedQueryStringWriter(OFHttpNestedQueryStringWriter *this)

{
  undefined1 auStack_c0 [4];
  OFOutputSerializer *local_bc;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_c0;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table8;
  local_70 = &LAB_000c95e8;
  local_bc = (OFOutputSerializer *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFOutputSerializer::OFOutputSerializer(local_bc);
  *(undefined ***)local_bc = &PTR_GetRTTI_001b72c0;
  *(undefined4 *)(local_bc + 0x18) = 0;
  *(undefined4 *)(local_bc + 0x1c) = 0;
  *(undefined4 *)(local_bc + 0x20) = 0;
  *(OFISerializer *)(local_bc + 0x24) = (OFISerializer)0x0;
  local_90 = 3;
  OFISerializer::setSerializeResourcesExternally((OFISerializer *)local_bc,false);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
