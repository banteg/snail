/*
 * mangled: _ZN19OFBinaryKeyedWriterC2Eb
 * demangled: OFBinaryKeyedWriter::OFBinaryKeyedWriter(bool)
 * address: 000c7648
 * size: 160
 */

/* OFBinaryKeyedWriter::OFBinaryKeyedWriter(bool) */

void __thiscall OFBinaryKeyedWriter::OFBinaryKeyedWriter(OFBinaryKeyedWriter *this,bool param_1)

{
  undefined1 auStack_b4 [4];
  uint local_b0;
  OFOutputSerializer *local_ac;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_b0 = (uint)param_1;
  local_74 = &stack0xfffffff8;
  local_6c = auStack_b4;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table7;
  local_70 = &LAB_000c76e8;
  local_ac = (OFOutputSerializer *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFOutputSerializer::OFOutputSerializer(local_ac);
  *(undefined ***)local_ac = &PTR_GetRTTI_001b70e8;
  *(undefined4 *)(local_ac + 0x18) = 0;
  local_90 = 2;
  OFISerializer::setSerializeResourcesExternally((OFISerializer *)local_ac,SUB41(local_b0,0));
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
