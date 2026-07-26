/*
 * mangled: _ZN29OFHttpNestedQueryStringWriterC1Ev
 * demangled: OFHttpNestedQueryStringWriter::OFHttpNestedQueryStringWriter()
 * address: 000c979c
 * size: 4
 */

/* OFHttpNestedQueryStringWriter::OFHttpNestedQueryStringWriter() */

void __thiscall
OFHttpNestedQueryStringWriter::OFHttpNestedQueryStringWriter(OFHttpNestedQueryStringWriter *this)

{
  undefined1 auStack_c0 [4];
  OFOutputSerializer *pOStack_bc;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = auStack_c0;
  puStack_7c = PTR_001b615c;
  puStack_78 = &GCC_except_table8;
  puStack_70 = &LAB_000c95e8;
  pOStack_bc = (OFOutputSerializer *)this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFOutputSerializer::OFOutputSerializer(pOStack_bc);
  *(undefined ***)pOStack_bc = &PTR_GetRTTI_001b72c0;
  *(undefined4 *)(pOStack_bc + 0x18) = 0;
  *(undefined4 *)(pOStack_bc + 0x1c) = 0;
  *(undefined4 *)(pOStack_bc + 0x20) = 0;
  *(OFISerializer *)(pOStack_bc + 0x24) = (OFISerializer)0x0;
  uStack_90 = 3;
  OFISerializer::setSerializeResourcesExternally((OFISerializer *)pOStack_bc,false);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
