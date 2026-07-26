/*
 * mangled: _ZN23OFBinarySdbmKeyedWriterC2E9OFPointerI12OFBinarySinkEb
 * demangled: OFBinarySdbmKeyedWriter::OFBinarySdbmKeyedWriter(OFPointer<OFBinarySink>, bool)
 * address: 000c833c
 * size: 212
 */

/* OFBinarySdbmKeyedWriter::OFBinarySdbmKeyedWriter(OFPointer<OFBinarySink>, bool) */

void __thiscall
OFBinarySdbmKeyedWriter::OFBinarySdbmKeyedWriter
          (OFBinarySdbmKeyedWriter *this,int *param_2,uint param_3)

{
  undefined1 auStack_a8 [4];
  uint local_a4;
  int *local_a0;
  OFBinaryKeyedWriter *local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFSmartObject *local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = auStack_a8;
  local_a4 = param_3 & 0xff;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table1;
  local_74 = &LAB_000c8410;
  local_a0 = param_2;
  local_9c = (OFBinaryKeyedWriter *)this;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  OFBinaryKeyedWriter::OFBinaryKeyedWriter(local_9c,SUB41(local_a4,0));
  *(undefined ***)local_9c = &PTR_GetRTTI_001b7200;
  local_64[0] = (OFSmartObject *)*local_a0;
  if (local_64[0] != (OFSmartObject *)0x0) {
    *(int *)(local_64[0] + 4) = *(int *)(local_64[0] + 4) + 1;
  }
  local_94 = 1;
  OFBinaryKeyedWriter::initialize(local_9c,local_64);
  if (local_64[0] != (OFSmartObject *)0x0) {
    local_94 = 2;
    OFSmartObject::Release(local_64[0]);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
